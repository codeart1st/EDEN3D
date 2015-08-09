#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include "stdafx.h"

#include "GameWindow.hpp"
#include "Renderer.hpp"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

namespace EDEN3D {

	struct EDEN3D_API RendererOptions {
		FLOAT* clearColor;
	};

	struct EDEN3D_API VERTEX {
		FLOAT X, Y, Z;
		D3DXCOLOR Color;
	};

	class EDEN3D_API D3DRenderer : public Renderer {

	public:
		D3DRenderer(const GameWindow&, const RendererOptions&);
		~D3DRenderer();

		void render();

	private:
		void InitPipeline();
		void InitGraphics();
		
		RendererOptions options;

		IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
		ID3D11Device *dev;                     // the pointer to our Direct3D device interface
		ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
		ID3D11RenderTargetView *backbuffer;    // the pointer to our back buffer
		ID3D11InputLayout *pLayout;            // the pointer to the input layout
		ID3D11VertexShader *pVS;               // the pointer to the vertex shader
		ID3D11PixelShader *pPS;                // the pointer to the pixel shader
		ID3D11Buffer *pVBuffer;                // the pointer to the vertex buffer
	};
}
