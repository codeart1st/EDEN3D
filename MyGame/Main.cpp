#include <GameApplication.hpp>
#include <GameWindow.hpp>
#include <DefaultRenderer.hpp>
#include <PerspectiveCamera.hpp>
#include <Triangle.hpp>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	EDEN3D::GameApplication game(hInstance, L"Game.ico");

	EDEN3D::PerspectiveCamera camera1;
	EDEN3D::PerspectiveCamera camera2;

	EDEN3D::DefaultRenderer renderer1(EDEN3D::GameWindow(game, L"EDEN3D - MyGameWindow 1"), {
		D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f)
	});

	EDEN3D::DefaultRenderer renderer2(EDEN3D::GameWindow(game, L"EDEN3D - MyGameWindow 2"), {
		D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f)
	});

	EDEN3D::Triangle triangle;
	
	return game.run([&] () {

		// TODO: Detect user input
		// TODO: Update and animate scene objects
		renderer1.render(camera1, triangle);
		renderer2.render(camera2, triangle);
	});
}
