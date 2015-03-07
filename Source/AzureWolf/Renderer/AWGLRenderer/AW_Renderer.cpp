#include "AzureWolfStd.h"

#include "AW_Renderer.h"
#include "AW_GLRenderData.h"
#include "../../Core Systems/Utilities/math_3d.h"
#include "../../Core Systems/Utilities/pipeline.h"
#include "../../Core Systems/Utilities/camera.h"
#include "../../Core Systems/FileIO/AW_FileIO.h"


using namespace AW;
using namespace std;

const char* pVSFileName = "../AzureWolf/Renderer/Shader/shader.vs";
const char* pFSFileName = "../AzureWolf/Renderer/Shader/shader.fs";

//GLfloat	rtri;				// Angle For The Triangle ( NEW )
//GLfloat	rquad;				// Angle For The Quad ( NEW )
	
GLuint VBO;						//Temp
GLuint IBO;

GLuint gScaleLocation;

Renderer::Renderer(RenderInput& input, int width, int height,
        int numMultisamples)
{
	//Creates Render Data and assign it to mData and set the input handle/dc to data
	AWGLRendererData* data = new0 AWGLRendererData();
	mData = data;
	data->mWindowHandle = input.mWindowHandle;
	data->mWindowDC = ::GetDC(input.mWindowHandle);

	//Sets the input.rendererDC to the data DC
	input.mRendererDC = data->mWindowDC;

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
				  PFD_SUPPORT_OPENGL | 
				  PFD_DOUBLEBUFFER;
		          //PFD_GENERIC_ACCELERATED|
	
    // colorFormat is ignored, create 32-bit RGBA buffer.
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    // depthStencilFormat is ignored, create 24-8 depthstencil buffer.
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
	
	input.mPixelFormat = ChoosePixelFormat(data->mWindowDC, &pfd);
	SetPixelFormat(data->mWindowDC,input.mPixelFormat,&pfd);
	data->mWindowRC = wglCreateContext(data->mWindowDC);
	wglMakeCurrent(data->mWindowDC,data->mWindowRC); 
	
	ShowWindow(input.mWindowHandle,SW_SHOW);						// Show The Window
	SetForegroundWindow(input.mWindowHandle);						// Slightly Higher Priority
	SetFocus(input.mWindowHandle);								// Sets Keyboard Focus To The Window

	//glViewport(0,0,width,height);						// Reset The Current Viewport

	//glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	//glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	//glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	//glLoadIdentity();									// Reset The Modelview Matrix

	InitGL();

	
    Vector3f Vertices[4];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(0.0f, -1.0f, 1.0f);
    Vertices[2] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);
    
 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	
    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 1, 2 };

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	
	CompileShaders();
}


void Renderer::InitGL(GLvoid)							// All Setup For OpenGL Goes Here
{
	IGLEW = glewInit();

	if(IGLEW != GLEW_OK)
	{
		assertion(false,"Rip");
	}

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
}



void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);
	
    const GLchar* p[1];
    GLint Lengths[1];

    p[0] = pShaderText;
    Lengths[0]= strlen(pShaderText);

	glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);
	
	GLint success = 0;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, sizeof(InfoLog), NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	glAttachShader(ShaderProgram, ShaderObj);
}


