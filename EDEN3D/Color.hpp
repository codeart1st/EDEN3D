#pragma once

#include "EDEN3D.hpp"

namespace EDEN3D {

	class EDEN3D_API Color {

	public:
		Color();
		Color(float, float, float, float);

		float r, g, b, a;
	};
}
