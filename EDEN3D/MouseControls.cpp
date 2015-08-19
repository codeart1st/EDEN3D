#include "MouseControls.hpp"

namespace EDEN3D {

	MouseControls::MouseControls(GameApplication& app, const GameWindow& window, const MouseHandler& callback) {

		handler = [=] (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

			switch (message) {
				case WM_MOUSEMOVE: {
						long x = GET_X_LPARAM(lParam);
						long y = GET_Y_LPARAM(lParam);
						wstring button;

						switch (wParam) {
						case MK_LBUTTON:
							button = L"MK_LBUTTON";
							break;
						case MK_MBUTTON:
							button = L"MK_MBUTTON";
							break;
						case MK_RBUTTON:
							button = L"MK_RBUTTON";
							break;
						}

						callback(x, y, button);
					} break;

				case WM_RBUTTONDOWN: {
						POINT point;
						GetCursorPos(&point);
						RECT rect = { point.x, point.y, point.x, point.y };
						ClipCursor(&rect);
						ShowCursor(false);
					} break;
				case WM_RBUTTONUP:
					ClipCursor(NULL);
					ShowCursor(true);
					break;
			}
		};

		app.addControlHandler(&handler);
	}
}
