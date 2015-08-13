#pragma once

#include "EDEN3D.hpp"
#include "Object3D.hpp"

namespace EDEN3D {

	class EDEN3D_API Camera : public Object3D {

	public:
		Camera() {};
		virtual ~Camera() {};

		virtual void render() = 0;
	};
}
