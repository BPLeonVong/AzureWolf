#pragma once

namespace AW
{
	class Texture
	{
	public:
		Texture(const char* pBuffer, size_t nBufferSize, int & nWidth, int & nHeight, int & nComponents);

		virtual ~Texture();

		void Bind(unsigned int unit);


	private:
		Texture(const Texture& otherTexture);
		void operator=(const Texture& otherTexture);

	private:
		std::string m_fileName;
		GLuint m_textureObj;

	};
}