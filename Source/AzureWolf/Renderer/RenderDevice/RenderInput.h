#pragma once

namespace AW
{
	class RenderInput
	{
	public:
		HWND mWindowHandle;
		HDC mRendererDC;
		int mPixelFormat;
		bool mDisableVerticalSync;
	};
}