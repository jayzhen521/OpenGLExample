#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <memory>

class Camera;
class PersProjInfo;

class Pipeline
{
public:
    Pipeline();
    void Scale(float ScaleX, float ScaleY, float ScaleZ);
    void WorldPos(float x, float y, float z);
    void Rotate(float RotateX, float RotateY, float RotateZ);
    void SetPersProjInfo(std::shared_ptr<PersProjInfo> pPersProjInfo);
    void SetCamera(std::shared_ptr<Camera> pCamera);
    const std::shared_ptr<glm::mat4> GetWVPTrans();
private:
    glm::vec3 m_scale;
    glm::vec3 m_worldPos;
    glm::vec3 m_rotateInfo;
    std::shared_ptr<glm::mat4> m_pTransformation;
    std::shared_ptr<PersProjInfo> m_pPersProjInfo;
    std::shared_ptr<Camera> m_pCamera;
};