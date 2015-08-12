#include <GameApplication.hpp>
#include <PerspectiveCamera.hpp>
#include <DefaultRenderer.hpp>
#include <WavefrontLoader.hpp>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	EDEN3D::GameApplication game(hInstance, L"game.ico");
	EDEN3D::PerspectiveCamera camera;

	EDEN3D::DefaultRenderer renderer1(EDEN3D::GameWindow(game, L"EDEN3D - MyGameWindow 1"), {
		EDEN3D::Color(0.15f, 0.15f, 0.15f, 1.0f)
	});

	EDEN3D::DefaultRenderer renderer2(EDEN3D::GameWindow(game, L"EDEN3D - MyGameWindow 1"), {
		EDEN3D::Color(1.0f, 1.0f, 0.0f, 1.0f)
	});

	EDEN3D::Mesh* mesh = EDEN3D::WavefrontLoader::load("Teapot.obj");
	
	int exit = game.run([&] () {

		renderer1.render(camera, *mesh);
		renderer2.render(camera, *mesh);
	});

	delete mesh;
	return exit;
}
