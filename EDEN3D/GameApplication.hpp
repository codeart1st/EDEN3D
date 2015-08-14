#pragma once

#include "EDEN3D.hpp"

#include <functional>

namespace EDEN3D {

	class EDEN3D_API GameApplication {

	friend class GameWindow;

	public:
		typedef function<void ()> GameLoop;

		GameApplication(const HINSTANCE&, wstring = NULL);
		~GameApplication();

		void getDeviceInfo();
		HINSTANCE getHandle() const;

		int run(const GameLoop&);

		static ID3D11Device* device;
		static ID3D11DeviceContext* context;
		static LPDIRECTINPUT8 directInput;

	protected:
		WNDCLASSEX winClass;
		HINSTANCE hInstance;
		LPCWSTR winClassName;

	private:
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		static int counter;
	};
}
