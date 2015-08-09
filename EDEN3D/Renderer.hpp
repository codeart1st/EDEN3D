#pragma once

#include "stdafx.h"

#include "Camera.hpp"
#include "Triangle.hpp"

namespace EDEN3D {

	struct EDEN3D_API RendererOptions {
		FLOAT* clearColor;
	};

	class Renderer {

	public:
		Renderer() {};
		virtual ~Renderer() {};

		virtual void render(const Camera&, Triangle&) = 0;
	};
}
