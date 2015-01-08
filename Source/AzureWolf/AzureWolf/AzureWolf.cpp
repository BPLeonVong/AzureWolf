#include "AzureWolfStd.h"

#include "AzureWolf.h"


AW_GameApplication::AW_GameApplication(const char* windowTitle, int xPosition, int yPosition,
        int width, int height, const Float4& clearColor)
		:
		WindowApplication(windowTitle,xPosition,yPosition,width,height,clearColor)
{

}

AW_GameApplication::~AW_GameApplication()
{
}

bool AW_GameApplication::OnInitialize()
{
	if (!WindowApplication::OnInitialize())
    {
        return false;
    }
	return true;
}

void AW_GameApplication::OnTerminate()
{
    WindowApplication::OnTerminate();
}

bool AW_GameApplication::OnKeyDown(unsigned char key, int x, int y)
{
	return true;
}