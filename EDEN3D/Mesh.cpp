#pragma comment (lib, "d3d11.lib")

#include "GameApplication.hpp"
#include "Mesh.hpp"

namespace EDEN3D {

	const int vcount = 8;
	const int icount = 36;

	Mesh::Mesh(vector<XMFLOAT3>& vertices, vector<XMFLOAT3>& indices) {

		pVBuffer = NULL;
		pIBuffer = NULL;

		VERTEX OurVertices[vcount] = {
			{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
			{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		};

		WORD OurIndices[icount] =
		{
			3, 1, 0,
			2, 1, 3,

			0, 5, 4,
			1, 5, 0,

			3, 4, 7,
			0, 4, 3,

			1, 6, 5,
			2, 6, 1,

			2, 7, 6,
			3, 7, 2,

			6, 4, 5,
			7, 4, 6,
		};

		D3D11_BUFFER_DESC bd = { 0 };

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX) * vcount;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = { 0 };
		InitData.pSysMem = OurVertices;
		GameApplication::device->CreateBuffer(&bd, &InitData, &pVBuffer);

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * icount;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		InitData.pSysMem = OurIndices;
		GameApplication::device->CreateBuffer(&bd, &InitData, &pIBuffer);
	}

	void Mesh::render() {

		// select which vertex buffer to display
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		GameApplication::context->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
		GameApplication::context->IASetIndexBuffer(pIBuffer, DXGI_FORMAT_R16_UINT, 0);

		// select which primtive type we are using
		GameApplication::context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// draw the vertex buffer to the back buffer
		GameApplication::context->DrawIndexed(icount, 0, 0);
	}

	Mesh::~Mesh() {

		if (pVBuffer) {
			pVBuffer->Release();
		}

		if (pIBuffer) {
			pIBuffer->Release();
		}
	}
}