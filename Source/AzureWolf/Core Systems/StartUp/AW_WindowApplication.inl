//Member Accesors
inline const char* WindowApplication::GetWindowTitle() const
{
	return mWindowTitle.c_str();
}

inline int WindowApplication::GetXPosition() const
{
	return mXPosition;
}

inline int WindowApplication::GetYPosition() const
{
	return mYPosition;
}

inline int WindowApplication::GetWidth () const
{
	return mWidth;
}
   
inline int WindowApplication::GetHeight () const
{
	return mHeight;
}

inline float WindowApplication::GetAspectRatio () const
{
    return ((float)mWidth)/(float)mHeight;
}

inline void WindowApplication::SetWinID (int windowID)
{
	mWindowID = windowID;
}

inline int WindowApplication::GetWinID () const
{
    return mWindowID;
}

inline const Renderer* WindowApplication::GetRenderer ()
{
    return mRenderer;
}

//Event call backs this is mainly for derived classes
inline bool WindowApplication::OnPrecreate()
{
	return true;
}

inline void WindowApplication::OnPreidle()
{
	//Clears all buffers
    //mRenderer->ClearBuffers();
}

inline void WindowApplication::OnDisplay()
{
}

inline void WindowApplication::OnIdle()
{ 
}

inline bool WindowApplication::OnKeyUp (unsigned char, int, int)
{
    return false;
}
/*
inline bool WindowApplication::OnSpecialKeyDown (int, int, int)
{
    return false;
}

inline bool WindowApplication::OnSpecialKeyUp (int, int, int)
{
    return false;
}*/

inline bool WindowApplication::OnMouseClick (int, int, int, int,
    unsigned int)
{
    return false;
}

inline bool WindowApplication::OnMotion (int, int, int, unsigned int)
{
    return false;
}

inline bool WindowApplication::OnPassiveMotion (int, int)
{
    return false;
}

inline bool WindowApplication::OnMouseWheel (int, int, int, unsigned int)
{
    return false;
}