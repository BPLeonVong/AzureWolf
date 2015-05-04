#pragma once

#include "../../AzureWolf/AzureWolfStd.h"

class GameBuildStd : public AW_WinGameApplication
{
	
    AW_DECLARE_INITIALIZE;
    AW_DECLARE_TERMINATE;

public:
	GameBuildStd();

	virtual bool OnInitialize();
	virtual void OnTerminate();
	virtual void OnIdle();
	virtual bool OnKeyDown(unsigned char key, int x, int y);

	void SetKeySettings();

protected:
    Float4 mTextColor;

};
AW_REGISTER_INITIALIZE(GameBuildStd);
AW_REGISTER_TERMINATE(GameBuildStd);