#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include "GameWindow.hpp"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

namespace EDEN3D {

	class D3DRenderer {

	public:
		D3DRenderer(const GameWindow*);
		~D3DRenderer();

	private:
		IDXGISwapChain *swapchain;
		ID3D11Device *dev;
		ID3D11DeviceContext *devcon;
	};
}
