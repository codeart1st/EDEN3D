#include "GameApplication.hpp"
#include "GameWindow.hpp"
#include "D3DRenderer.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	EDEN3D::GameApplication game(hInstance);
	EDEN3D::GameWindow window(game, L"GameWindow", 640, 480, L"Game.ico");

	EDEN3D::D3DRenderer renderer(window, {
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f)
	});
	
	int exit = game.run([&renderer]() {

		// TODO: Detect user input
		// TODO: Update and animate scene objects
		renderer.render();
	});

	// Clean up stuff

	return exit;
}
