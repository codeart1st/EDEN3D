#pragma once

#include "EDEN3D.hpp"
#include "GameApplication.hpp"
#include "GameWindow.hpp"

namespace EDEN3D {

	class EDEN3D_API MouseControls {

	public:
		typedef function<void (long&, long&)> MouseHandler;

		MouseControls(GameApplication&, const GameWindow&, const MouseHandler&);

	private:
		GameApplication::ControlHandler handler;
	};
}
