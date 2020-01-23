#include "..\include\AmbientLight.h"

#include "Texture.h"
#include "Camera.h"
#include "Light.h"
#include "Math3d.h"
#include "TechLight.h"
#include "Pipeline.h"
#include "Vertex.h"

AmbientLight::AmbientLight()
	:m_pCamera(nullptr),
	m_pTexture(nullptr),
	m_pEffect(nullptr),
	m_pDirectionalLight(nullptr),
	m_pPersProjInfo(nullptr),
	m_move(0.0f),
	m_VBO(0),//?
	m_IBO(0)
{
}

AmbientLight::~AmbientLight()
{
}

bool AmbientLight::Init()
{
	//model
	CreateVertexBuffer();
	CreateIndexBuffer();

	//effect-1.build
	m_pEffect = std::make_shared<TechLight>();
	if (!m_pEffect->Init())
		return false;
	m_pEffect->Enable();
	m_pEffect->SetTextureUnit(0);

	//camera
	m_pCamera = std::make_shared<Camera>(WINDOW_WIDTH, WINDOW_HEIGHT);

	//proj
	m_pPersProjInfo = std::make_shared<PersProjInfo>(60.0f / 180.0f * PI, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);

	//texture
	m_pTexture = std::make_shared<Texture>(GL_TEXTURE_2D, "images/test.png");
	if (!m_pTexture->Load())
		return false;

	//light
	m_pDirectionalLight = std::make_shared<DirectionalLight>();
	m_pDirectionalLight->Color = { 1.0f, 1.0f, 1.0f };
	m_pDirectionalLight->AmbientIntensity = 0.5f;

	return true;
}

void AmbientLight::Display()
{
	m_pCamera->OnRender();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_move += 0.1f;
	Pipeline p;
	p.Rotate(0.0f, m_move, 0.0f);
	p.WorldPos(0.0f, 0.0f, -10.0f);
	p.SetCamera(m_pCamera);
	p.SetPersProjInfo(m_pPersProjInfo);
	m_pEffect->SetWVP(p.GetWVPTrans());
	m_pEffect->SetDirectionalLight(m_pDirectionalLight);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	m_pTexture->Bind(GL_TEXTURE0);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void AmbientLight::KeyboardCB(KEY key, BUTTON_ACTION state)
{
	m_pCamera->OnKeyboard(key);
}

void AmbientLight::PassiveMouseCB(int x, int y)
{
	m_pCamera->OnMouse((uint32_t)x, (uint32_t)y);
}

void AmbientLight::FrameSetting(bool withDepth, bool withStencil)
{
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	if (withDepth) {
		glEnable(GL_DEPTH_TEST);
	}

	if (withStencil) {
		glEnable(GL_STENCIL_TEST);
	}
}

void AmbientLight::CreateVertexBuffer()
{
	Vertex Vertices[4] = {
		{{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
		{{0.0f, -1.0f, 1.0f}, {0.5f, 0.0f}},
		{{1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
		{{0.0f, 1.0f, 0.0f}, {0.5f, 1.0f}}
	};

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

void AmbientLight::CreateIndexBuffer()
{
	Index Indices[] = { 0, 1, 3,
						1, 2, 3,
						2, 0, 3,
						0, 2, 1 };

	glCreateBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}


