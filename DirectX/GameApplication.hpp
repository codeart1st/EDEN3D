#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

namespace EDEN3D {

	class GameApplication {

	friend class GameWindow;

	public:
		GameApplication(const HINSTANCE&);

		template<typename Func> void run(const Func& func) {

			MSG msg;

			while (GetMessage(&msg, NULL, 0, 0)) {

				TranslateMessage(&msg);
				DispatchMessage(&msg);

				func();
			}
		};

	protected:
		WNDCLASSEX wc;

	private:
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		HINSTANCE hInstance;
		LPCSTR wcName;
	};
}
