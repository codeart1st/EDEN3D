#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "GameApplication.hpp"

namespace EDEN3D {

	class GameWindow {

	public:
		GameWindow(GameApplication&, LPCSTR, const int = 640, const int = 480);

	private:
		HWND hWnd;
	};
}