#include "GameApplication.hpp"
#include "Mesh.hpp"

namespace EDEN3D {

	Mesh::Mesh(vector<VERTEX>& vertices, vector<DWORD>& indices) {

		vcount = vertices.size();
		icount = indices.size();

		D3D11_BUFFER_DESC bufferDesc = {};
		D3D11_SUBRESOURCE_DATA resourceData = {};

		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(VERTEX) * vcount;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		resourceData.pSysMem = &vertices[0];
		GameApplication::device->CreateBuffer(&bufferDesc, &resourceData, &VertexBuffer);

		bufferDesc.ByteWidth = sizeof(DWORD) * icount;
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		resourceData.pSysMem = &indices[0];
		GameApplication::device->CreateBuffer(&bufferDesc, &resourceData, &IndexBuffer);
	}

	void Mesh::render() {

		UINT stride = sizeof(VERTEX);
		UINT offset = 0;

		GameApplication::context->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
		GameApplication::context->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		GameApplication::context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		GameApplication::context->DrawIndexed(icount, 0, 0);
	}

	Mesh::~Mesh() {

		VertexBuffer->Release();
		IndexBuffer->Release();
	}
}