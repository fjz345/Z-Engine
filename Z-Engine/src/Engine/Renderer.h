#ifndef RENDERER_H
#define RENDERER_H

#include "Core.h"
#include "Window.h"

namespace ZE
{

	class ZE_API Renderer
	{
	public:
		// Platform specific
		static Renderer* Create(Window* renderTarget);

		Renderer(const Renderer& other) = delete;
		Renderer& operator=(const Renderer& other) = delete;

		virtual ~Renderer() {}

		virtual void Render(double dt) = 0;

	protected:
		Renderer(Window* renderTarget = nullptr) : _renderTarget(renderTarget) {}

		virtual void WaitForGPU() = 0;

		unsigned int _frameCounter = 0;

		Window* _renderTarget = nullptr;
	};



}

#endif // RENDERER_H