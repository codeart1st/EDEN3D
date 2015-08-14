#pragma once

#include "EDEN3D.hpp"
#include "GameWindow.hpp"

namespace EDEN3D {

	class EDEN3D_API MouseControls {

	public:
		MouseControls(const GameWindow&);
		~MouseControls();

	protected:
		LPDIRECTINPUTDEVICE8 mouse;
	};
}
