#include <windows.h>

#include "GameApplication.hpp"
#include "GameWindow.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	EDEN3D::GameApplication game(hInstance);

	EDEN3D::GameWindow window1(game, "Main App Window 1");
	EDEN3D::GameWindow window2(game, "Main App Window 2");

	//EDEN3D::D3DRenderer(window1);

	game.run([]() {

		// update - animate
		// renderer.render(scene, camera);
	});

	return ERROR_SUCCESS;
}
