#include "../Window.h"

namespace ZE
{
	class Win32Window : public Window
	{
	public:
		Win32Window(HINSTANCE hInstance, int nCmdShow, unsigned int screenWidth, unsigned int screenHeight, bool fullscreen, LPCTSTR windowName, LPCTSTR windowTitle);

		~Win32Window();

		void Update(double dt);

		inline HWND* GetHWND() { return &_hwnd; }

		void SetWindowTitle(std::wstring newTitle) const;

	private:
		HWND _hwnd = nullptr;
	};

}