#include "GameWindow.hpp"

namespace EDEN3D {

	GameWindow::GameWindow(GameApplication& app, LPCSTR title, const int width, const int height) {

		int centerX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		int centerY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
		hWnd = CreateWindowEx(NULL, app.wcName, title, WS_OVERLAPPEDWINDOW, centerX, centerY, width, height, NULL, NULL, app.hInstance, NULL);

		ShowWindow(hWnd, SW_SHOW);
	}
}
