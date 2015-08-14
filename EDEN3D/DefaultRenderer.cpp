#include "DefaultRenderer.hpp"

namespace EDEN3D {

	DefaultRenderer::DefaultRenderer(GameWindow& window, const RendererOptions& options) {

		if (window.inUse) {

			int ret = MessageBox(
				NULL,
				L"GameWindow already linked with a renderer.",
				L"ERROR",
				MB_ICONERROR | MB_OK);

			exit(EXIT_FAILURE);

		} else {
			window.inUse = true;
		}

		this->options = options;

		DXGI_SWAP_CHAIN_DESC scd = {};

		scd.BufferCount = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.Width = window.getWidth();
		scd.BufferDesc.Height = window.getHeight();
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = window.hWnd;
		scd.SampleDesc.Count = 1;
		scd.Windowed = TRUE;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		IDXGIDevice* device = NULL;
		IDXGIAdapter* adapter = NULL;
		IDXGIFactory1* factory = 0;

		GameApplication::device->QueryInterface(&device);
		device->GetAdapter(&adapter);
		adapter->GetParent(IID_PPV_ARGS(&factory));

		factory->CreateSwapChain(GameApplication::device, &scd, &swapchain);

		// TODO: Das sollte im render prozess geupdated werden -> unterschiedliche fenstergrößen
		// oder mehrere contexte nutzen?
		D3D11_VIEWPORT viewport = {};

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.Width = window.getWidth();
		viewport.Height = window.getHeight();

		GameApplication::context->RSSetViewports(1, &viewport);

		// load and compile the two shaders
		ID3D10Blob *VS, *PS;
		D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
		D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

		// encapsulate both shaders into shader objects
		GameApplication::device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
		GameApplication::device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

		// create the input layout object
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		GameApplication::device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
		GameApplication::context->IASetInputLayout(pLayout);

		// get the address of the back buffer
		ID3D11Texture2D *pBackBuffer;
		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		// use the back buffer address to create the render target
		GameApplication::device->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
		pBackBuffer->Release();

		D3D11_TEXTURE2D_DESC descDepth = {};

		descDepth.Width = window.getWidth();
		descDepth.Height = window.getHeight();
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count = 1;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		ID3D11Texture2D* pDepthStencil;
		GameApplication::device->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
		GameApplication::device->CreateDepthStencilView(pDepthStencil, &descDSV, &pDepthStencilView);
		pDepthStencil->Release();
	}

	DefaultRenderer::~DefaultRenderer() {

		swapchain->SetFullscreenState(FALSE, NULL);
		
		pDepthStencilView->Release();
		pLayout->Release();
		pVS->Release();
		pPS->Release();
		swapchain->Release();
		backbuffer->Release();
	}

	void DefaultRenderer::render(Camera& camera, EDEN3D::Mesh* mesh) {

		// set the shader objects
		GameApplication::context->VSSetShader(pVS, 0, 0);
		GameApplication::context->PSSetShader(pPS, 0, 0);
		
		// set the render target as the back buffer
		GameApplication::context->OMSetRenderTargets(1, &backbuffer, pDepthStencilView);

		FLOAT color[4] = {
			options.clearColor.r,
			options.clearColor.g,
			options.clearColor.b,
			options.clearColor.a
		};

		GameApplication::context->ClearRenderTargetView(backbuffer, color);
		GameApplication::context->ClearDepthStencilView(pDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);

		camera.render();
		if (mesh) mesh->render();

		swapchain->Present(0, 0);
	}
}
