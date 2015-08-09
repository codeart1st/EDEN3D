#pragma once

#include "stdafx.h"

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

namespace EDEN3D {

	typedef struct EDEN3D_API VERTEX {
		D3DXVECTOR3 Position;
		D3DXCOLOR Color;
	};

	class EDEN3D_API Triangle {

	public:
		Triangle();
		~Triangle();

		void render();

	protected:
		VERTEX* OurVertices;
		ID3D11Buffer *pVBuffer;
	};
}
