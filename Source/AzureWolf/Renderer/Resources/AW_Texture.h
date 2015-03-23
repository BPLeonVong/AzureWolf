#pragma once

namespace AW
{
	class Texture
	{
	public:
		Texture(GLenum TextureTarget, const std::string& FileName);

		bool Load();

		void Bind(GLenum TextureUnity);

	private:
		std::string m_fileName;
		GLenum m_textureTarget;
		GLuint m_textureObj;

	};
}