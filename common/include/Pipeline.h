#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <memory>

#include "Config.h"
#include "Camera.h"

struct PerspectiveProj
{
    PerspectiveProj(
        float fov = 30.0f / 180.0f * PI,
        float width = WINDOW_WIDTH,
        float height = WINDOW_HEIGHT,
        float zNear = 1.0f,
        float zFar = 100.0f)
        :fov(fov),
        width(width),
        height(height),
        zNear(zNear),
        zFar(zFar) 
    {}

    float fov;
    float width;
    float height;
    float zNear;
    float zFar;
};

class Pipeline
{
public:
    Pipeline();
    void Scale(float ScaleX, float ScaleY, float ScaleZ);
    void WorldPos(float x, float y, float z);
    void Rotate(float RotateX, float RotateY, float RotateZ);
    void SetPerspectiveProj(float fov, float width, float height, float zNear, float zFar);
    void SetCamera(std::shared_ptr<Camera> pCamera);
    const glm::mat4* GetTrans();
private:
    glm::vec3 m_scale;
    glm::vec3 m_worldPos;
    glm::vec3 m_rotateInfo;
    glm::mat4 m_transformation;
    PerspectiveProj m_persProj = {};
    std::shared_ptr<Camera> m_pCamera;
};