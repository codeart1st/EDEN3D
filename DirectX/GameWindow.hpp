#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "GameApplication.hpp"

namespace EDEN3D {

	class GameWindow {

	friend class D3DRenderer;

	public:
		GameWindow(GameApplication&, LPCSTR, const int = 640, const int = 480);

		const int& getWidth() const { return width; };
		const int& getHeight() const { return height; };

	private:
		HWND hWnd;
		int width;
		int height;
	};
}