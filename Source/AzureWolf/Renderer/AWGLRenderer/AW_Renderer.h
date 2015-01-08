#pragma once

#include "../RenderDevice/RenderInput.h"
#include "../AW_Graphics.h"


namespace AW
{
	
class RendererInput;
class RendererData;

	class Renderer
	{
	public:
		
		//void Initialize(int width, int height, Texture::Format colorFormat,
        //Texture::Format depthStencilFormat, int numMultisamples);
		
		
		Renderer (RenderInput& input, int width, int height,
        int numMultisamples);
	
	private:
	public:
		RendererData* mData;
		void RenderScene();
		void InitGL();

		//~Renderer ();


		//inline void SetClearColor(const Float4& clearColor);
	};
}
