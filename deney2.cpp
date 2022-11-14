// deney.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
#include <cmath>

using namespace std;
#define PI 3.14
#define IX(i,j) ((i)+(N+2)*(j))

#include <iostream>
const int N = 1000;

void add_source(int N, float* x, float* s, float dt)
{
	int i, size = (N + 2) * (N + 2);
	for (i = 0; i < size; i++) x[i] += dt * s[i];
}

int main()
{
	int size = (N + 2) * (N + 2);
	int* u = new int[size];
	int* v = new int[size];
	int* u_prev = new int[size];
	int* v_prev = new int[size];
	int* dens = new int[size];
	int* dens_prev = new int[size];
	delete[] u; delete[] v; delete[] u_prev; delete[] v_prev; delete[] dens; delete[] dens_prev;
	
	

	cout << size;
	HWND myConsole = GetConsoleWindow();
	HDC mdc = GetDC(myConsole);
	int pixelX = 0;
	COLORREF COLOR = RGB(0, 255, 0);
	for (double i = 0; i < PI * 4; i += 0.05) {
		SetPixel(mdc, pixelX, (int)(50 + 25 * cos(i)), COLOR);
		pixelX++;
	}
	ReleaseDC(myConsole, mdc);
	cin.ignore();
	return 0;
}
