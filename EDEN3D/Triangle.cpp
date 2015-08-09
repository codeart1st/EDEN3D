#include "stdafx.h"
#include "Triangle.hpp"

#include "DefaultRenderer.hpp"

namespace EDEN3D {

	Triangle::Triangle() {

		pVBuffer = NULL;

		OurVertices = new VERTEX[3] {
			{ D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) },
			{ D3DXVECTOR3(0.45f, -0.5, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) },
			{ D3DXVECTOR3(-0.45f, -0.5f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) }
		};

		D3D11_BUFFER_DESC bd = { 0 };

		bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
		bd.ByteWidth = sizeof(VERTEX) * 3;             // size is the VERTEX struct * 3
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

		GameApplication::dev->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer

		// copy the vertices into the buffer
		D3D11_MAPPED_SUBRESOURCE ms;
		GameApplication::devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, OurVertices, sizeof(VERTEX) * 3);
		GameApplication::devcon->Unmap(pVBuffer, NULL);
	}

	void Triangle::render() {

		// select which vertex buffer to display
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		GameApplication::devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

		// select which primtive type we are using
		GameApplication::devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// draw the vertex buffer to the back buffer
		GameApplication::devcon->Draw(3, 0);
	}

	Triangle::~Triangle() {

		delete[] OurVertices;
		if (pVBuffer) {
			pVBuffer->Release();
		}
	}
}
