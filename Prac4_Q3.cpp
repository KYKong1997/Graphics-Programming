#include <Windows.h>
#include <gl/GL.h>
#include<math.h>
#include<tchar.h>
#include<ctime>
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float direction = 0.05;
float x = 1;
float y = 1;
float z = 1;
int rotate = 0;
int move_arm = 0;
int already_move_arm = 0;
float move_arm_rotate = 0.05;
float move_angle = 10;
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		if (wParam == VK_RIGHT || wParam == VK_LEFT) {
			rotate = 1;

		}
		if (wParam == VK_SPACE) {
			rotate = 0;
			move_arm= 0;
			already_move_arm = 0;
			glLoadIdentity();
			glOrtho(-10, 10, -10, 10, -10, 10);
		}
		if (wParam == VK_UP) {
			move_arm = 1;
			already_move_arm = 1;
		}
		if (wParam == VK_DOWN) {
			move_arm = -1;
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
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	if (rotate == 1) {
		glRotatef(direction, 1, 1, 1);
		
	}
	
		
	glBegin(GL_LINES);

	glVertex3f(0, -2, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, 2);
	glVertex3f(0, -2, 2);
	glVertex3f(0, -2, 2);
	glVertex3f(0, -2, 0);

	glVertex3f(0, -2, 2);
	glVertex3f(4, -2, 2);
	glVertex3f(4, -2, 2);
	glVertex3f(4, -2, 0);
	glVertex3f(4, -2, 0);
	glVertex3f(0, -2, 0);
	glVertex3f(0, -2, 0);
	glVertex3f(0, -2, 2);

	glVertex3f(4, -2, 2);
	glVertex3f(4, 0, 2);
	glVertex3f(4, 0, 2);
	glVertex3f(4, 0, 0);
	glVertex3f(4, 0, 0);
	glVertex3f(4, -2, 0);
	glVertex3f(4, -2, 0);
	glVertex3f(4, -2, 2);

	glVertex3f(4, 0, 2);
	glVertex3f(4, 0, 0);
	glVertex3f(4, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 2);
	glVertex3f(0, 0, 2);
	glVertex3f(4, 0, 2);

	glEnd();
	
	if (move_arm == 1) {
		glPushMatrix();
		glRotatef(move_angle, 0,0, 1);
		glBegin(GL_LINES);

		glVertex3f(4, 0, 2);
		glVertex3f(4, 0, 0);
		glVertex3f(4, 0, 0);
		glVertex3f(4, -2, 0);
		glVertex3f(4, -2, 0);
		glVertex3f(4, -2, 2);
		glVertex3f(4, -2, 2);
		glVertex3f(4, 0, 2);

		glVertex3f(4, 0, 2);
		glVertex3f(4, 0, 0);
		glVertex3f(4, 0, 0);
		glVertex3f(8, 0, 0);
		glVertex3f(8, 0, 0);
		glVertex3f(8, 0, 2);
		glVertex3f(8, 0, 2);
		glVertex3f(4, 0, 2);

		glVertex3f(8, 0, 2);
		glVertex3f(8, 0, 0);
		glVertex3f(8, 0, 0);
		glVertex3f(8, -2, 0);
		glVertex3f(8, -2, 0);
		glVertex3f(8, -2, 2);
		glVertex3f(8, -2, 2);
		glVertex3f(8, 0, 2);

		glVertex3f(4, -2, 2);
		glVertex3f(4, -2, 0);
		glVertex3f(4, -2, 0);
		glVertex3f(8, -2, 0);
		glVertex3f(8, -2, 0);
		glVertex3f(8, -2, 2);
		glVertex3f(8, -2, 2);
		glVertex3f(4, -2, 2);
		glEnd();
		
		glPopMatrix();
	}
	else if (move_arm == -1) {
		if (already_move_arm == 1) {
			move_angle = 20;
		}
		glPushMatrix();
		glRotatef(-move_angle, 0, 0, 1);
		glBegin(GL_LINES);

		glVertex3f(4, 0, 2);
		glVertex3f(4, 0, 0);
		glVertex3f(4, 0, 0);
		glVertex3f(4, -2, 0);
		glVertex3f(4, -2, 0);
		glVertex3f(4, -2, 2);
		glVertex3f(4, -2, 2);
		glVertex3f(4, 0, 2);

		glVertex3f(4, 0, 2);
		glVertex3f(4, 0, 0);
		glVertex3f(4, 0, 0);
		glVertex3f(8, 0, 0);
		glVertex3f(8, 0, 0);
		glVertex3f(8, 0, 2);
		glVertex3f(8, 0, 2);
		glVertex3f(4, 0, 2);

		glVertex3f(8, 0, 2);
		glVertex3f(8, 0, 0);
		glVertex3f(8, 0, 0);
		glVertex3f(8, -2, 0);
		glVertex3f(8, -2, 0);
		glVertex3f(8, -2, 2);
		glVertex3f(8, -2, 2);
		glVertex3f(8, 0, 2);

		glVertex3f(4, -2, 2);
		glVertex3f(4, -2, 0);
		glVertex3f(4, -2, 0);
		glVertex3f(8, -2, 0);
		glVertex3f(8, -2, 0);
		glVertex3f(8, -2, 2);
		glVertex3f(8, -2, 2);
		glVertex3f(4, -2, 2);
		glEnd();
		glPopMatrix();
	}
	else {
		glBegin(GL_LINES);

		glVertex3f(4, 0, 2);
		glVertex3f(4, 0, 0);
		glVertex3f(4, 0, 0);
		glVertex3f(4, -2, 0);
		glVertex3f(4, -2, 0);
		glVertex3f(4, -2, 2);
		glVertex3f(4, -2, 2);
		glVertex3f(4, 0, 2);

		glVertex3f(4, 0, 2);
		glVertex3f(4, 0, 0);
		glVertex3f(4, 0, 0);
		glVertex3f(8, 0, 0);
		glVertex3f(8, 0, 0);
		glVertex3f(8, 0, 2);
		glVertex3f(8, 0, 2);
		glVertex3f(4, 0, 2);

		glVertex3f(8, 0, 2);
		glVertex3f(8, 0, 0);
		glVertex3f(8, 0, 0);
		glVertex3f(8, -2, 0);
		glVertex3f(8, -2, 0);
		glVertex3f(8, -2, 2);
		glVertex3f(8, -2, 2);
		glVertex3f(8, 0, 2);

		glVertex3f(4, -2, 2);
		glVertex3f(4, -2, 0);
		glVertex3f(4, -2, 0);
		glVertex3f(8, -2, 0);
		glVertex3f(8, -2, 0);
		glVertex3f(8, -2, 2);
		glVertex3f(8, -2, 2);
		glVertex3f(4, -2, 2);
		glEnd();
	}
	







	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10);
	while (true)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------