void Renderer::CompileShaders()
{
    ISHADEPROGRAM = glCreateProgram();
	
    if (ISHADEPROGRAM == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
   }


    string vs, fs;
	
    if (!fRead(pVSFileName, vs)) {
        exit(1);
    };

    if (!fRead(pFSFileName, fs)) {
        exit(1);
    };
    AddShader(ISHADEPROGRAM, vs.c_str(), GL_VERTEX_SHADER);
    AddShader(ISHADEPROGRAM, fs.c_str(), GL_FRAGMENT_SHADER);
	
	
	glLinkProgram(ISHADEPROGRAM);
	
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

	glGetProgramiv(ISHADEPROGRAM, GL_LINK_STATUS, &Success);
	if (Success == 0) 
	{
		glGetProgramInfoLog(ISHADEPROGRAM, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	glValidateProgram(ISHADEPROGRAM);
    glGetProgramiv(ISHADEPROGRAM, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ISHADEPROGRAM, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

	gScaleLocation = glGetUniformLocation(ISHADEPROGRAM, "gScale");
    glUseProgram(ISHADEPROGRAM);
}
/*
static void SpecialKeyboardCB(int Key, int x, int y)
{
    GameCamera.OnKeyboard(Key);
}*/

void Renderer::RenderScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	
    static float Scale = 0.0f;
	
    Scale += 0.1f;
	
    Pipeline p;
    p.Rotate(0.0f, Scale, 0.0f);
    p.WorldPos(0.0f, 0.0f, 3.0f);
    Vector3f CameraPos(0.0f, 0.0f, -3.0f);
    Vector3f CameraTarget(0.0f, 0.0f, 2.0f);
    Vector3f CameraUp(0.0f, 1.0f, 0.0f);
    p.SetCamera(CameraPos, CameraTarget, CameraUp);

	//p.SetCamera(GameCamera.GetPos(), GameCamera.GetTarget(), GameCamera.GetUp());
    
    p.SetPerspectiveProj(30.0f, 800, 600, 1.0f, 100.0f);

    glUniformMatrix4fv(gScaleLocation, 1, GL_TRUE, (const GLfloat*)p.GetTrans());

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
	

	/*
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(rtri,0.0f,1.0f,0.0f);						// Rotate The Triangle On The Y axis ( NEW )
	glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Front)
		glColor3f(0.0f,1.0f,0.0f);						// Green
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Left Of Triangle (Front)
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Right Of Triangle (Front)
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Right)
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Left Of Triangle (Right)
		glColor3f(0.0f,1.0f,0.0f);						// Green
		glVertex3f( 1.0f,-1.0f, -1.0f);					// Right Of Triangle (Right)
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Back)
		glColor3f(0.0f,1.0f,0.0f);						// Green
		glVertex3f( 1.0f,-1.0f, -1.0f);					// Left Of Triangle (Back)
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f(-1.0f,-1.0f, -1.0f);					// Right Of Triangle (Back)
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Left)
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Left Of Triangle (Left)
		glColor3f(0.0f,1.0f,0.0f);						// Green
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Right Of Triangle (Left)
	glEnd();											// Done Drawing The Pyramid

	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(1.5f,0.0f,-7.0f);						// Move Right 1.5 Units And Into The Screen 7.0
	glRotatef(rquad,1.0f,1.0f,1.0f);					// Rotate The Quad On The X axis ( NEW )
	glBegin(GL_QUADS);									// Draw A Quad
		glColor3f(0.0f,1.0f,0.0f);						// Set The Color To Green
		glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Right Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Bottom Left Of The Quad (Top)
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Bottom Right Of The Quad (Top)
		glColor3f(1.0f,0.5f,0.0f);						// Set The Color To Orange
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Top Right Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Top Left Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Left Of The Quad (Bottom)
		glVertex3f( 1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Bottom)
		glColor3f(1.0f,0.0f,0.0f);						// Set The Color To Red
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Front)
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Front)
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Front)
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Front)
		glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Yellow
		glVertex3f( 1.0f,-1.0f,-1.0f);					// Top Right Of The Quad (Back)
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Top Left Of The Quad (Back)
		glVertex3f(-1.0f, 1.0f,-1.0f);					// Bottom Left Of The Quad (Back)
		glVertex3f( 1.0f, 1.0f,-1.0f);					// Bottom Right Of The Quad (Back)
		glColor3f(0.0f,0.0f,1.0f);						// Set The Color To Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Left)
		glVertex3f(-1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Left)
		glColor3f(1.0f,0.0f,1.0f);						// Set The Color To Violet
		glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Right Of The Quad (Right)
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Right)
	glEnd();											// Done Drawing The Quad

	rtri+=0.2f;											// Increase The Rotation Variable For The Triangle ( NEW )
	rquad-=0.15f;										// Decrease The Rotation Variable For The Quad ( NEW )										// Done Drawing The Quad*/
}

Renderer::~Renderer ()
{
}
/*
inline void Renderer::SetClearColor(const Float4& clearColor)
{
}*/
