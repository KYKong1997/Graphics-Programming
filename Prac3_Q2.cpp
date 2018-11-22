#include <Windows.h>
#include <gl/GL.h>
#include<math.h>

#include<ctime>
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"
int num = 3;
float rotate = 0.05;
const double PI = 3.141592654;
float direction = 0.05;
float  counter = 0.06;
bool stopMill = false;
bool night = false;

float rForSky = 0.196078;
float gForSky = 0.6;
float bForSky = 0.8;
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		if (wParam == VK_UP) {

			if (num < 10) {

				num++;
			}

		}
		if (wParam == VK_DOWN) {

			if (num > 3)

				num--;
		}
		if (wParam == VK_SPACE) {
			glLoadIdentity();
			stopMill ^= true;
		}
		if (wParam == 'T') {
			(direction == 0.5) ? (direction = 0.05) : (direction = 0.5);

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
void draw_circle(float x, float y, float radius) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	static const int circle_points = 100;
	static const float angle = 2.0f * 3.1416f / circle_points;

	// this code (mostly) copied from question:
	glBegin(GL_POLYGON);
	double angle1 = 0.0;
	glVertex2d(radius * cos(0.0), radius * sin(0.0));
	int i;
	for (i = 0; i < circle_points; i++)
	{
		glVertex2d(radius * cos(angle1), radius *sin(angle1));
		angle1 += angle;
	}
	glEnd();
	glPopMatrix();
}
void drawmill() {
	float angle = 360 / num;
	for (int i = 0; i < num; i++) {

		glPushMatrix();

		glRotatef(angle*i, 0, 0, 1);
		glBegin(GL_QUADS);
		glVertex2f(-0.05, 0.5);
		glVertex2f(0.05, 0.5);
		glVertex2f(0.05, 0);
		glVertex2f(-0.05, 0);
		glEnd();
		glPopMatrix();


	}
}
void drawDisk(double radius) {
	int d;

	glTranslatef(-0.7, 0.7, 0);
	glBegin(GL_POLYGON);
	for (d = 0; d < 360; d++) {
		double angle = 2 * PI / 32 * d;
		glVertex2d(-radius*cos(angle), -radius*sin(angle));
	}
	glEnd();

}
void drawRoad() {
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-1, -0.8);
	glVertex2f(-1, -0.6);
	glVertex2f(1, -0.6);
	glVertex2f(1, -0.8);
	glEnd();

}
void drawSun() {
	int i = 0;

	if (night) {
		glColor3f(1, 1, 1);
	}
	else {
		glColor3f(1, 1, 0);
	}


	drawDisk(0.05);
	glColor3f(0, 0, 0);

}
void wheel() {
	float th;
	int d = 0;
	float radius = 0.05;
	glPushMatrix();
	glTranslatef(-0.90, -0.65, 0);
	glBegin(GL_POLYGON);
	for (d = 0; d < 360; d++) {
		double angle = 2 * PI / 32 * d;
		glVertex2d(-radius * cos(angle), -radius * sin(angle));
	}
	glEnd();
	glPopMatrix();
}
void wheel_1() {
	float th;
	int d = 0;
	float radius = 0.05;
	glPushMatrix();
	glTranslatef(-0.75, -0.65, 0);
	glBegin(GL_POLYGON);
	for (d = 0; d < 360; d++) {
		double angle = 2 * PI / 32 * d;
		glVertex2d(-radius * cos(angle), -radius * sin(angle));
	}
	glEnd();
	glPopMatrix();
}
void drawWheel() {
	counter = counter + 0.0001;
	glPushMatrix();
	glTranslatef(counter, 0.000001, 0.0);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(-1, -0.65);
	glVertex2f(-1, -0.55);
	glVertex2f(-0.65, -0.55);
	glVertex2f(-0.65, -0.65);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(-0.95, -0.55);
	glVertex2f(-0.9, -0.45);
	glVertex2f(-0.8, -0.45);
	glVertex2f(-0.7, -0.55);
	glEnd();
	wheel();
	wheel_1();
	glPopMatrix();
}
void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	glClear(GL_COLOR_BUFFER_BIT);
	//(night==true)? glClearColor(0, 0.2, 0.4,0.5) : glClearColor(0.196078, 0.6, 0.8, 0.5);
	//glClearColor(1, 1, 1, 0.5);
	glLoadIdentity();
	//background
	glBegin(GL_QUADS);
	//(night == true) ? glColor3f(0, 0.2, 0.4) : glColor3f(0.196078, 0.6, 0.8);
	rForSky -= 0.0001;
	gForSky -= 0.0001;
	bForSky -= 0.0001;
	if(rForSky<0.2){rForSky += 0.0001;}
	if (gForSky < 0.2 || bForSky < 0.2) { gForSky += 0.0001; bForSky += 0.0001; }

	glColor3f(rForSky, gForSky, bForSky);
	glVertex2f(-1, 1);
	glVertex2f(1, 1);
	glVertex2f(1, -1);
	glVertex2f(-1, -1);
	glEnd();

	//tower
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(-0.05, 0);
	glVertex2f(0.05, 0);
	glVertex2f(0.1, -0.8);
	glVertex2f(-0.1, -0.8);
	glEnd();




	//windmill
	glColor3f(1, 1, 1);

	if (stopMill == true) {
		drawmill();
	}
	else {
		glPushMatrix();
		glRotatef(rotate, 0, 0, 1);
		drawmill();
		glPopMatrix();
		rotate += direction;
	}


	//ground
	glBegin(GL_QUADS);
	glColor3f(0.48, 0.98, 0);
	glVertex2f(-1, -1);
	glVertex2f(-1, -0.5);
	glVertex2f(1, -0.5);
	glVertex2f(1, -1);
	glEnd();

	glPushMatrix();
	drawSun();
	glPopMatrix();


	//road
	drawRoad();
	drawWheel();










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

	std::clock_t start;
	double duration;
	start = std::clock();
	
	while (true)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		
		display();
		//int a = clock() / CLOCKS_PER_SEC;
		
		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------