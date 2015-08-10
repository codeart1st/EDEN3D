#pragma once

#include "EDEN3D.hpp"
#include "GameApplication.hpp"

namespace EDEN3D {

	class EDEN3D_API GameWindow {

	friend class DefaultRenderer;

	public:
		GameWindow(GameApplication&, LPCWSTR = title, const int = 640, const int = 480);

		const int& getWidth() const { return width; };
		const int& getHeight() const { return height; };

	private:
		HWND hWnd;
		int width;
		int height;
		bool inUse;

		static LPCWSTR title;
	};
}