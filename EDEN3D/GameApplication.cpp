#include "GameApplication.hpp"

#include <vector>

namespace EDEN3D {

	int GameApplication::counter = 0;
	
	ID3D11Device* GameApplication::device = NULL;
	ID3D11DeviceContext* GameApplication::context = NULL;
	LPDIRECTINPUT8 GameApplication::directInput = NULL;

	GameApplication::GameApplication(const HINSTANCE& hInstance, wstring iconPath) {

		if (counter > 0) {

			int ret = MessageBox(
				NULL,
				L"GameApplication already instantiated.",
				L"ERROR",
				MB_ICONERROR | MB_OK);

			exit(EXIT_FAILURE);

		} else counter++;

		directInput = NULL;
		this->hInstance = hInstance;
		this->winClassName = L"GameWindowClass";

		winClass = {};
		winClass.cbSize = sizeof(WNDCLASSEX);
		winClass.style = CS_HREDRAW | CS_VREDRAW;
		winClass.lpfnWndProc = WndProc;
		winClass.hInstance = this->hInstance;
		winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		winClass.hCursor = LoadCursorFromFile(L"cursor.cur");
		winClass.lpszClassName = this->winClassName;

		HANDLE hIcon = LoadImage(0, iconPath.c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);

		if (hIcon) winClass.hIcon = reinterpret_cast<HICON>(hIcon);

		RegisterClassEx(&winClass);

		D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &device, NULL, &context);
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL);
	}

	GameApplication::~GameApplication() {

		directInput->Release();
		context->Release();
		device->Release();
	}

	HINSTANCE GameApplication::getHandle() const {
		return hInstance;
	}

	void GameApplication::getDeviceInfo() {

		// TODO:
		IDXGIDevice* device = NULL;
		IDXGIAdapter* adapter = NULL;

		GameApplication::device->QueryInterface(&device);
		device->GetAdapter(&adapter);

		DXGI_ADAPTER_DESC description = {};
		adapter->GetDesc(&description);

		UINT i = 0;
		IDXGIOutput * output;
		std::vector<IDXGIOutput*> outputs;
		while (adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND) {

			outputs.push_back(output);
			++i;
		}

		DXGI_OUTPUT_DESC desc = {};
		
		for (auto output: outputs) {
			output->GetDesc(&desc);
			OutputDebugString(desc.DeviceName);
		}
	}

	int GameApplication::run(const GameLoop& func) {

		MSG msg;

		while (TRUE) {

			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if (msg.message == WM_QUIT) break;

			}
			else func();
		}

		return msg.wParam;
	};

	LRESULT CALLBACK GameApplication::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

		switch (message) {
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
		}

		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}
