#pragma once

#include "zepch.h"
#include "Logging.h"
#include "Window.h"

namespace ZE
{
	bool Window::IsFullscreen() const
	{
		return this->_fullscreen;
	}
	unsigned int Window::GetWidth() const
	{
		return this->_width;
	}
	unsigned int Window::GetHeight() const
	{
		return this->_height;
	}




	#ifdef ZE_PLATFORM_WINDOWS

	/*

	Window* Create(std::wstring title, unsigned int width, unsigned int height)
	{
		//return new WindowsWindow(gHInstance, gNCmdShow, width, height, false, L"windowName", L"FUCK");
		//return new WindowsWindow(nullptr, 0, 0, 0, false, L"ASD", L"ASD");
		return nullptr;
	}

	*/

	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
			{
				if (MessageBox(0, L"Are you sure you want to exit?", L"Exit", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					DestroyWindow(hWnd);
				}
			}

			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	WindowsWindow::WindowsWindow(HINSTANCE hInstance, int nCmdShow, unsigned int screenWidth, unsigned int screenHeight, bool fullscreen, LPCTSTR windowName, LPCTSTR windowTitle)
		: Window(windowTitle, screenWidth, screenHeight, fullscreen)
	{
		if (this->_fullscreen)
		{
			HMONITOR hmon = MonitorFromWindow(this->_hwnd, MONITOR_DEFAULTTONEAREST);
			MONITORINFO mi = { sizeof(mi) };
			GetMonitorInfo(hmon, &mi);

			this->_width = mi.rcMonitor.right - mi.rcMonitor.left;
			this->_height = mi.rcMonitor.bottom - mi.rcMonitor.top;
		}

		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;	// Device Context
		wc.lpfnWndProc = WndProc;	// Callback, Event catcher
		wc.cbClsExtra = NULL;
		wc.cbWndExtra = NULL;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = windowName;
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		ZE_ASSERT(!RegisterClassEx(&wc), ZE_ERROR("Error registering window class"))

			// This structure describes the window
			this->_hwnd = CreateWindowEx(NULL,
				windowName,
				windowTitle,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,
				screenWidth, screenHeight,
				NULL,
				NULL,
				hInstance,
				NULL);

		// If the windowhandle was unsuccesful
		ZE_ASSERT(!this->_hwnd, ZE_ERROR("Error creating window"))

			// Remove the topbar of the window if we are in fullscreen
			if (this->_fullscreen)
			{
				SetWindowLong(this->_hwnd, GWL_STYLE, 0);
			}

		ShowWindow(this->_hwnd, nCmdShow);
		UpdateWindow(this->_hwnd);
	}

	bool WindowsWindow::ExitWindow() const
	{
		bool closeWindow = false;
		MSG msg = { 0 };

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			TranslateMessage(&msg);
			DispatchMessage(&msg);	// Går in i "CALLBACK" funktionen

			if (msg.message == WM_QUIT)
			{
				closeWindow = true;
			}
		}
		return closeWindow;
	}

#else
ZE_ASSERT(false, "Fix support for more than windows")
#endif



}