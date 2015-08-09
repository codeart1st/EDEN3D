#include "D3DRenderer.hpp"

namespace EDEN3D {

	D3DRenderer::D3DRenderer(const GameWindow& window, const RendererOptions& options) {

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

		D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &scd, &swapchain, &dev, NULL, &devcon);

		// get the address of the back buffer
		ID3D11Texture2D *pBackBuffer;
		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		// use the back buffer address to create the render target
		dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
		pBackBuffer->Release();

		// set the render target as the back buffer
		devcon->OMSetRenderTargets(1, &backbuffer, NULL);

		// Set the viewport
		D3D11_VIEWPORT viewport = { 0 };

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = window.getWidth();
		viewport.Height = window.getHeight();

		devcon->RSSetViewports(1, &viewport);

		InitPipeline();
		InitGraphics();
	}

	void D3DRenderer::InitPipeline() {

		// load and compile the two shaders
		ID3D10Blob *VS, *PS;
		D3DX11CompileFromFile("shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
		D3DX11CompileFromFile("shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

		// encapsulate both shaders into shader objects
		dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
		dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

		// set the shader objects
		devcon->VSSetShader(pVS, 0, 0);
		devcon->PSSetShader(pPS, 0, 0);

		// create the input layout object
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
		devcon->IASetInputLayout(pLayout);
	}

	void D3DRenderer::InitGraphics() {

		// create a triangle using the VERTEX struct
		VERTEX OurVertices[] =
		{
			{ 0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) },
			{ 0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) },
			{ -0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) }
		};
		
		// create the vertex buffer
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
		bd.ByteWidth = sizeof(VERTEX) * 3;             // size is the VERTEX struct * 3
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

		dev->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer


		// copy the vertices into the buffer
		D3D11_MAPPED_SUBRESOURCE ms;
		devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
		memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // copy the data
		devcon->Unmap(pVBuffer, NULL);                                      // unmap the buffer
	}

	D3DRenderer::~D3DRenderer() {

		swapchain->SetFullscreenState(FALSE, NULL);

		pLayout->Release();
		pVS->Release();
		pPS->Release();
		pVBuffer->Release();
		swapchain->Release();
		backbuffer->Release();
		dev->Release();
		devcon->Release();
	}

	void D3DRenderer::render() {

		// clear the back buffer to a deep blue
		devcon->ClearRenderTargetView(backbuffer, options.clearColor);

			// select which vertex buffer to display
			UINT stride = sizeof(VERTEX);
			UINT offset = 0;
			devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

			// select which primtive type we are using
			devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// draw the vertex buffer to the back buffer
			devcon->Draw(3, 0);

		// switch the back buffer and the front buffer
		swapchain->Present(0, 0);
	}
}
