#pragma once

#include "stdafx.h"
#include "GameApplication.hpp"

namespace EDEN3D {

	class EDEN3D_API GameWindow {

	friend class D3DRenderer;

	public:
		GameWindow(GameApplication&, LPCWSTR, const int = 640, const int = 480);

		const int& getWidth() const { return width; };
		const int& getHeight() const { return height; };

	private:
		HWND hWnd;
		int width;
		int height;
	};
}