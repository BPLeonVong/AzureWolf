#pragma once

//Gives the application access to the application base class
#include "AW_Application.h"

//Allows the application to set the initializers
#include "../Utilities/AWInit.h"

//Includes camera system to the application
#include "../Utilities/camera.h"

namespace AW
{

class WindowApplication : public Application
{
protected:
	//The Application Properties
	WindowApplication(const char* windowTitle, int xPosition,
		int yPosition, int width, int height, const Float4& clearColor);
public:

	//Destructor
    virtual ~WindowApplication ();
	//This is found in AW_WindowApplicationMain.cpp and is where the entry point
    virtual int Main (int numArguments, char** arguments);
	
	//Member Accesors
    inline const char*	GetWindowTitle () const;		//Get window title from mWindowTitle
	inline int			GetXPosition () const;			//Get x position from mXPosition
	inline int			GetYPosition () const;			//Get y position from mYPosition
    inline int			GetWidth () const;				//Get width from mWidth
    inline int			GetHeight () const;				//Get height from mHeight
    inline float		GetAspectRatio () const;		//Get aspect ratio 
    inline void			SetWinID (int windowID);		//Set the window ID
    inline int			GetWinID () const;				//Get the windowID
    inline const		Renderer* GetRenderer ();		//Get the renderer

	//Event callbacks these can be overrided by dervied classes
	virtual bool OnInitialize();						//Defined in the cpp file
	virtual void OnTerminate();							//Defined in the cpp file
    virtual void OnMove (int x, int y);					//Defined in the cpp file
    virtual void OnResize (int width, int height);		//Defined in the cpp file
	
	//Defined in the .inls and are meant for derived classes
    inline virtual bool OnPrecreate ();					
	inline virtual void OnPreidle();
    inline virtual void OnDisplay ();
	inline virtual void OnIdle();

	virtual bool OnKeyDown (unsigned char key, int x, int y);

	//Defined in .inl
    inline virtual bool OnKeyUp (unsigned char key, int x, int y);
    inline virtual bool OnSpecialKeyDown (int key, int x, int y);
    inline virtual bool OnSpecialKeyUp (int key, int x, int y);
    inline virtual bool OnMouseClick (int button, int state, int x, int y, unsigned int modifiers);
    inline virtual bool OnMotion (int button, int x, int y, unsigned int modifiers);
    inline virtual bool OnPassiveMotion (int x, int y);
    inline virtual bool OnMouseWheel (int delta, int x, int y, unsigned int modifiers);

	//Mouse Position
	void SetMousePosition (int x, int y);
    void GetMousePosition (int& x, int& y) const;

	//Font information
	int GetStringWidth (const char* text) const;
    int GetCharacterWidth (const char character) const;
    int GetFontHeight () const;

	//Key Identifiers, classes must imlement the keys after deriving
	int KEY_TERMINATE;				//Predefined as KEY_ESCAPE
    static const int KEY_ESCAPE;
    static const int KEY_LEFT_ARROW;
    static const int KEY_RIGHT_ARROW;
    static const int KEY_UP_ARROW;
    static const int KEY_DOWN_ARROW;
    static const int KEY_HOME;
    static const int KEY_END;
    static const int KEY_PAGE_UP;
    static const int KEY_PAGE_DOWN;
    static const int KEY_INSERT;
    static const int KEY_DELETE;
    static const int KEY_F1;
    static const int KEY_F2;
    static const int KEY_F3;
    static const int KEY_F4;
    static const int KEY_F5;
    static const int KEY_F6;
    static const int KEY_F7;
    static const int KEY_F8;
    static const int KEY_F9;
    static const int KEY_F10;
    static const int KEY_F11;
    static const int KEY_F12;
    static const int KEY_BACKSPACE;
    static const int KEY_TAB;
    static const int KEY_ENTER;
    static const int KEY_RETURN;

// Keyboard modifiers.
    static const int KEY_SHIFT;
    static const int KEY_CONTROL;
    static const int KEY_ALT;
    static const int KEY_COMMAND;

    // Mouse buttons.
    static const int MOUSE_LEFT_BUTTON;
    static const int MOUSE_MIDDLE_BUTTON;
    static const int MOUSE_RIGHT_BUTTON;

    // Mouse state.
    static const int MOUSE_UP;
    static const int MOUSE_DOWN;

    // Mouse modifiers.
    static const int MODIFIER_CONTROL;
    static const int MODIFIER_LBUTTON;
    static const int MODIFIER_MBUTTON;
    static const int MODIFIER_RBUTTON;
    static const int MODIFIER_SHIFT;

protected:
    static int Run (int numArguments, char** arguments);

	//Window Parameters in the constructor
    std::string mWindowTitle;
    int mXPosition, mYPosition, mWidth, mHeight;
    Float4 mClearColor;
    bool mAllowResize;

	//Handle of Window
    int mWindowID;

    //Texture::Format mColorFormat;
    //Texture::Format mDepthStencilFormat;
    int mNumMultisamples;
    Renderer* mRenderer;

	//Performance measurements
    void ResetTime ();
    void MeasureTime ();
    void UpdateFrameCount ();
    void DrawFrameRate (int x, int y, const Float4& color);

    double mLastTime, mAccumulatedTime, mFrameRate;
    int mFrameCount, mAccumulatedFrameCount, mTimer, mMaxTimer;

	//Key Presses temp here
	bool mUArrowPressed;
	bool mRArrowPressed;
	bool mDArrowPressed;
	bool mLArrowPressed;

	//Camera moving temp
	Camera *mCamera;
	virtual bool MoveCamera();
    virtual void MoveForward();
    virtual void MoveBackward();
    virtual void MoveLeft();
    virtual void MoveRight();
};

#include "AW_WindowApplication.inl"

#define AW_WINDOW_APPLICATION(classname) \
AW_IMPLEMENT_INITIALIZE(classname); \
AW_IMPLEMENT_TERMINATE(classname); \
\
void classname::Initialize () \
{ \
    Application::Run = &WindowApplication::Run; \
    MYApplication = new0 classname(); \
} \
\
void classname::Terminate () \
{ \
    delete0(MYApplication); \
}

}

