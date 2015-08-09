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

	class EDEN3D_API DefaultRenderer : public Renderer {

	public:
		DefaultRenderer(GameWindow&, const RendererOptions&);
		~DefaultRenderer();

		void render(const Camera&, Triangle&);
		
	private:
		void InitPipeline();
		
		RendererOptions options;

		IDXGISwapChain* swapchain;             // the pointer to the swap chain interface
		ID3D11RenderTargetView* backbuffer;    // the pointer to our back buffer
		ID3D11InputLayout* pLayout;            // the pointer to the input layout
		ID3D11VertexShader* pVS;               // the pointer to the vertex shader
		ID3D11PixelShader* pPS;                // the pointer to the pixel shader
	};
}
