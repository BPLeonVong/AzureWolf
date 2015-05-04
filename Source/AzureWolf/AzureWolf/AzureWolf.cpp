#include "AzureWolfStd.h"

#include "AzureWolf.h"


AW_WinGameApplication::AW_WinGameApplication(const char* windowTitle, int xPosition, int yPosition,
        int width, int height, const Float4& clearColor)
		:
		WindowApplication(windowTitle,xPosition,yPosition,width,height,clearColor)
{

}

AW_WinGameApplication::~AW_WinGameApplication()
{
}

bool AW_WinGameApplication::OnInitialize()
{
	if (!WindowApplication::OnInitialize())
    {
        return false;
    }
	return true;
}

void AW_WinGameApplication::OnTerminate()
{
    WindowApplication::OnTerminate();
}

bool AW_WinGameApplication::OnKeyDown(unsigned char key, int x, int y)
{
	return true;
}