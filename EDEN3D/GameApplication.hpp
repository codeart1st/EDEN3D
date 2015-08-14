#pragma once

#include "EDEN3D.hpp"

#include <functional>

namespace EDEN3D {

	class EDEN3D_API GameApplication {

	friend class GameWindow;

	public:
		GameApplication(const HINSTANCE&, wstring = NULL);
		~GameApplication();

		void GetDeviceInfo();

		int run(const function<void ()>&);

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
