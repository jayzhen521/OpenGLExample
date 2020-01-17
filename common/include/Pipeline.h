#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

struct PerspectiveProj
{
    float fov;
    float width;
    float height;
    float zNear;
    float zFar;
};

struct Camera {
    glm::vec3 Pos;
    glm::vec3 Target;
    glm::vec3 Up;
};

class Pipeline
{
public:
    Pipeline();
    void Scale(float ScaleX, float ScaleY, float ScaleZ);
    void WorldPos(float x, float y, float z);
    void Rotate(float RotateX, float RotateY, float RotateZ);
    void SetPerspectiveProj(float fov, float width, float height, float zNear, float zFar);
    void SetCamera(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
    const glm::mat4* GetTrans();
private:
    glm::vec3 m_scale;
    glm::vec3 m_worldPos;
    glm::vec3 m_rotateInfo;
    glm::mat4 m_transformation;
    PerspectiveProj m_persProj;
    Camera m_camera;
};