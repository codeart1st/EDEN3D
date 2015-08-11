#pragma comment (lib, "d3d11.lib")

#include "GameApplication.hpp"
#include "Mesh.hpp"

namespace EDEN3D {

	Mesh::Mesh(vector<XMFLOAT3>& vertices, vector<XMFLOAT3>& indices) {

		pVBuffer = NULL;

		OurVertices = new VERTEX[3] {
			{ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(0.45f, -0.5, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
			{ XMFLOAT3(-0.45f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) }
		};

		D3D11_BUFFER_DESC bd = { 0 };

		bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
		bd.ByteWidth = sizeof(VERTEX) * 3;             // size is the VERTEX struct * 3
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

		GameApplication::device->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer

		// copy the vertices into the buffer
		D3D11_MAPPED_SUBRESOURCE ms;
		GameApplication::context->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, OurVertices, sizeof(VERTEX) * 3);
		GameApplication::context->Unmap(pVBuffer, NULL);
	}

	void Mesh::render() {

		// select which vertex buffer to display
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		GameApplication::context->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

		// select which primtive type we are using
		GameApplication::context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// draw the vertex buffer to the back buffer
		GameApplication::context->Draw(3, 0);
	}

	Mesh::~Mesh() {

		delete[] OurVertices;
		if (pVBuffer) {
			pVBuffer->Release();
		}
	}
}
