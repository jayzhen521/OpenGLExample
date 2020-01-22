#pragma once

#include <memory>
#include <GL/gl3w.h>

#include "ICallbacks.h"
#include "Statistics.h"
#include "Keys.h"

//
class TechLight;
class PersProjInfo;
class Texture;
class Camera;
class DirectionalLight;

class AmbientLight : public ICallbacks, public Statistics
{
public:
    AmbientLight();
    ~AmbientLight();

    bool Init();

    virtual void Display() override;

    virtual void KeyboardCB(KEY key, BUTTON_ACTION state) override;

    virtual void PassiveMouseCB(int x, int y) override;

    virtual void FrameSetting(bool withDepth, bool withStencil) override;

private:
    void CreateVertexBuffer();

    void CreateIndexBuffer();

    GLuint m_VBO;
    GLuint m_IBO;
    std::shared_ptr<TechLight> m_pEffect;
    std::shared_ptr<Texture> m_pTexture;
    std::shared_ptr<Camera> m_pCamera;
    std::shared_ptr<PersProjInfo> m_pPersProjInfo;
    std::shared_ptr<DirectionalLight> m_pDirectionalLight;

    float m_move;
};