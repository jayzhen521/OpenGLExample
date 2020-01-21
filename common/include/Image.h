#pragma once

#include <cstdint>
#include <string>

/*
 *memory was not released after texture generating.
 */
class Image
{
public:
	Image(std::string imageName);
	~Image();

	const unsigned char* getData() const;
	bool load();
	uint32_t columns();
	uint32_t rows();

private:
	std::string m_name = "";

	unsigned char* m_data = nullptr;

	int m_columns = 0;
	int m_rows = 0;
	int m_channels = 0;
};