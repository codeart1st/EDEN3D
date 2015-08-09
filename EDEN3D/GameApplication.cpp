#include "stdafx.h"
#include "GameApplication.hpp"

namespace EDEN3D {

	GameApplication::GameApplication(const HINSTANCE& hInstance) {

		this->hInstance = hInstance;
		this->wcName = L"WindowClass";

		wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = this->hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = this->wcName;

		RegisterClassEx(&wc);
	}

	LRESULT CALLBACK GameApplication::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

		if (message == WM_DESTROY) {
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}
