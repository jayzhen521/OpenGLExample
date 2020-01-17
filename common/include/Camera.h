#pragma once

#include <glm/vec3.hpp>

struct Camera {

    Camera(
        const glm::vec3& Pos = { 0.0f, 0.0f, 0.0f },
        const glm::vec3& Target = { 0.0f, 0.0f, -1.0f },
        const glm::vec3& Up = { 0.0f, 1.0f, 0.0f });

    bool OnKeyboard(int Key);

    const glm::vec3& GetPos() const;
    const glm::vec3& GetTarget() const;
    const glm::vec3& GetUp() const;

private:
    glm::vec3 m_pos;
    glm::vec3 m_target;
    glm::vec3 m_up;
};
