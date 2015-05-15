#include "GameBuildStd.h"

AW_WINDOW_APPLICATION(GameBuildStd);

//Initialize window
GameBuildStd::GameBuildStd()
	:
	AW_WinGameApplication("Game Application", 0, 0, 800, 600,
        Float4(0.0f, 0.0f, 0.0f, 0.5f)),
        mTextColor(1.0f, 1.0f, 1.0f, 1.0f)
{
	
}
 
//Initialized after window is made
bool GameBuildStd::OnInitialize()
{
	if (!AW_WinGameApplication::OnInitialize())
	{
		return false;
	}
	return true;
}

void GameBuildStd::OnTerminate()
{
	AW_WinGameApplication::OnTerminate();
} 

//Game Loop
void GameBuildStd::OnIdle()
{
	//Check Timer

	//Update Camera
	if (MoveCamera())
	{

	}

	//Update GameObjects

	//Update renderer
	//draw pre objects,clear buffers, draw special effects, draw post objects, draw buffer
	mRenderer->ClearBuffers();
	mRenderer->RenderScene();
	mRenderer->DisplayColorBuffer();

	//Update fps displayed
}

bool GameBuildStd::OnKeyDown(unsigned char key, int x, int y)
{
	return true;
}

void SetKeySettings()
{
	//Set the keys to the in game settings
}