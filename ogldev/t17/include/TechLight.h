#include <glm/mat4x4.hpp>
#include <GL/gl3w.h>
#include <memory>

#include "Light.h"
#include "Technique.h"

class TechLight : public Technique
{
public:
	TechLight();

	virtual bool Init() override;

	void SetWVP(const std::shared_ptr<glm::mat4> pWVP);
	void SetTextureUnit(unsigned int TextureUnit);
	void SetDirectionalLight(const std::shared_ptr<DirectionalLight> pLight);

private:
	GLuint m_WVPLocation = 0xFFFFFFFF;
	GLuint m_samplerLocation = 0xFFFFFFFF;
	GLuint m_dirLightColorLocation = 0xFFFFFFFF;
	GLuint m_dirLightAmbientIntensityLocation = 0xFFFFFFFF;
};