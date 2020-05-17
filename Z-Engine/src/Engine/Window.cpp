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


}