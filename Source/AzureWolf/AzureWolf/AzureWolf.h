#pragma once 

#include "../Core Systems/StartUp/AW_WindowApplication.h"

//Construction, destruction, event callbacks, camera motion, object motion, base properties, managers

using namespace AW;

class AW_GameApplication : public WindowApplication
{
public:
	AW_GameApplication(const char* windowTitle, int xPosition, int yPosition,
        int width, int height, const Float4& clearColor);
	
	virtual bool OnInitialize();
	virtual void OnTerminate();
	virtual bool OnKeyDown(unsigned char key, int x, int y);

	virtual ~AW_GameApplication();
};