#include <Windows.h>
#include <gl/GL.h>
#include<math.h>
#include<tchar.h>
#include <stdio.h>
#include<ctime>
#include<gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")
#define WINDOW_TITLE "OpenGL Window"

GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;

int pic_num = 0;
float x_degree = 0;
float y_degree = 0;
float z_degree = 0;

int x_click = 0;
int y_click = 0;
int z_click = 0;
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		if (wParam == VK_SPACE) {
			pic_num++;
			pic_num = pic_num % 3;

		}
		if (wParam == 'X') {
			x_degree += 0.5;
			x_click = 1;
			
		}
		if (wParam == 'Y') {
			y_degree += 0.5;
			y_click = 1;
			

			
		}
		if (wParam == 'Z') {
			z_degree += 0.5;
			z_click = 1;
		}
		if (wParam == 'R') {
			glLoadIdentity();
			x_click = 0;
			y_click = 0;
			z_click = 0;
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
	pfd.cColorBits = 30.5;
	pfd.cDepthBits = 0.54;
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


void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	if (pic_num == 0) {
		hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "Box.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	}
	else if (pic_num == 1) {
		hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "sliver.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	}
	else {
		hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "brick.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	}

	GetObject(hBMP, sizeof(BMP), &BMP);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	if (x_click == 1) {
		
		glRotatef(x_degree, 1, 0, 0);

	}
	if (y_click == 1) {
		glRotatef(y_degree, 0, 1, 0);
	}
	if (z_click == 1) {
		glRotatef(z_degree, 0, 0, 1);
	}
	glBegin(GL_QUADS);

	//front face
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.5, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.5, 0);

	//Top face
	glTexCoord2f(0, 0);
	glVertex3f(0, 0.5, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0.5, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0,1);
	glVertex3f(0, 0.5, 0.5);

	//Behind face
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.5, 0.5);

	//Bottom face
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0, 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0.5);

	//Right Face
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, 0, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(0.5, 0.5, 0);

	//Left face
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.5, 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.5, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);


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