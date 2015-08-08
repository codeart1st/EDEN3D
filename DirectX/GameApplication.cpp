#include "GameApplication.hpp"

namespace EDEN3D {

	GameApplication::GameApplication(const HINSTANCE& hInstance) {

		this->hInstance = hInstance;
		this->wcName = "WindowClass";

		wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = this->hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = this->wcName;

		RegisterClassEx(&wc);
	}

	LRESULT CALLBACK GameApplication::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

		switch (message) {
			case WM_CLOSE:
				DestroyWindow(hwnd);
				break;
			case WM_DESTROY:
				//PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hwnd, message, wParam, lParam);
		}

		return 0;
	}
}
