#pragma once


#include "../AW_CoreSystems.h"
#include "../Utilities/DataTypes/AWFloat4.h"
#include "../../Renderer/AW_Graphics.h"
#include "../../Renderer/AWGLRenderer/AW_Renderer.h"
#include "AW_Command.h"

/*
#include "Wm5Core.h"
#include "Wm5Mathematics.h"
#include "Wm5Imagics.h"
#include "Wm5Physics.h"
#include "Wm5Graphics.h"
#include "Wm5Renderers.h"
#include "Wm5Command.h"
*/

namespace AW
{
	class AW_CORESYSTEM Application
	{
	protected:
		Application ();
	public:
		virtual ~Application ();
	
		static Application* MYApplication;

		static Command* TheCommand;

		static std::string DirPath;

		typedef int (*EntryPoint)(int, char**);
		static EntryPoint Run;
	};
}