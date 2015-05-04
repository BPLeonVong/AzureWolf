#include "AzureWolfStd.h"
#include "AW_WindowApplication.h"

//Key Identifiers, classes must imlement the keys after deriving
const int WindowApplication::KEY_ESCAPE = VK_ESCAPE;
const int WindowApplication::KEY_LEFT_ARROW = VK_LEFT;
const int WindowApplication::KEY_RIGHT_ARROW = VK_RIGHT;
const int WindowApplication::KEY_UP_ARROW = VK_UP;
const int WindowApplication::KEY_DOWN_ARROW = VK_DOWN;
const int WindowApplication::KEY_HOME = VK_HOME;
const int WindowApplication::KEY_END = VK_END;
const int WindowApplication::KEY_PAGE_UP = VK_PRIOR;
const int WindowApplication::KEY_PAGE_DOWN = VK_NEXT;
const int WindowApplication::KEY_INSERT = VK_INSERT;
const int WindowApplication::KEY_DELETE = VK_DELETE;
const int WindowApplication::KEY_F1 = VK_F1;
const int WindowApplication::KEY_F2 = VK_F2;
const int WindowApplication::KEY_F3 = VK_F3;
const int WindowApplication::KEY_F4 = VK_F4;
const int WindowApplication::KEY_F5 = VK_F5;
const int WindowApplication::KEY_F6 = VK_F6;
const int WindowApplication::KEY_F7 = VK_F7;
const int WindowApplication::KEY_F8 = VK_F8;
const int WindowApplication::KEY_F9 = VK_F9;
const int WindowApplication::KEY_F10 = VK_F10;
const int WindowApplication::KEY_F11 = VK_F11;
const int WindowApplication::KEY_F12 = VK_F12;
const int WindowApplication::KEY_BACKSPACE = VK_BACK;
const int WindowApplication::KEY_TAB = VK_TAB;
const int WindowApplication::KEY_ENTER = VK_RETURN;
const int WindowApplication::KEY_RETURN = VK_RETURN;

// Keyboard modifiers.
const int WindowApplication::KEY_SHIFT = VK_SHIFT;
const int WindowApplication::KEY_CONTROL = VK_CONTROL;
const int WindowApplication::KEY_ALT = 0; //Nothing
const int WindowApplication::KEY_COMMAND = 0; //Nothing

// Mouse buttons.
const int WindowApplication::MOUSE_LEFT_BUTTON = 0;
const int WindowApplication::MOUSE_MIDDLE_BUTTON = 1;
const int WindowApplication::MOUSE_RIGHT_BUTTON = 2;

// Mouse state.
const int WindowApplication::MOUSE_UP = 0;
const int WindowApplication::MOUSE_DOWN = 1;

// Mouse modifiers.
const int WindowApplication::MODIFIER_CONTROL = MK_CONTROL;
const int WindowApplication::MODIFIER_LBUTTON = MK_LBUTTON;
const int WindowApplication::MODIFIER_MBUTTON = MK_MBUTTON;
const int WindowApplication::MODIFIER_RBUTTON = MK_RBUTTON;
const int WindowApplication::MODIFIER_SHIFT = MK_SHIFT;

using namespace AW;

WindowApplication::WindowApplication (const char* windowTitle, int xPosition,
    int yPosition, int width, int height, const Float4& clearColor)
    :
    mWindowTitle(windowTitle),
    mXPosition(xPosition),
    mYPosition(yPosition),
    mWidth(width),
    mHeight(height),
    mClearColor(clearColor),
    mAllowResize(true),
    mWindowID(0),
    mRenderer(0),
    mLastTime(-1.0),
    mAccumulatedTime(0.0),
    mFrameRate(0.0),
    mFrameCount(0),
    mAccumulatedFrameCount(0),
    mTimer(30),
    mMaxTimer(30)
{
	 mUArrowPressed = false;
	 mRArrowPressed = false;
	 mDArrowPressed = false;
	 mLArrowPressed = false;
    //ThePath = WM5Path + std::string(windowTitle) + "/";

    // NOTE.  The derived-class constructors may override these settings.
    //mColorFormat = Texture::TF_A8R8G8B8;
    //mDepthStencilFormat = Texture::TF_D24S8;
    mNumMultisamples = 0;
}

//Destructor
WindowApplication::~WindowApplication ()
{
}


