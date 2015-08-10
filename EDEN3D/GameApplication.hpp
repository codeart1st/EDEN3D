#pragma once

#include <D3D11.h>

#include "EDEN3D.hpp"

#pragma comment (lib, "d3d11.lib")

namespace EDEN3D {

	class EDEN3D_API GameApplication {

	friend class GameWindow;

	public:
		GameApplication(const HINSTANCE&, LPCWSTR = NULL);
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
		WNDCLASSEX wc;

	private:
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		static int counter;

		HINSTANCE hInstance;
		LPCWSTR wcName;
	};
}
