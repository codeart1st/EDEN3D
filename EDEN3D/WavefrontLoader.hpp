#pragma once

#include "EDEN3D.hpp"
#include "Mesh.hpp"

#include <functional>

namespace EDEN3D {

	class EDEN3D_API WavefrontLoader {

	public:
		static void load(string, const function<void (Mesh*)>&);
	};
}