int WindowApplication::Run (int numArguments, char** arguments)
{
    WindowApplication* theApp = (WindowApplication*)MYApplication;
    return theApp->Main(numArguments, arguments);
}

bool WindowApplication::OnInitialize ()
{
	//This is called in the AW_WindowApplicationMain after window is created
//    mRenderer->SetClearColor(mClearColor);
	mCamera = new0 Camera();
	mRenderer->SetCamera(mCamera);
    return true;
}

//Definition of terminate function
void WindowApplication::OnTerminate ()
{
}

//Definition of move function
void WindowApplication::OnMove (int x, int y)
{
    mXPosition = x;
    mYPosition = y;
}

//Definition of resize function
void WindowApplication::OnResize (int width, int height)
{
    if (width > 0 && height > 0)
    {
        if (mRenderer)
        {
        //    mRenderer->Resize(width, height);
        }

        mWidth = width;
        mHeight = height;
    }
}

//On Key Down
bool WindowApplication::OnKeyDown (unsigned char key, int, int)
{
    if (key == '?')
    {
        ResetTime();
        return true;
    };

    return false;
}

// Performance measurements.
void WindowApplication::ResetTime ()
{
    mLastTime = -1.0;
}

void WindowApplication::MeasureTime ()
{
    if (mLastTime == -1.0)
    {
        mLastTime = GetTimeInSeconds();
        mAccumulatedTime = 0.0;
        mFrameRate = 0.0;
        mFrameCount = 0;
        mAccumulatedFrameCount = 0;
        mTimer = mMaxTimer;
    }

    if (--mTimer == 0)
    {
        double dCurrentTime = GetTimeInSeconds();
        double dDelta = dCurrentTime - mLastTime;
        mLastTime = dCurrentTime;
        mAccumulatedTime += dDelta;
        mAccumulatedFrameCount += mFrameCount;
        mFrameCount = 0;
        mTimer = mMaxTimer;
    }
}

void WindowApplication::UpdateFrameCount ()
{
    ++mFrameCount;
}

void WindowApplication::DrawFrameRate (int x, int y, const Float4& color)
{
    if (mAccumulatedTime > 0.0)
    {
        mFrameRate = mAccumulatedFrameCount/mAccumulatedTime;
    }
    else
    {
        mFrameRate = 0.0;
    }

    char message[256];
    sprintf(message, "fps: %.1lf", mFrameRate);
//    mRenderer->Draw(x, y, color, message);
}

bool WindowApplication::OnSpecialKeyDown(int key,int,int)
{
	if (key == KEY_UP_ARROW)
	{
		mUArrowPressed = true;
		return true;
	}
	if (key == KEY_RIGHT_ARROW)
	{
		mRArrowPressed = true;
		return true;
	}
	if (key == KEY_DOWN_ARROW)
	{
		mDArrowPressed = true;
		return true;
	}
	if (key == KEY_LEFT_ARROW)
	{
		mLArrowPressed = true;
		return true;
	}
	return false;
}

bool WindowApplication::OnSpecialKeyUp(int key,int,int)
{
	if (key == KEY_UP_ARROW)
	{
		mUArrowPressed = false;
		return true;
	}
	if (key == KEY_RIGHT_ARROW)
	{
		mRArrowPressed = false;
		return true;
	}
	if (key == KEY_DOWN_ARROW)
	{
		mDArrowPressed = false;
		return true;
	}
	if (key == KEY_LEFT_ARROW)
	{
		mLArrowPressed = false;
		return true;
	}
	return false;
}

bool WindowApplication::MoveCamera()
{
	bool bCameraMove=false;
	if (mUArrowPressed)
	{
		MoveForward();
		bCameraMove = true;
	}
	if (mRArrowPressed)
	{
		MoveRight();
		bCameraMove = true;
	}
	if (mDArrowPressed)
	{
		MoveBackward();
		bCameraMove = true;
	}
	if (mLArrowPressed)
	{
		MoveLeft();
		bCameraMove = true;
	}
	return bCameraMove;
}

void WindowApplication::MoveForward()
{
	mCamera->MoveUp();
}
void WindowApplication::MoveRight()
{
	mCamera->MoveRight();
}
void WindowApplication::MoveBackward()
{
	mCamera->MoveDown();
}
void WindowApplication::MoveLeft()
{
	mCamera->MoveLeft();
}