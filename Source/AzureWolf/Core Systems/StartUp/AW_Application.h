#pragma once


//Gives the application access to the core systems
#include "../AW_CoreSystems.h"

//Gives the application access to the graphics library
#include "../../Renderer/AW_Graphics.h"

//Gives the application the ability to handle command arguments
#include "AW_Command.h"

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