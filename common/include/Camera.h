#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "Config.h"
#include "Keys.h"

const uint32_t MARGIN = 10;

class Camera {
public:
    Camera(
        uint32_t WindowWidth,
        uint32_t WindowHeight,
        const glm::vec3& Pos = { 0.0f, 0.0f, 10.0f },
        const glm::vec3& Target = { 0.0f, 0.0f, -1.0f },
        const glm::vec3& Up = { 0.0f, 1.0f, 0.0f });

    void Init();

    bool OnKeyboard(KEY key);

    /*
    *If we move mouse to the left edge, with DelatX changed, status m_onLeftEdge will not be changed,
    and then If we stop move the mouse, no cursor event, so m_onLeftEdge will not be changed too. Only
    when cursor in the left edge and when you move cursor up or down.
    */

    void OnMouse(uint32_t x, uint32_t y);
    void OnRender();
    void Update();

    const glm::vec3& GetPos() const;
    const glm::vec3& GetTarget() const;
    const glm::vec3& GetUp() const;

private:
    uint32_t m_windowWidth;
    uint32_t m_windowHeight;
    glm::vec3 m_pos;
    glm::vec3 m_target;
    glm::vec3 m_up;

    float m_angleH = 0.0f;
    float m_angleV = 0.0f;

    bool m_onUpperEdge = false;
    bool m_onLowerEdge = false;
    bool m_onLeftEdge = false;
    bool m_onRightEdge = false;

    glm::uvec2 m_mousePos = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
};
