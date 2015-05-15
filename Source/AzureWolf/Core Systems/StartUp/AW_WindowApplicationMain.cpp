#include "AzureWolfStd.h"
#include "AW_WindowApplication.h"

#include "../Utilities/camera.h"

#include "../../Core Systems/Utilities/CPractices/LinkedList.h"
#include "../../Core Systems/Utilities/CPractices/BST.h"
#include "../../Core Systems/Utilities/CPractices/Recursion.h"
#include "../../Core Systems/Utilities/CPractices/Structors.h"

using namespace std;
using namespace AW;

static bool gsIgnoreWindowDestroy = false;
static bool applicationRunning;

// ~~~ Window Procedure ~~~
LRESULT CALLBACK WndEventProc(HWND handle, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	WindowApplication* theApp = (WindowApplication*)Application::MYApplication;
	
	if(!theApp || !theApp->GetWinID())
	{
		return DefWindowProc(handle, message, wParam, lParam);
	}
	
	switch(message)
	{        
	case WM_KEYDOWN:
        {
            unsigned char key = (unsigned char)(char)wParam;
			
            // Get the cursor position in client coordinates.
            POINT point;
            GetCursorPos(&point);
            ScreenToClient(handle, &point);
            int xPos = (int)point.x;
            int yPos = (int)point.y;

            // Quit the application if the KEY_TERMINATE key is pressed.
            if (key == theApp->KEY_TERMINATE)
            {
                PostQuitMessage(0);
                return 0;
            }
			else if (key==theApp->KEY_LEFT_ARROW ||
				     key==theApp->KEY_DOWN_ARROW ||
					 key==theApp->KEY_RIGHT_ARROW ||
					 key==theApp->KEY_UP_ARROW)
			{
				theApp->OnSpecialKeyDown(key,xPos,yPos);
			}

            //theApp->OnKeyDown(key, xPos, yPos);
            return 0;
        }
	case WM_KEYUP:
		{
			  unsigned char key = (unsigned char)(char)wParam;
			
            // Get the cursor position in client coordinates.
            POINT point;
            GetCursorPos(&point);
            ScreenToClient(handle, &point);
            int xPos = (int)point.x;
            int yPos = (int)point.y;

            // Quit the application if the KEY_TERMINATE key is pressed.
            if (key == theApp->KEY_TERMINATE)
            {
                PostQuitMessage(0);
                return 0;
            }
			else if (key==theApp->KEY_LEFT_ARROW ||
				     key==theApp->KEY_DOWN_ARROW ||
					 key==theApp->KEY_RIGHT_ARROW ||
					 key==theApp->KEY_UP_ARROW)
			{
				theApp->OnSpecialKeyUp(key,xPos,yPos);
			}


            //theApp->OnKeyUp(key, xPos, yPos);
			return 0;
		}
	case WM_DESTROY:
        {
			applicationRunning = false;
            return 0;
		}
	case WM_CLOSE:
		{
			applicationRunning = false;
			return 0;
		}
	}

	return DefWindowProc(handle, message, wParam, lParam);
}


int WindowApplication::Main(int, char**)
{
	//Need to check System Resources
	//Detects instances of application, checks memory and storage space, calculates cpu, load game resources, load player prompts, create lua script manager, create event manager, load game settings (default), initialize renderer, create game logic and game view, sets the directory saves, preload certain resources
	//Check CPU Speed

	//Initialize Random Number Generator

	//Load programmer debugging options/tools

	//Initialize memory cache

	//Create window

	//Initialize audio system

	//Load player game settings and saved files

	//Create drawing surfaces

	//Performance initialization

	//Reference to the Application
	WindowApplication* theApp = (WindowApplication*)MYApplication;

	//Sets the Escape Key to Terminate Variable
	theApp->KEY_TERMINATE = WindowApplication::KEY_ESCAPE;

	//Testing C++ practices in console

	//Linked List Example
	/*PLinkedList pLLTemp;
	pLLTemp.Insert(3);
	pLLTemp.Insert(5);
	pLLTemp.Insert(7);
	pLLTemp.Display();
	pLLTemp.Delete(7);
	pLLTemp.Display();*/

	//Binary Search Tree Example
	/*PBST pBSTTemp;
	int TreeKeys[5] = { 4, 5, 10, 6, 3 };
	pBSTTemp.Display();
	for (int i = 0; i < 5; ++i)
	{
		pBSTTemp.Insert(TreeKeys[i]);
	}
	pBSTTemp.Display();*/

	//Recursion Example
	//PRecursion pRTemp;
	//pRTemp.Display();

	//Structor
	//{ B b(5); }
	//std::cout << std::endl;
	//std::cout << 22 / 5 * 3;
	//Check if the application was created
	if(!theApp->OnPrecreate())
	{
		return -1;
	}

	//Registering the Window Class
	static char sWindowClass[] = "Application Name";
	WNDCLASS wc = {};
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc   = WndEventProc;
    wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
    wc.lpszClassName = sWindowClass;

	if (!RegisterClass(&wc))
	{
		//Log an error
		return 0;
	}

	DWORD dwStyle;
    if (mAllowResize)
    {
        dwStyle = WS_OVERLAPPEDWINDOW;
    }
    else
    {
        dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    }

	//Rectangle of Game Screen
    RECT rect = { 0, 0, theApp->GetWidth()-1, theApp->GetHeight()-1 };

	//Calculate size of rectangle and style
    AdjustWindowRect(&rect, dwStyle, FALSE);


	//Creating the window
    HWND handle = CreateWindow(sWindowClass, theApp->GetWindowTitle(),
        dwStyle, theApp->GetXPosition(), theApp->GetYPosition(),
        rect.right - rect.left + 1, rect.bottom - rect.top + 1, 0, 0, 0, 0);

	if (handle == NULL)
	{
		printf("The window was unable to be built");
		//return 1;
	}


	//Save handle as 'int'
    theApp->SetWinID(PtrToInt(handle));

	//Use opengl
	input.mWindowHandle = handle;
	input.mPixelFormat = 0;
	input.mRendererDC = 0;
	input.mDisableVerticalSync = true;

	mRenderer = new0 Renderer(input, theApp->GetWidth(), theApp->GetHeight(), mNumMultisamples);

	if (mRenderer == NULL)
	{
		printf("The renderer was unable to be built");
		//return 1;
	}

	if(theApp->OnInitialize())
	{
        theApp->OnPreidle();
        ShowWindow(handle, SW_SHOW);
        UpdateWindow(handle);
		
		applicationRunning = true;

		while(applicationRunning)
		{
			MSG msg;
			if(PeekMessage(&msg,0,0,0,PM_REMOVE))
			{
				if(msg.message == WM_QUIT)
				{
					applicationRunning = false;
					continue;
				}
				   HACCEL accel = 0;

                if (!TranslateAccelerator(handle, accel, &msg))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
			}
            else
            {
                theApp->OnIdle();
            }
		}
	}

	theApp->OnTerminate();
	delete0(mRenderer);

	return 0;
}