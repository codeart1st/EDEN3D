#pragma once

#include "stdafx.h"

namespace EDEN3D {

	class EDEN3D_API GameApplication {

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
		LPCWSTR wcName;
	};
}
