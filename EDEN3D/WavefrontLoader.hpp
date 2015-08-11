#pragma once

#include "EDEN3D.hpp"
#include "Mesh.hpp"

namespace EDEN3D {

	class EDEN3D_API WavefrontLoader {

	public:
		static Mesh* load(const string);
	};
}
