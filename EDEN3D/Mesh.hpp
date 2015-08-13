#pragma once

#include "EDEN3D.hpp"

namespace EDEN3D {
	
	typedef struct EDEN3D_API VERTEX {
		XMFLOAT3 Position;
		XMFLOAT3 Normal;
	};

	class EDEN3D_API Mesh {

	public:
		Mesh(vector<VERTEX>&, vector<DWORD>&);
		~Mesh();

		void render();

	protected:
		ID3D11Buffer* VertexBuffer;
		ID3D11Buffer* IndexBuffer;

		unsigned int vcount, icount;
	};
}
