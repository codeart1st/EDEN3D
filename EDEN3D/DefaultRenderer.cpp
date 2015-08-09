#include "stdafx.h"
#include "DefaultRenderer.hpp"
#include "GameApplication.hpp"

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

		DXGI_SWAP_CHAIN_DESC scd = { 0 };

		scd.BufferCount = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.Width = window.getWidth();
		scd.BufferDesc.Height = window.getHeight();
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = window.hWnd;
		scd.SampleDesc.Count = 4;
		scd.Windowed = TRUE;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		IDXGIDevice* device = NULL;
		IDXGIAdapter* adapter = NULL;
		IDXGIFactory1* factory = 0;

		GameApplication::dev->QueryInterface(&device);
		device->GetAdapter(&adapter);
		adapter->GetParent(IID_PPV_ARGS(&factory));

		factory->CreateSwapChain(GameApplication::dev, &scd, &swapchain);

		// Set the viewport
		D3D11_VIEWPORT viewport = { 0 };

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = window.getWidth();
		viewport.Height = window.getHeight();

		GameApplication::devcon->RSSetViewports(1, &viewport);

		InitPipeline();
	}

	DefaultRenderer::~DefaultRenderer() {

		swapchain->SetFullscreenState(FALSE, NULL);

		pLayout->Release();
		pVS->Release();
		pPS->Release();
		swapchain->Release();
		backbuffer->Release();
	}

	void DefaultRenderer::InitPipeline() {

		// load and compile the two shaders
		ID3D10Blob *VS, *PS;
		D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
		D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

		// encapsulate both shaders into shader objects
		GameApplication::dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
		GameApplication::dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

		// create the input layout object
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		GameApplication::dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
		GameApplication::devcon->IASetInputLayout(pLayout);
	}

	void DefaultRenderer::render(const Camera& camera, Triangle& tri) {

		// set the shader objects
		GameApplication::devcon->VSSetShader(pVS, 0, 0);
		GameApplication::devcon->PSSetShader(pPS, 0, 0);

		// get the address of the back buffer
		ID3D11Texture2D *pBackBuffer;
		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		// use the back buffer address to create the render target
		GameApplication::dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
		pBackBuffer->Release();

		// set the render target as the back buffer
		GameApplication::devcon->OMSetRenderTargets(1, &backbuffer, NULL);

		GameApplication::devcon->ClearRenderTargetView(backbuffer, options.clearColor);

		tri.render();

		swapchain->Present(0, 0);
	}
}
