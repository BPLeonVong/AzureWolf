#pragma once

namespace AW
{
	class Texture
	{
	public:
		enum Format
		{       
			TF_NONE,

			// Small-bit color formats.
			TF_R5G6B5,
			TF_A1R5G5B5,
			TF_A4R4G4B4,

			// 8-bit integer formats.
			TF_A8,
			TF_L8,
			TF_A8L8,
			TF_R8G8B8,
			TF_A8R8G8B8,
			TF_A8B8G8R8,

			// 16-bit integer formats.
			TF_L16,
			TF_G16R16,
			TF_A16B16G16R16,

			// 16-bit floating-point formats ('half float' channels).
			TF_R16F,
			TF_G16R16F,
			TF_A16B16G16R16F,

			// 32-bit floating-point formats ('float' channels).
			TF_R32F,
			TF_G32R32F,
			TF_A32B32G32R32F,

			// DXT compressed formats.
			TF_DXT1,
			TF_DXT3,
			TF_DXT5,

			// Depth-stencil format.
			TF_D24S8,
			TF_QUANTITY
		}; 

		enum Type
		{
			TT_1D,
			TT_2D,
			TT_3D,
			TT_CUBE,
			TT_QUANTITY
		};

		//Max Mipmap Levels for Texture 4096x4096 has 13 levels
		enum
		{
			MM_MAX_MIPMAP_LEVELS = 16
		};
	protected:
		   // Texture (Format tformat, Type type, Buffer::Usage usage, int numLevels);
	public:
		//virtual ~Texture ();
	protected:
		Format mFormat;
		Type mType;
		//Buffer::Usage mUsage;
		int mNumLevels;
	public:
		//static Texture* LoadWMTF (const std::string& name,
        //int mode = FileIO::FM_DEFAULT_READ);

		//void SaveWMTF (const std::string& name,
        //int mode = FileIO::FM_DEFAULT_WRITE);
	};
}