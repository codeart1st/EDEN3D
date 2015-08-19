#pragma once

#include "EDEN3D.hpp"
#include "Camera.hpp"

namespace EDEN3D {

	class EDEN3D_API PerspectiveCamera : public Camera {

	public:
		PerspectiveCamera(float, float, float, float);
		~PerspectiveCamera();

		void render();

		void position(float, float, float);
		void rotation(float, float, float);

		void rotateX(float);
		void rotateY(float);
		void rotateZ(float);

		void translateX(float);
		void translateY(float);
		void translateZ(float);

	protected:
		ID3D11Buffer* pCBuffer;

		XMMATRIX g_World;
		XMMATRIX g_View;
		XMMATRIX g_Projection;
		XMVECTOR Eye, At, Up;

		struct ConstantBuffer {

			XMMATRIX mWorld;
			XMMATRIX mView;
			XMMATRIX mProjection;
		} ConstantBuffer;
	};
}
