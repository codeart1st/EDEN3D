#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")

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

		DXGI_SWAP_CHAIN_DESC scd = { 0 };

		scd.BufferCount = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.Width = window.getWidth();
		scd.BufferDesc.Height = window.getHeight();
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = window.hWnd;
		scd.SampleDesc.Count = 8;
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
		D3D11_VIEWPORT viewport = { 0 };

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.Width = window.getWidth();
		viewport.Height = window.getHeight();

		GameApplication::context->RSSetViewports(1, &viewport);

		InitPipeline();
	}

	DefaultRenderer::~DefaultRenderer() {

		swapchain->SetFullscreenState(FALSE, NULL);

		pCBuffer->Release();
		pLayout->Release();
		pVS->Release();
		pPS->Release();
		swapchain->Release();
		backbuffer->Release();
	}

	void DefaultRenderer::InitPipeline() {

		pCBuffer = NULL;

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
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		GameApplication::device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
		GameApplication::context->IASetInputLayout(pLayout);

		// get the address of the back buffer
		ID3D11Texture2D *pBackBuffer;
		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		// use the back buffer address to create the render target
		GameApplication::device->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
		pBackBuffer->Release();

		D3D11_BUFFER_DESC bd = { 0 };

		// Create the constant buffer
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ConstantBuffer);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		GameApplication::device->CreateBuffer(&bd, NULL, &pCBuffer);

		// Initialize the world matrix
		g_World = XMMatrixIdentity();

		// Initialize the view matrix
		XMVECTOR Eye = XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f);
		XMVECTOR At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		g_View = XMMatrixLookAtLH(Eye, At, Up);

		// Initialize the projection matrix
		g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, 640 / (FLOAT)480, 0.01f, 100.0f);
	}

	void DefaultRenderer::render(const Camera& camera, Mesh& tri) {

		// set the shader objects
		GameApplication::context->VSSetShader(pVS, 0, 0);
		GameApplication::context->PSSetShader(pPS, 0, 0);
		
		// set the render target as the back buffer
		GameApplication::context->OMSetRenderTargets(1, &backbuffer, NULL);

		FLOAT color[4] = {
			options.clearColor.r,
			options.clearColor.g,
			options.clearColor.b,
			options.clearColor.a
		};

		GameApplication::context->ClearRenderTargetView(backbuffer, color);

		static float t = 0.0f;
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;

		g_World = XMMatrixRotationY(t);
		g_World *= XMMatrixScaling(0.5f, 0.5f, 0.5f);
		g_World *= XMMatrixTranslation(0.0f, -2.0f, 0.0f);

		ConstantBuffer.mWorld = XMMatrixTranspose(g_World);
		ConstantBuffer.mView = XMMatrixTranspose(g_View);
		ConstantBuffer.mProjection = XMMatrixTranspose(g_Projection);
		GameApplication::context->UpdateSubresource(pCBuffer, 0, NULL, &ConstantBuffer, 0, 0);
		GameApplication::context->VSSetConstantBuffers(0, 1, &pCBuffer);

		tri.render();

		swapchain->Present(0, 0);
	}
}
