#include <glm/gtc/matrix_transform.hpp>

#include "Pipeline.h"

Pipeline::Pipeline()
	:m_scale(glm::vec3()),
	m_rotateInfo(glm::vec3()),
	m_worldPos(glm::vec3()),
	m_transformation(glm::mat4())
{
}

void Pipeline::Scale(float ScaleX, float ScaleY, float ScaleZ)
{
	m_scale.x = ScaleX;
	m_scale.y = ScaleY;
	m_scale.z = ScaleZ;
}

void Pipeline::WorldPos(float x, float y, float z)
{
	m_worldPos.x = x;
	m_worldPos.y = y;
	m_worldPos.z = z;
}

void Pipeline::Rotate(float RotateX, float RotateY, float RotateZ)
{
	m_rotateInfo.x = RotateX;
	m_rotateInfo.y = RotateY;
	m_rotateInfo.z = RotateZ;
}

const glm::mat4* Pipeline::GetTrans()
{
	glm::mat4 rotateX, rotateY, rotateZ;
	rotateX = glm::rotate(rotateX, m_rotateInfo.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotateY = glm::rotate(rotateY, m_rotateInfo.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotateZ = glm::rotate(rotateZ, m_rotateInfo.z, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 scale;
	scale = glm::scale(scale, m_scale);

	glm::mat4 translate;
	translate = glm::translate(translate, m_worldPos);

	m_transformation = translate * scale * rotateX * rotateY * rotateZ;

	return &m_transformation;
}
