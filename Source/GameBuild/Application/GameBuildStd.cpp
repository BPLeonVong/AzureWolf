#include "GameBuildStd.h"


AW_WINDOW_APPLICATION(GameBuildStd);

GameBuildStd::GameBuildStd()
	:
	AW_WinGameApplication("Mint Tea", 0, 0, 800, 600,
        Float4(0.0f, 0.0f, 0.0f, 0.5f)),
        mTextColor(1.0f, 1.0f, 1.0f, 1.0f)
{
	
}
 
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

void GameBuildStd::OnIdle()
{
	if (MoveCamera())
	{

	}
}

bool GameBuildStd::OnKeyDown(unsigned char key, int x, int y)
{
	return true;
}

void SetKeySettings()
{
	//Set the keys to the in game settings
}