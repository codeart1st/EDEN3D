#pragma once

#include "EDEN3D.hpp"

namespace EDEN3D {
	
	typedef struct EDEN3D_API VERTEX {
		XMFLOAT3 Position;
		XMFLOAT4 Color;
	};

	class EDEN3D_API Mesh {

	public:
		Mesh(vector<XMFLOAT3>&, vector<XMFLOAT3>&);
		~Mesh();

		void render();

	protected:
		VERTEX* OurVertices;
		ID3D11Buffer *pVBuffer;
	};
}
