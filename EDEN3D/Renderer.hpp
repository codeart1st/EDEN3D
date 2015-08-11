#pragma once

#include "EDEN3D.hpp"
#include "Color.hpp"
#include "Mesh.hpp"

namespace EDEN3D {

	struct EDEN3D_API RendererOptions {
		Color clearColor;
	};

	class EDEN3D_API Renderer {

	public:
		Renderer() {};
		virtual ~Renderer() {};
	};
}
