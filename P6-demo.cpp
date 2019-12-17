#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window"

void drawCone();
void drawIcecreamBall();
void display();
void drawTopping();
float rotateSpeed = 0;
boolean rotate = false;
float ambient[] = { 0.0, 0.0, 1.0 };
float position[] = { 0.0, 1.0, 0.0 };
float position2[] = { 1.0, 0.0, 0.0 };
float difuse[] = { 0.0,1.0,0.0 }; 

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		else if (wParam == VK_UP)
		{
			if (rotate)
				rotate = false;
			else
				rotate = true;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, difuse);
	glLightfv(GL_LIGHT1, GL_POSITION, position2);
	glEnable(GL_LIGHT1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glRotatef(rotateSpeed, 0, 1, 0);
	drawIcecreamBall();
	drawTopping();
	drawCone();
}
//--------------------------------------------------------------------

void drawTopping()
{
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0.3, 0.1, 0);
	glRotatef(45, 0, 0, 1);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.8);
	glVertex2f(0.02, 0.8);
	glVertex2f(0.02, 0.5);
	glVertex2f(0.0, 0.5);
	glPopMatrix();
	glEnd();

}

void drawIcecreamBall()
{
	GLUquadricObj *sphere = NULL;
	sphere = gluNewQuadric();

	glPushMatrix();
	
	glColor3f(0, 1, 0);
	glTranslatef(0, 0.1, 0);
	//glRotatef(rotateSpeed, 0, 0, 1);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, 0.25, 30, 30);

	gluDeleteQuadric(sphere);
	glPopMatrix();


	glPushMatrix();
	GLUquadricObj *sphere2 = NULL;
	sphere2 = gluNewQuadric();

	glColor3f(0.95, 0.61, 0.73);
	glTranslatef(0, 0.3, 0);
	//glRotatef(rotateSpeed, 0, 0, 1);
	gluQuadricDrawStyle(sphere2, GLU_FILL);
	gluSphere(sphere2, 0.22, 30, 30);

	gluDeleteQuadric(sphere2);
	glPopMatrix();

	glPushMatrix();
	GLUquadricObj *sphere3 = NULL;
	sphere3 = gluNewQuadric();

	glLoadIdentity();
	glColor3f(1, 1, 1);
	glTranslatef(0, 0.45, 0);
	//glRotatef(rotateSpeed, 0, 0, 1);
	gluQuadricDrawStyle(sphere3, GLU_FILL);
	gluSphere(sphere3, 0.18, 30, 30);

	gluDeleteQuadric(sphere3);
	glPopMatrix();
}

void drawCone()
{
	glLoadIdentity();
	GLUquadricObj *cylinder = NULL;
	cylinder = gluNewQuadric();

	glPushMatrix();
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.7, 0);
	glRotatef(270, 1, 0, 0);
	//glRotatef(rotateSpeed, 0, 0, 1);
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.001, 0.28, 0.8, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.59, 0.29, 0);
	glTranslatef(0, -0.7, 0);
	glRotatef(270, 1, 0, 0);
	//glRotatef(rotateSpeed, 0, 0, 1);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.001, 0.28, 0.8, 30, 30);
	glPopMatrix();

	gluDeleteQuadric(cylinder);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		if (rotate)
			rotateSpeed ++;
		else
			rotateSpeed = 0;

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------