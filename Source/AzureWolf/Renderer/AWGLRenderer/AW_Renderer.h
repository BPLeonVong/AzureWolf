#pragma once

#include "../RenderDevice/RenderInput.h"
#include "../AW_Graphics.h"
#include "../../Core Systems/Utilities/camera.h"


namespace AW
{
	
class RendererInput;
class RendererData;

	class Renderer
	{
	public:
		
		//void Initialize(int width, int height, Texture::Format colorFormat,
        //Texture::Format depthStencilFormat, int numMultisamples);
		
		//Access Camera State
		inline void SetCamera (Camera* camera);
		inline Camera* GetCamera ();

		Renderer (RenderInput& input, int width, int height,
        int numMultisamples);
	
	private:
		GLenum IGLEW;
		GLuint ISHADEPROGRAM;
		Camera* mCamera;
	public:
		RendererData* mData;
		void RenderScene();
		void InitGL();

		void CompileShaders();


		~Renderer ();


		//inline void SetClearColor(const Float4& clearColor);
	};
	#include "AW_Renderer.inl"
}
