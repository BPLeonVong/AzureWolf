#include "AzureWolfStd.h"
#include "AW_WindowApplication.h"

#include <iostream>

using namespace std;
using namespace AW;

const int WindowApplication::KEY_ESCAPE = VK_ESCAPE;

static bool gsIgnoreWindowDestroy = false;

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
	case WM_CHAR:
        {
            unsigned char key = (unsigned char)(char)wParam;

            // Quit the application if the KEY_TERMINATE key is pressed.
            if (key == theApp->KEY_TERMINATE)
            {
                PostQuitMessage(0);
                return 0;
            }

            // Get the cursor position in client coordinates.
            POINT point;
            GetCursorPos(&point);
            ScreenToClient(handle, &point);
            int xPos = (int)point.x;
            int yPos = (int)point.y;

            theApp->OnKeyDown(key, xPos, yPos);
            return 0;
        }
	case WM_DESTROY:
        {
            // The DestroyWindow call when recreating the window for
            // multisampling causes the application to terminate.  It is
            // not clear why the same problem did not occur in WM4.
            if (!gsIgnoreWindowDestroy)
            {
                PostQuitMessage(0);
            }
            gsIgnoreWindowDestroy = false;
            return 0;
        }
	}

	return DefWindowProc(handle, message, wParam, lParam);
}


int WindowApplication::Main(int, char**)
{
	//Reference to the Application
	WindowApplication* theApp = (WindowApplication*)MYApplication;

	//Sets the Escape Key to Terminate Variable
	theApp->KEY_TERMINATE = WindowApplication::KEY_ESCAPE;

	//Check if the application was created
	if(!theApp->OnPrecreate())
	{
		return -1;
	}

	//Registering the Window Class
	static char sWindowClass[] = "Application Name";
    WNDCLASS wc;
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc   = WndEventProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = 0;
    wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
    wc.lpszClassName = sWindowClass;
    wc.lpszMenuName  = 0;

    RegisterClass(&wc);

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

	//Save handle as 'int'
    theApp->SetWinID(PtrToInt(handle));

	//Use opengl
	RenderInput input;
	input.mWindowHandle = handle;
	input.mPixelFormat = 0;
	input.mRendererDC = 0;
	input.mDisableVerticalSync = true;

	mRenderer = new0 Renderer(input, theApp->GetWidth(), theApp->GetHeight(), mNumMultisamples);
	
	if(theApp->OnInitialize())
	{
        theApp->OnPreidle();
        ShowWindow(handle, SW_SHOW);
        UpdateWindow(handle);
		
		bool applicationRunning = true;

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
				mRenderer->RenderScene();				//TEmp
			SwapBuffers(input.mRendererDC);				// Swap Buffers (Double Buffering)
            }

		}
	}

	theApp->OnTerminate();
	delete0(mRenderer);

	return 0;
}