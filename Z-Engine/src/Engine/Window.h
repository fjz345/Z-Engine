#pragma once

#include "zepch.h"
#include "Core.h"



namespace ZE
{

	class ZE_API Window
	{
	public:
		virtual ~Window() {}

		virtual void Update() = 0;

		virtual void SetWindowTitle(std::wstring newTitle) const = 0;
		virtual bool ExitWindow() const = 0;

		virtual bool IsFullscreen() const;
		virtual unsigned int GetWidth() const;
		virtual unsigned int GetHeight() const;

	protected:
		Window(std::wstring title, unsigned int width, unsigned int height, bool fullscreen)
			: _title(title), _width(width), _height(height) {}

		unsigned int _width = 800;
		unsigned int _height = 600;

		std::wstring _title = L"NoTitle";
		bool _fullscreen = false;
	};

	// Platform specific
	//static Window* Create(std::wstring title, unsigned int width, unsigned int height);


#ifdef ZE_PLATFORM_WINDOWS

	extern HINSTANCE gHInstance;
	extern int gNCmdShow;

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(HINSTANCE hInstance, int nCmdShow, unsigned int screenWidth, unsigned int screenHeight, bool fullscreen, LPCTSTR windowName, LPCTSTR windowTitle);

		~WindowsWindow() {}

		void Update() {}

		void SetWindowTitle(std::wstring newTitle) const { SetWindowTextW(this->_hwnd, newTitle.c_str()); }
		bool ExitWindow() const;

	private:
		HWND _hwnd = nullptr;
	};



#else
	ZE_ASSERT(false, "Fix support for more than windows")
#endif


}