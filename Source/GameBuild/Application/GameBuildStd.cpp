#include "GameBuildStd.h"


AW_WINDOW_APPLICATION(GameBuildStd);

GameBuildStd::GameBuildStd()
	:
	AW_GameApplication("Mint Tea", 0, 0, 800, 600,
        Float4(0.0f, 0.0f, 0.0f, 0.5f)),
        mTextColor(1.0f, 1.0f, 1.0f, 1.0f)
{
}
 
bool GameBuildStd::OnInitialize()
{
	if(!AW_GameApplication::OnInitialize())
	{
		return false;
	}
	return true;
}

void GameBuildStd::OnTerminate()
{
	AW_GameApplication::OnTerminate();
} 

void GameBuildStd::OnIdle()
{
}

bool GameBuildStd::OnKeyDown(unsigned char key, int x, int y)
{
	return true;
}