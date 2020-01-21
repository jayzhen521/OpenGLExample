#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

typedef glm::vec3 Position;
typedef glm::vec2 TexCoord;

typedef uint32_t Index;

class Vertex
{
public:
	Position m_position;
	TexCoord m_texCoord;
};