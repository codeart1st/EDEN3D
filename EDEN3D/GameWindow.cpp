#include "stdafx.h"
#include "GameWindow.hpp"

namespace EDEN3D {

	GameWindow::GameWindow(GameApplication& app, LPCWSTR title, const int width, const int height, LPWSTR iconPath) {

		this->width = width;
		this->height = height;

		int centerX = (GetSystemMetrics(SM_CXSCREEN) - this->width) / 2;
		int centerY = (GetSystemMetrics(SM_CYSCREEN) - this->height) / 2;

		DWORD dwStyle = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX;
		RECT rect = { 0, 0, this->width, this->height };

		AdjustWindowRect(&rect, dwStyle, FALSE);

		hWnd = CreateWindowEx(NULL, app.wcName, title, dwStyle, centerX, centerY, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, app.hInstance, NULL);

		ShowWindow(hWnd, SW_SHOW);
		setIcon(iconPath);
	}

	void GameWindow::setIcon(LPWSTR iconPath) {

		HANDLE hIcon = LoadImage(0, iconPath, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

		if (hIcon) {
			SendMessage(hWnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon));
			SendMessage(hWnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon));
			SendMessage(GetWindow(hWnd, GW_OWNER), WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon));
			SendMessage(GetWindow(hWnd, GW_OWNER), WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon));
		}
	}
}
