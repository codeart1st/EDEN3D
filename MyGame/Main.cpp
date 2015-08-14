#include <GameApplication.hpp>
#include <PerspectiveCamera.hpp>
#include <DefaultRenderer.hpp>
#include <WavefrontLoader.hpp>

#include <thread>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	EDEN3D::GameApplication game(hInstance, L"favicon.ico");
	EDEN3D::GameWindow window(game, L"EDEN3D - MyGameWindow");

	EDEN3D::PerspectiveCamera camera(XMConvertToRadians(45), window.getWidth() / (float)window.getHeight(), 0.01f, 100.0f);
	camera.position(0.0f, 0.0f, -10.0f);
	
	EDEN3D::DefaultRenderer renderer(window, {
		EDEN3D::Color(0.15f, 0.15f, 0.15f, 1.0f)
	});

	EDEN3D::Mesh* mesh = NULL;
	
	thread load(EDEN3D::WavefrontLoader::load, "Bunny.obj", [&] (EDEN3D::Mesh* created) {
		// load the model asynchronous
		mesh = created;
	});
	
	int exit = game.run([&] () {

		renderer.render(camera, mesh);
	});

	load.join();

	delete mesh;
	return exit;
}
