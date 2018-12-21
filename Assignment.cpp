#include <Windows.h>
#include <gl/GL.h>
#include<math.h>
#include<tchar.h>
#include <stdio.h>
#include<ctime>

#pragma comment (lib, "OpenGL32.lib")
#define WINDOW_TITLE "OpenGL Window"
float direction = 0;
float x = 1;
float y = 1;
float z = 1;
float rotate = 0.05;
double arm = 0;
int move_arm = 0;
int already_move_arm = 0;
float move_arm_rotate = 0.05;
float move_angle = 0;
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
			direction += rotate;
		}
		if (wParam == VK_SPACE) {
			rotate = 0;
			move_arm = 0;
			already_move_arm = 0;
			glLoadIdentity();
			glRotatef(270, 1, 0, 0);
			direction = 0;
			move_angle = 0;

		}
		if (wParam == VK_UP) {
			if (move_angle > 90) {
				move_angle = move_angle;
			}
			else {
				move_angle += 1;
			}
		}
		if (wParam == VK_DOWN) {


			if (move_angle < 0) {
				move_angle = move_angle;
			}
			else {
				move_angle -= 1;
			}

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
void footer_plan() {
	glColor3f(0.329412, 0.329412, 0.329412);
	glBegin(GL_QUADS);

	glVertex3f(0, 0, 0);
	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0, 0.05, 0);

	glVertex3f(0, 0.05, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0.2, 0.05, 0.3);
	glVertex3f(0, 0.05, 0.3);

	glVertex3f(0, 0.05, 0.3);
	glVertex3f(0.2, 0.05, 0.3);
	glVertex3f(0.2, 0, 0.3);
	glVertex3f(0, 0, 0.3);

	glVertex3f(0, 0, 0);
	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0, 0.3);
	glVertex3f(0, 0, 0.3);

	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0.2, 0.05, 0.3);
	glVertex3f(0.2, 0, 0.3);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.05, 0);
	glVertex3f(0, 0.05, 0.3);
	glVertex3f(0, 0, 0.3);

	glEnd();
}
void draw_lower_leg() {
	glBegin(GL_QUADS);
	
	glVertex3f(0, 0, 0);
	glVertex3f(0.1, 0, 0.1);
	glVertex3f(0.3, 0, 0.1);
	glVertex3f(0.5, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0.1, 0, 0.1);
	glVertex3f(0.1, 0.5, 0.1);
	glVertex3f(0, 0.5, 0);

	glVertex3f(0.1, 0, 0.1);
	glVertex3f(0.3, 0, 0.1);
	glVertex3f(0.3, 0.5, 0.1);
	glVertex3f(0.1, 0.5, 0.1);
	

	glVertex3f(0.3, 0, 0.1);
	glVertex3f(0.3, 0.5, 0.1);
	glVertex3f(0.5, 0.5, 0);
	glVertex3f(0.5, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5, 0);
	glVertex3f(0.5, 0.5, 0);
	glVertex3f(0, 0.5, 0);

	glVertex3f(0, 0.5, 0);
	glVertex3f(0.1, 0.5, 0.1);
	glVertex3f(0.3, 0.5, 0.1);
	glVertex3f(0.5, 0.5, 0);

	glEnd();

	glBegin(GL_QUADS);

	glVertex3f(0, 0.5, 0);
	glVertex3f(0.1, 0.5, -0.1);
	glVertex3f(0.3, 0.5, -0.1);
	glVertex3f(0.5, 0.5, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0.1, 0, -0.1);
	glVertex3f(0.3, 0, -0.1);
	glVertex3f(0.5, 0, 0);

	glVertex3f(0, 0.5, 0);
	glVertex3f(0.1, 0.5, -0.1);
	glVertex3f(0.1, 0, -0.1);
	glVertex3f(0, 0, 0);

	glVertex3f(0.1, 0.5, -0.1);
	glVertex3f(0.3, 0.5, -0.1);
	glVertex3f(0.3, 0, -0.1);
	glVertex3f(0.1, 0, -0.1);

	glVertex3f(0.3, 0, -0.1);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0.5, 0.5, 0);
	glVertex3f(0.3, 0.5, -0.1);

	glVertex3f(0, 0, 0);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0.5, 0.5, 0);
	glVertex3f(0, 0.5, 0);

	glEnd();



}
void leg_foot_connector() {
	glBegin(GL_POLYGON);

	glVertex3f(0, 0, 0);
	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0.1, 0);
	glVertex3f(0, 0.1, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.1, 0);
	glVertex3f(0.1, 0.1, -0.2);
	glVertex3f(0.1, 0, -0.2);

	glVertex3f(0.2, 0, 0);
	glVertex3f(0.1, 0, -0.2);
	glVertex3f(0.1, 0.1, -0.2);
	glVertex3f(0.2, 0.1, 0);

	glVertex3f(0, 0.1, 0);
	glVertex3f(0.2, 0.1, 0);
	glVertex3f(0.1, 0.1, -0.2);

	glVertex3f(0, 0, 0);
	glVertex3f(0.2, 0, 0);
	glVertex3f(0.1, 0, -0.2);

	glEnd();
}
void prism() {
	
	glBegin(GL_QUADS);
	
	glVertex3f(0, 0, 0);
	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0, 0.05, 0);

	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0.2, 0.05, -0.2);
	glVertex3f(0.2, 0, -0.2);

	glVertex3f(0.2, 0, -0.2);
	glVertex3f(0.2, 0.05, -0.2);
	glVertex3f(0, 0.05, -0.2);
	glVertex3f(0, 0, -0.2);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.05, 0);
	glVertex3f(0, 0.05, -0.2);
	glVertex3f(0, 0, -0.2);

	glVertex3f(0, 0.05, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0.2, 0.05, -0.2);
	glVertex3f(0, 0.05, -0.2);

	glVertex3f(0, 0, 0);
	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0, -0.2);
	glVertex3f(0, 0, -0.2);

	glEnd();

	glBegin(GL_POLYGON);

	glVertex3f(0, 0, 0.05);
	glVertex3f(0.2, 0, 0.05);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0, 0.05, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.05, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0.2, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.05);
	glVertex3f(0.2, 0, 0.05);
	glVertex3f(0.2, 0, 0);

	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0.2, 0, 0.05);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.05, 0);
	glVertex3f(0, 0, 0.05);

	glEnd();

}
//--------------------------------------------------------------------
float degree = 0;
void plexis(int postion) {
	glPushMatrix();
	if (postion == 0) {
		glRotatef(90, 0, 1, 0);
		glRotatef(45, 1, 0, 0);
	}
	else {
		glRotatef(-90, 0, 1, 0);
		//glTranslatef(0, 0, -0.2);
		glRotatef(45, 1, 0, 0);
	}
	glBegin(GL_QUADS);

	glVertex3f(0, 0, 0);
	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0, 0.05, 0);

	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0.2, 0.05, -0.2);
	glVertex3f(0.2, 0, -0.2);

	glVertex3f(0.2, 0, -0.2);
	glVertex3f(0.2, 0.05, -0.2);
	glVertex3f(0, 0.05, -0.2);
	glVertex3f(0, 0, -0.2);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.05, 0);
	glVertex3f(0, 0.05, -0.2);
	glVertex3f(0, 0, -0.2);

	glVertex3f(0, 0.05, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0.2, 0.05, -0.2);
	glVertex3f(0, 0.05, -0.2);

	glVertex3f(0, 0, 0);
	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0, -0.2);
	glVertex3f(0, 0, -0.2);

	glEnd();

	glBegin(GL_POLYGON);

	glVertex3f(0, 0, 0.05);
	glVertex3f(0.2, 0, 0.05);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0, 0.05, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.05, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0.2, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.05);
	glVertex3f(0.2, 0, 0.05);
	glVertex3f(0.2, 0, 0);

	glVertex3f(0.2, 0, 0);
	glVertex3f(0.2, 0.05, 0);
	glVertex3f(0.2, 0, 0.05);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.05, 0);
	glVertex3f(0, 0, 0.05);

	glEnd();

	glPopMatrix();
}
void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	
	//glRotatef(0.5, 0, 1, 0);
	degree += 0.5;

	//Upper Right Leg
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0,-0.2,0.2);
	draw_lower_leg();
	glPopMatrix();

	//Upper Left Leg
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, -0.2, -0.2);
	draw_lower_leg();
	glPopMatrix();
	
	//Right foot plan
	glPushMatrix();
	glTranslatef(0.1, -0.9, -0.3);
	footer_plan();
	glPopMatrix();

	//Left foot plan
	glPushMatrix();
	glTranslatef(-0.3, -0.9, -0.3);
	footer_plan();
	glPopMatrix();


	//Right Lower Leg
	glPushMatrix();
	
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, -0.8, 0.2);
	draw_lower_leg();
	glPopMatrix();

	//Right Connector between leg and foot plan
	glPushMatrix();
	glTranslatef(0.1, -0.9, -0.3);
	leg_foot_connector();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, -0.85, -0.1);
	prism();
	glPopMatrix();


	//Left Lower Leg
	
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, -0.8, -0.2);
	draw_lower_leg();
	glPopMatrix();
	
	

	//Left Connector between leg and foot plan
	glPushMatrix();
	glTranslatef(-0.3, -0.9, -0.3);
	leg_foot_connector();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.85, -0.1);
	
	prism();
	glPopMatrix();

	//Plexis
	glPushMatrix();
	glTranslatef(-0.05, 0.125, 0);
	plexis(0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.03, 0.125, 0);
	plexis(1);
	glPopMatrix();
	

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
