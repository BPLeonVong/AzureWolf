#pragma once 

//Includes the base Window Application and makes it a Generic Title
#include "../Core Systems/StartUp/AW_WindowApplication.h"

//Construction, destruction, event callbacks, camera motion, object motion, base properties, managers

using namespace AW;

class AW_WinGameApplication : public WindowApplication
{
public:
	AW_WinGameApplication(const char* windowTitle, int xPosition, int yPosition,
        int width, int height, const Float4& clearColor);
	
	virtual bool OnInitialize();
	virtual void OnTerminate();
	virtual bool OnKeyDown(unsigned char key, int x, int y);

	virtual ~AW_WinGameApplication();
};