#include <glm/gtc/type_ptr.hpp>

#include "TechLight.h"

TechLight::TechLight()
{
}

bool TechLight::Init()
{
	if (!Technique::Init())
		return false;

	if (!AddShader(GL_VERTEX_SHADER, "shaders/lighting.vs"))
		return false;

	if (!AddShader(GL_FRAGMENT_SHADER, "shaders/lighting.fs"))
		return false;

	if (!Finalize())
		return false;

	m_WVPLocation = GetUniformLocation("gWVP");
	m_samplerLocation = GetUniformLocation("gSampler");
	m_dirLightColorLocation = GetUniformLocation("gDirectionalLight.Color");
	m_dirLightAmbientIntensityLocation = GetUniformLocation("gDirectionalLight.AmbientIntensity");

	if (m_dirLightAmbientIntensityLocation == 0xFFFFFFFF ||
		m_WVPLocation == 0xFFFFFFFF ||
		m_samplerLocation == 0xFFFFFFFF ||
		m_dirLightColorLocation == 0xFFFFFFFF)
	{
		return false;
	}

	return true;
}

void TechLight::SetWVP(const std::shared_ptr<glm::mat4> WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, glm::value_ptr(*WVP));
}

void TechLight::SetTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_samplerLocation, TextureUnit);
}

void TechLight::SetDirectionalLight(const std::shared_ptr<DirectionalLight> pLight)
{
	glUniform3f(m_dirLightColorLocation, pLight->Color.x, pLight->Color.y, pLight->Color.z);
	glUniform1f(m_dirLightAmbientIntensityLocation, pLight->AmbientIntensity);
}
