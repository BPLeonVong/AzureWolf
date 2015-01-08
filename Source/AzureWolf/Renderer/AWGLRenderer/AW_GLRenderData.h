#pragma once

#include "../OpenGLRenderer/AWOpenGLRendererData.h"

namespace AW
{
	class AWGLRendererData : public RendererData
	{
	public:
		HWND mWindowHandle;
		HDC mWindowDC;
		HGLRC mWindowRC;
	};
}
