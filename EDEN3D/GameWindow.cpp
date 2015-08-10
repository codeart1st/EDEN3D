#include "EDEN3D.hpp"
#include "GameWindow.hpp"

namespace EDEN3D {

	LPCWSTR GameWindow::title = L"GameWindow";

	GameWindow::GameWindow(GameApplication& app, LPCWSTR title, const int width, const int height) {

		this->width = width;
		this->height = height;
		this->inUse = false;

		int centerX = (GetSystemMetrics(SM_CXSCREEN) - this->width) / 2;
		int centerY = (GetSystemMetrics(SM_CYSCREEN) - this->height) / 2;

		DWORD dwStyle = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX;
		RECT rect = { 0, 0, this->width, this->height };

		AdjustWindowRect(&rect, dwStyle, FALSE);

		hWnd = CreateWindowEx(NULL, app.wcName, title, dwStyle, centerX, centerY, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, app.hInstance, NULL);

		ShowWindow(hWnd, SW_SHOW);
	}
}
