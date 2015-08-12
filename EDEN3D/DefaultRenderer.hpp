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

		void render(const Camera&, Mesh&);
		
	private:
		void InitPipeline();
		
		RendererOptions options;

		IDXGISwapChain* swapchain;
		ID3D11RenderTargetView* backbuffer;
		ID3D11InputLayout* pLayout;
		ID3D11VertexShader* pVS;
		ID3D11PixelShader* pPS;

		ID3D11Buffer* pCBuffer;

		XMMATRIX g_World;
		XMMATRIX g_View;
		XMMATRIX g_Projection;

		struct ConstantBuffer {

			XMMATRIX mWorld;
			XMMATRIX mView;
			XMMATRIX mProjection;
		} ConstantBuffer;
	};
}
