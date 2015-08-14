#pragma once

#include "EDEN3D.hpp"
#include "Renderer.hpp"
#include "GameWindow.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

namespace EDEN3D {

	class EDEN3D_API DefaultRenderer : public Renderer {

	public:
		DefaultRenderer(GameWindow&, const RendererOptions&);
		~DefaultRenderer();

		void render(Camera&, Mesh*);
		
	private:
		RendererOptions options;

		
		ID3D11DepthStencilView* pDepthStencilView;

		IDXGISwapChain* swapchain;
		ID3D11RenderTargetView* backbuffer;
		ID3D11InputLayout* pLayout;
		ID3D11VertexShader* pVS;
		ID3D11PixelShader* pPS;
	};
}
