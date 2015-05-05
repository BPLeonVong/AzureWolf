#include "AzureWolfStd.h"

#include "AW_Renderer.h"
#include "AW_GLRenderData.h"
#include "../../Core Systems/Utilities/math_3d.h"
#include "../../Core Systems/Utilities/pipeline.h"
#include "../../Core Systems/Utilities/camera.h"
#include "../../Core Systems/FileIO/AW_FileIO.h"

#include "../Resources/AW_Texture.h"


using namespace AW;
using namespace std;

const char* pVSFileName = "../AzureWolf/Renderer/Shader/shader.vs";
const char* pFSFileName = "../AzureWolf/Renderer/Shader/shader.fs";
const char* pVSFileName2 = "shader.vs";
const char* pFSFileName2 = "shader.fs";

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

	//Texture texture("tempBackground.jpg");
	//texture.Bind(0);
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
		if (!fRead(pVSFileName2, vs)) {
			printf("Shader was unable to load");
		};
    };

	if (!fRead(pFSFileName, fs)) {
		if (!fRead(pFSFileName2, fs)) {
			printf("Shader was unable to load");
		};
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
    //p.SetCamera(CameraPos, CameraTarget, CameraUp);

	p.SetCamera(mCamera->GetPos(), mCamera->GetTarget(), mCamera->GetUp());
    
    p.SetPerspectiveProj(30.0f, 800, 600, 1.0f, 100.0f);

    glUniformMatrix4fv(gScaleLocation, 1, GL_TRUE, (const GLfloat*)p.GetTrans());

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
	
}

Renderer::~Renderer ()
{
}