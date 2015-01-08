#pragma once

//Maintains core corecomponents and is the precompiled header

#define WIN32_LEAN_AND_MEAN	

//Include Windows
#include <Windows.h>
#include <Windowsx.h>

#include <crtdbg.h>

//Check Version
#define		_VS2010_
#if			_MSC_VER < 1600
	#undef	_VS2010_
#endif

#pragma warning( disable : 4996 )

// C Runtime Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <mmsystem.h>

#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <map>

//Include OpenGl
#include <gl/glu.h>

using std::tr1::shared_ptr;
using std::tr1::weak_ptr;
using std::tr1::static_pointer_cast;
using std::tr1::dynamic_pointer_cast;

//Don't Copy Base Class
class DCTOR_UNCOPY
{
private:
	DCTOR_UNCOPY			(const DCTOR_UNCOPY& x);
	DCTOR_UNCOPY& operator= (const DCTOR_UNCOPY& x);
public:
	DCTOR_UNCOPY(){}
};

//3rd Party
#include "../3rd_Party/tinyxml_2_6_2/tinyxml.h"
#include "../3rd_Party/FastDelegate/FastDelegate.h"

using fastdelegate::MakeDelegate;

//AW Personal Systems
#include "Core Systems/AW_CoreSystems.h"
//#include "Renderer/Graphics3D/geometry.h"

#include "AzureWolf/interfaces.h"


#include "AzureWolf/AzureWolf.h"

/*
To Do List:
Actors Base Class
Component Base Class
Processes Base Class
Factory Creation Class
Logger
Templates
types
Environment directories
Memory type class
Pointer?
Application Base Class to set the screen
*/