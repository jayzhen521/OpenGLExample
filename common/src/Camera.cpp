#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Camera.h"
#include "Config.h"

Camera::Camera(uint32_t WindowWidth, uint32_t WindowHeight, const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up)
    :m_windowWidth(WindowWidth),
    m_windowHeight(WindowHeight),
    m_pos(Pos),
    m_target(Target),
    m_up(Up)
{
    m_target = glm::normalize(m_target);
    m_up = glm::normalize(m_up);

    Init();
}

void Camera::Init()
{
    glm::vec3 HTarget(m_target.x, 0.0f, m_target.z);
    HTarget = glm::normalize(HTarget);

    if (HTarget.z >= 0)
    {
        if (HTarget.x >= 0)
        {
            m_angleH = 360.0f - glm::degrees(asinf(HTarget.z));
        }
        else
        {
            m_angleH = 180.0f + glm::degrees(asinf(HTarget.z));
        }
    }
    else
    {
        if (HTarget.x >= 0)
        {
            m_angleH = glm::degrees(asinf(HTarget.z));
        }
        else
        {
            m_angleH = 180.0f - glm::degrees(asinf(HTarget.z));
        }
    }

    m_angleV = -glm::degrees(asinf(m_target.y));

    m_onUpperEdge = false;
    m_onLowerEdge = false;
    m_onLeftEdge = false;
    m_onRightEdge = false;
    m_mousePos.x = m_windowWidth / 2;
    m_mousePos.y = m_windowHeight / 2;

    //?send command to window
}

bool Camera::OnKeyboard(KEY key)
{
    bool Ret = false;

    switch (key)
    {
    case KEY::KEY_UP://towards the target
    {
        m_pos += m_target * CameraMoveStepSize;
        Ret = true;
        break;
    }
    case KEY::KEY_DOWN:
    {
        m_pos -= m_target * CameraMoveStepSize;
        Ret = true;
        break;
    }
    case KEY::KEY_LEFT:
    {
        glm::vec3 left = -glm::cross(m_target, m_up);
        left = glm::normalize(left);
        left *= CameraMoveStepSize;
        m_pos += left;
        Ret = true;
        break;
    }
    case KEY::KEY_RIGHT:
    {
        glm::vec3 right = glm::cross(m_target, m_up);
        right = glm::normalize(right);
        right *= CameraMoveStepSize;
        m_pos += right;
        Ret = true;
        break;
    }
    }

    return Ret;
}

void Camera::OnMouse(uint32_t x, uint32_t y)
{
    const int DeltaX = x - m_mousePos.x;
    const int DeltaY = y - m_mousePos.y;
    m_mousePos = { x, y };

    m_angleH += (float)DeltaX / 100.0f;
    m_angleV += (float)DeltaY / 100.0f;

    if (DeltaX == 0)
    {
        if ((uint32_t)x <= MARGIN) {
            m_onLeftEdge = true;
        }
        else if ((uint32_t)x >= m_windowWidth - MARGIN){
            m_onRightEdge = true;
        }
    }
    else {
        m_onLeftEdge = false;
        m_onRightEdge = false;
    }

    if (DeltaY == 0) {
        if ((uint32_t)y <= MARGIN) {
            m_onUpperEdge = true;
        }
        else if ((uint32_t)y >= (m_windowHeight - MARGIN)) {
            m_onLowerEdge = true;
        }
    }
    else {
        m_onUpperEdge = false;
        m_onLowerEdge = false;
    }

    Update();
}

void Camera::OnRender()
{
    bool ShouldUpdate = false;

    if (m_onLeftEdge) {
        m_angleH -= 0.1f;
        ShouldUpdate = true;
    }
    else if (m_onRightEdge) {
        m_angleH += 0.1f;
        ShouldUpdate = true;
    }

    if (m_onUpperEdge) {
        if (m_angleV > -90.0f) {
            m_angleV -= 0.1f;
            ShouldUpdate = true;
        }
    }
    else if (m_onLowerEdge) {
        if (m_angleV < 90.0f) {
            m_angleV += 0.1f;
            ShouldUpdate = true;
        }
    }

    if (ShouldUpdate) {
        Update();
    }
}

void Camera::Update()
{
    const float aot = glm::radians(m_angleH / 2.0f);
    const float sin_aot = sinf(aot);
    const float cos_aot = cosf(aot);

    const float aotv = glm::radians(m_angleV / 2.0f);
    const float sin_aotv = sinf(aotv);
    const float cos_aotv = cosf(aotv);

    glm::vec3 VAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 View = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::quat quaternion = glm::quat(cos_aot, sin_aot * VAxis);
    View = glm::conjugate(quaternion) * View * quaternion;
    View = glm::normalize(View);

    glm::mat4 mat = glm::toMat4(quaternion);
    
    glm::vec3 Haxis = glm::cross(View, VAxis);
    Haxis = glm::normalize(Haxis);
    quaternion = glm::quat(cos_aotv, sin_aotv * Haxis);
    View = glm::conjugate(quaternion) * View * quaternion;
    View = glm::normalize(View);

    m_target = View;
    m_up = glm::cross(Haxis, m_target);

    m_up = glm::normalize(m_up);
}

const glm::vec3& Camera::GetPos() const
{
    return m_pos;
}

const glm::vec3& Camera::GetTarget() const
{
    return m_target;
}

const glm::vec3& Camera::GetUp() const
{
    return m_up;
}
