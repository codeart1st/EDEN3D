#include "stdafx.h"
#include "GameApplication.hpp"

namespace EDEN3D {

	int GameApplication::counter = 0;

	ID3D11Device* GameApplication::dev = NULL;
	ID3D11DeviceContext* GameApplication::devcon = NULL;

	GameApplication::GameApplication(const HINSTANCE& hInstance, LPCWSTR iconPath) {

		if (counter > 0) {

			int ret = MessageBox(
				NULL,
				L"GameApplication already instantiated.",
				L"ERROR",
				MB_ICONERROR | MB_OK);

			exit(EXIT_FAILURE);

		} else counter++;

		this->hInstance = hInstance;
		this->wcName = L"GameWindowClass";

		wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = this->hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = this->wcName;

		HANDLE hIcon = LoadImage(0, iconPath, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

		if (hIcon) {
			wc.hIcon = reinterpret_cast<HICON>(hIcon);
		}

		RegisterClassEx(&wc);

		D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &dev, NULL, &devcon);
	}

	GameApplication::~GameApplication() {

		dev->Release();
		devcon->Release();
	}

	LRESULT CALLBACK GameApplication::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

		if (message == WM_DESTROY) {
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}
