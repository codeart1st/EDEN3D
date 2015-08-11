#include "Color.hpp"

namespace EDEN3D {

	Color::Color() {

		this->r = 0.0f;
		this->g = 0.0f;
		this->b = 0.0f;
		this->a = 1.0f;
	}

	Color::Color(float r, float g, float b, float a) {

		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
}
