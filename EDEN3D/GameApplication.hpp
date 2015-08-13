#pragma once

#include "EDEN3D.hpp"

namespace EDEN3D {

	class EDEN3D_API GameApplication {

	friend class GameWindow;

	public:
		GameApplication(const HINSTANCE&, wstring = NULL);
		~GameApplication();

		void GetDeviceInfo();

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

		static ID3D11Device* device;
		static ID3D11DeviceContext* context;

	protected:
		WNDCLASSEX winClass;
		HINSTANCE hInstance;
		LPCWSTR winClassName;

	private:
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		static int counter;
	};
}
