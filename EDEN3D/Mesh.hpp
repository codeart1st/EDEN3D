#pragma once

#include "EDEN3D.hpp"

namespace EDEN3D {
	
	typedef struct EDEN3D_API VERTEX {
		XMFLOAT3 Position;
		XMFLOAT4 Color;
	};

	class EDEN3D_API Mesh {

	public:
		Mesh(vector<XMFLOAT3>&, vector<WORD>&);
		~Mesh();

		void render();

	protected:
		ID3D11Buffer *pVBuffer;
		ID3D11Buffer *pIBuffer;

		unsigned int vcount, icount;
	};
}
