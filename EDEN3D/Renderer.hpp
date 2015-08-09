#pragma once

#include "stdafx.h"

namespace EDEN3D {

	class EDEN3D_API Renderer {

	public:
		Renderer() {};
		virtual ~Renderer() {};

		virtual void render() = 0;
	};
}
