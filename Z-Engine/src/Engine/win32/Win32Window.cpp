#include "Win32Window.h"

#include "Win32Functions.h"

namespace ZE
{
	Window* Window::Create(std::wstring title, unsigned int width, unsigned int height)
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		return new Win32Window(hInstance, 1, width, height, false, L"windowName", title.c_str());
	}

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

	std::string GetLastErrorAsString()
	{
		//Get the error message, if any.
		DWORD errorMessageID = ::GetLastError();
		if (errorMessageID == 0)
			return std::string(); //No error message has been recorded

		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

		std::string message(messageBuffer, size);

		//Free the buffer.
		LocalFree(messageBuffer);

		return message;
	}

	Win32Window::Win32Window(HINSTANCE hInstance, int nCmdShow, unsigned int screenWidth, unsigned int screenHeight, bool fullscreen, LPCTSTR windowName, LPCTSTR windowTitle)
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

		ZE_ASSERT(RegisterClassEx(&wc), ZE_ERROR("Error registering window class"));

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
		ZE_ASSERT(this->_hwnd, ZE_ERROR("Error creating window"));

		// Remove the topbar of the window if we are in fullscreen
		if (this->_fullscreen)
		{
			SetWindowLong(this->_hwnd, GWL_STYLE, 0);
		}

		ShowWindow(this->_hwnd, nCmdShow);
		UpdateWindow(this->_hwnd);
	}

	bool Win32Window::ExitWindow() const
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

}