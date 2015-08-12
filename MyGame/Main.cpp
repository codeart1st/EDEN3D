#include <GameApplication.hpp>
#include <PerspectiveCamera.hpp>
#include <DefaultRenderer.hpp>
#include <WavefrontLoader.hpp>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	EDEN3D::GameApplication game(hInstance, L"game.ico");
	EDEN3D::PerspectiveCamera camera;

	EDEN3D::DefaultRenderer renderer(EDEN3D::GameWindow(game, L"EDEN3D - MyGameWindow"), {
		EDEN3D::Color(0.15f, 0.15f, 0.15f, 1.0f)
	});

	EDEN3D::Mesh* mesh = EDEN3D::WavefrontLoader::load("Dragon.obj");
	
	int exit = game.run([&] () {

		renderer.render(camera, *mesh);
	});

	delete mesh;
	return exit;
}
