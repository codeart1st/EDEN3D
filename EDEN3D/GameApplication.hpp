#pragma once

#include "EDEN3D.hpp"

namespace EDEN3D {

	class EDEN3D_API GameApplication {

	friend class GameWindow;

	public:
		typedef function<void ()> GameLoop;
		typedef function<void (HWND, UINT, WPARAM, LPARAM)> ControlHandler;

		GameApplication(const HINSTANCE&, wstring = NULL);
		~GameApplication();

		void getDeviceInfo();
		HINSTANCE getHandle() const;

		void addControlHandler(ControlHandler*);

		int run(const GameLoop&);

		static ID3D11Device* device;
		static ID3D11DeviceContext* context;

	protected:
		WNDCLASSEX winClass;
		HINSTANCE hInstance;
		LPCWSTR winClassName;

		static vector<const ControlHandler*> controls;

	private:
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		static int counter;
	};
}
