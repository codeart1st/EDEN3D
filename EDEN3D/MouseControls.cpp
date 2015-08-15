#include "MouseControls.hpp"

namespace EDEN3D {

	MouseControls::MouseControls(GameApplication& app, const GameWindow& window, const MouseHandler& callback) {

		handler = [=] (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

			switch (message) {
				case WM_MOUSEMOVE:
					long x = GET_X_LPARAM(lParam);
					long y = GET_Y_LPARAM(lParam);
					callback(x, y);
					break;
			}
		};

		app.addControlHandler(&handler);
	}
}
