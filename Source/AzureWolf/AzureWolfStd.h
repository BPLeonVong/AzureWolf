#pragma once

//Maintains core corecomponents and is the precompiled header

#define WIN32_LEAN_AND_MEAN	

//Include Windows
#include <Windows.h>
#include <Windowsx.h>

#include <crtdbg.h>

//Check Version
#define		_VS2012_
#if			_MSC_VER < 1700
	#undef	_VS2012_
#endif

#pragma warning( disable : 4996 )

// C Runtime Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <mmsystem.h>

#include <algorithm>
#include <list>
#include <vector>
#include <queue>
#include <map>

#include <iostream>
#include <string>
#include <fstream>


#define GLEW_STATIC 1

//Include OpenGl
#include "glew.h"
#include <gl/glu.h>


//using std::shared_ptr<int> p1;
//using std:::weak_ptr;
//using std::static_pointer_cast;
//using std::tr1::dynamic_pointer_cast;

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
#include <tinyxml.h>
#include <FastDelegate.h>
#include <zlib.h>
#include <stb_image.h>


using fastdelegate::MakeDelegate;

//AW Personal Systems
#include "Core Systems/AW_CoreSystems.h"
//#include "Renderer/Graphics3D/geometry.h"

#include "AzureWolf/interfaces.h"


#include "AzureWolf/AzureWolf.h"
