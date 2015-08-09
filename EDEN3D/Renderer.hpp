#pragma once

#include "stdafx.h"

namespace EDEN3D {

	class Renderer {

	public:
		Renderer() {};
		virtual ~Renderer() {};

		virtual void render() = 0;
	};
}
