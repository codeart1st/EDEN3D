#include "MouseControls.hpp"
#include "GameApplication.hpp"

namespace EDEN3D {

	MouseControls::MouseControls(const GameWindow& window) {

		mouse = NULL;

		GameApplication::directInput->CreateDevice(GUID_SysMouse, &mouse, NULL);
		mouse->SetCooperativeLevel(window.getHandle(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
		mouse->SetDataFormat(&c_dfDIMouse);
		mouse->Acquire();
	}

	MouseControls::~MouseControls() {

		mouse->Release();
	}
}
