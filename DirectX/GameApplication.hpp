#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

namespace EDEN3D {

	class GameApplication {

	friend class GameWindow;

	public:
		GameApplication(const HINSTANCE&);

		template<typename Func> int run(const Func& func) {

			MSG msg;

			while (TRUE) {

				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

					TranslateMessage(&msg);
					DispatchMessage(&msg);

					if (msg.message == WM_QUIT) break;

				} else func();
			}

			return msg.wParam;
		};

	protected:
		WNDCLASSEX wc;

	private:
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		HINSTANCE hInstance;
		LPCSTR wcName;
	};
}
