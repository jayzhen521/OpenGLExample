#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Image::Image(std::string imageName)
	:m_name(imageName)
{
}

Image::~Image()
{
	stbi_image_free(m_data);
}

const unsigned char* Image::getData() const
{
	return m_data;
}

bool Image::load()
{
	m_data = stbi_load(m_name.c_str(), &m_columns, &m_rows, &m_channels, STBI_rgb_alpha);
	if (m_data != nullptr)
	{
		return true;
	}
	return false;
}

uint32_t Image::columns()
{
	return m_columns;
}

uint32_t Image::rows()
{
	return m_rows;
}
