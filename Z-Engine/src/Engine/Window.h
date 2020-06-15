#ifndef WINDOW_H
#define WINDOW_H

#include "Core.h"

namespace ZE
{

	class ZE_API Window
	{
	public:
		// Platform specific
		static Window* Create(std::wstring title, unsigned int width, unsigned int height);

		virtual ~Window() {}

		virtual void Update() = 0;

		virtual void SetWindowTitle(std::wstring newTitle) const = 0;
		virtual bool ExitWindow() const = 0;

		inline bool IsFullscreen() const;
		inline unsigned int GetWidth() const;
		inline unsigned int GetHeight() const;

	protected:
		Window(std::wstring title, unsigned int width, unsigned int height, bool fullscreen)
			: _title(title), _width(width), _height(height), _fullscreen(fullscreen) {}

		unsigned int _width = 800;
		unsigned int _height = 600;

		std::wstring _title = L"NoTitle";
		bool _fullscreen = false;
	};



}

#endif // WINDOW_H