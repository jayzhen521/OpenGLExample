#include <glm/gtc/matrix_transform.hpp>

#include "Pipeline.h"

Pipeline::Pipeline()
	:m_scale(glm::vec3(1.0f, 1.0f, 1.0f)),
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

void Pipeline::SetPerspectiveProj(float fov, float width, float height, float zNear, float zFar)
{
	m_persProj = {fov, width, height, zNear, zFar};
}

void Pipeline::SetCamera(std::shared_ptr<Camera> pCamera)
{
	m_pCamera = pCamera;
}

const glm::mat4* Pipeline::GetTrans()
{
	glm::mat4 rotateX = glm::mat4(1.0), rotateY = glm::mat4(1.0), rotateZ = glm::mat4(1.0);
	rotateX = glm::rotate(rotateX, m_rotateInfo.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotateY = glm::rotate(rotateY, m_rotateInfo.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotateZ = glm::rotate(rotateZ, m_rotateInfo.z, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 scale = glm::mat4(1.0);
	scale = glm::scale(scale, m_scale);

	glm::mat4 translate = glm::mat4(1.0);
	translate = glm::translate(translate, m_worldPos);

	glm::mat4 cameraTranslate = glm::mat4(1.0f);
	//glm::lookAt the second parameter is target point, not direction.
	cameraTranslate = glm::lookAt(m_pCamera->GetPos(), m_pCamera->GetTarget() + m_pCamera->GetPos(), m_pCamera->GetUp());

	glm::mat4 persProj = glm::mat4(1.0f);
	persProj = glm::perspective(m_persProj.fov, m_persProj.width/m_persProj.height, m_persProj.zNear, m_persProj.zFar);

	m_transformation = persProj * cameraTranslate * translate * scale * rotateX * rotateY * rotateZ;

	return &m_transformation;
}
