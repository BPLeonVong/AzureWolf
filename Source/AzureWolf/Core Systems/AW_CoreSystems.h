#pragma once

#include "Core Systems\Debugging\Logger.h"
#include "Core Systems\Utilities\templates.h"
#include "Core Systems\Utilities\types.h"

#include "Core Systems\Memory\AW_Memory.h"

#include "Core Systems\Time\AWTime.h"

#if defined(AW_CORE_DLL_EXPORT)
    #define AW_CORESYSTEM __declspec(dllexport)
#elif defined(AW_CORE_DLL_IMPORT)
    #define AW_CORESYSTEM __declspec(dllimport)
#else
    #define AW_CORESYSTEM
#endif
