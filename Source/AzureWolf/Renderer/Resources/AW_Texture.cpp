#include "AzureWolfStd.h"
#include "AW_Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>


using namespace AW;

Texture::Texture(const char* pBuffer, size_t nBufferSize, int & nWidth, int & nHeight, int & nComponents)
{
	stbi_uc* pTextureData = stbi_load_from_memory((const stbi_uc*)pBuffer, nBufferSize, &nWidth, &nHeight, &nComponents, 0);
	if (pTextureData)
	{
		char* pCopy = new0 char[nWidth * nHeight * nComponents];
		memcpy(pCopy, pTextureData, sizeof(const char) * nWidth * nHeight * nComponents);
		stbi_image_free(pTextureData);
	}
	//int width, height, numComponents;
	//unsigned char* imageData = stbi_load(FileName.c_str(), &width, &height, &numComponents,4);

	//if (imageData == nullptr)
		//std::cerr << "Texture Loaded failed " << FileName.c_str() << std::endl;

	//glGenTextures(1, &m_textureObj);
	//glBindTexture(GL_TEXTURE_2D, m_textureObj);

	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//	glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);


}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureObj);
}

void Texture::Bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_textureObj);
}
