#include "PerspectiveCamera.hpp"
#include "GameApplication.hpp"

namespace EDEN3D {

	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float n, float f) : Camera() {

		D3D11_BUFFER_DESC bd = {};

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ConstantBuffer);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		GameApplication::device->CreateBuffer(&bd, NULL, &pCBuffer);

		Eye = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
		At = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		g_View = XMMatrixLookAtLH(Eye, At, Up);
		g_World = XMMatrixIdentity();
		g_Projection = XMMatrixPerspectiveFovLH(fov, aspect, n, f);
	}

	PerspectiveCamera::~PerspectiveCamera() {

		pCBuffer->Release();
	}

	void PerspectiveCamera::position(float x, float y, float z) {

		Eye = XMVectorSet(x, y, z, 0.0f);
		g_View = XMMatrixLookAtLH(Eye, At, Up);
	}

	void PerspectiveCamera::rotation(float x, float y, float z) {
		
		XMVECTOR _Eye = Eye;

		// Set rotation of the three axis
		_Eye = XMVector3Transform(_Eye, XMMatrixRotationNormal(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), x));
		_Eye = XMVector3Transform(_Eye, XMMatrixRotationNormal(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), y));
		_Eye = XMVector3Transform(_Eye, XMMatrixRotationNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), z));

		g_View = XMMatrixLookAtLH(_Eye, At, Up);
	}

	void PerspectiveCamera::render() {
		/*static float t = 0.0f;
		static DWORD dwTimeStart = 0;
		DWORD dwTimeCur = GetTickCount();
		if (dwTimeStart == 0)
			dwTimeStart = dwTimeCur;
		t = (dwTimeCur - dwTimeStart) / 1000.0f;

		g_World = XMMatrixRotationY(t);
		g_World *= XMMatrixScaling(2.0f, 2.0f, 2.0f);
		g_World *= XMMatrixTranslation(0.0f, -2.0f, 0.0f);*/

		ConstantBuffer.mWorld = XMMatrixTranspose(g_World);
		ConstantBuffer.mView = XMMatrixTranspose(g_View);
		ConstantBuffer.mProjection = XMMatrixTranspose(g_Projection);
		GameApplication::context->UpdateSubresource(pCBuffer, 0, NULL, &ConstantBuffer, 0, 0);
		GameApplication::context->VSSetConstantBuffers(0, 1, &pCBuffer);
	}

	void PerspectiveCamera::rotateX(float x) {
		Eye = XMVector3Transform(Eye, XMMatrixRotationNormal(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), x));
		g_View = XMMatrixLookAtLH(Eye, At, Up);
	}

	void PerspectiveCamera::rotateY(float y) {
		Eye = XMVector3Transform(Eye, XMMatrixRotationNormal(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), y));
		g_View = XMMatrixLookAtLH(Eye, At, Up);
	}

	void PerspectiveCamera::rotateZ(float z) {
		Eye = XMVector3Transform(Eye, XMMatrixRotationNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), z));
		g_View = XMMatrixLookAtLH(Eye, At, Up);
	}

	void PerspectiveCamera::translateX(float x) {
		// TODO
	}

	void PerspectiveCamera::translateY(float y) {
		// TODO
	}

	void PerspectiveCamera::translateZ(float z) {
		// TODO
	}
}
