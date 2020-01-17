#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>

#include "Camera.h"
#include "Config.h"

Camera::Camera(const glm::vec3& Pos, const glm::vec3& Target, const glm::vec3& Up)
    :m_pos(Pos),
    m_target(Target),
    m_up(Up)
{
}

bool Camera::OnKeyboard(int key)
{
    bool Ret = false;

    switch (key)
    {
    case GLFW_KEY_UP://towards the target
    {
        m_pos += m_target * CameraMoveStepSize;
        Ret = true;
        break;
    }
    case GLFW_KEY_DOWN:
    {
        m_pos -= m_target * CameraMoveStepSize;
        Ret = true;
        break;
    }
    case GLFW_KEY_LEFT:
    {
        glm::vec3 left = -glm::cross(m_target, m_up);
        left = glm::normalize(left);
        left *= CameraMoveStepSize;
        m_pos += left;
        Ret = true;
        break;
    }
    case GLFW_KEY_RIGHT:
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
