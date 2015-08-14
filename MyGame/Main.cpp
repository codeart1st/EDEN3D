#include <GameApplication.hpp>
#include <PerspectiveCamera.hpp>
#include <DefaultRenderer.hpp>
#include <WavefrontLoader.hpp>
#include <MouseControls.hpp>

#include <thread>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	
	EDEN3D::GameApplication game(hInstance, L"favicon.ico");
	EDEN3D::GameWindow window(game, L"EDEN3D - MyGameWindow");

	EDEN3D::PerspectiveCamera camera(XMConvertToRadians(45), window.getWidth() / (float)window.getHeight(), 0.01f, 100.0f);
	camera.position(0.0f, 0.0f, -10.0f);
	
	EDEN3D::DefaultRenderer renderer(window, {
		EDEN3D::Color(0.15f, 0.15f, 0.15f, 1.0f)
	});

	EDEN3D::MouseControls controls(window);

	EDEN3D::Mesh* mesh = NULL;
	
	thread load([&] {
		// load the model asynchronous
		EDEN3D::WavefrontLoader::load(L"Bunny.obj", &mesh);
	});
	
	int exit = game.run([&] {
		// game loop

		/* controls.update([&] (int x, int y, int button) {
		   });
		*/
		renderer.render(camera, mesh);
	});

	load.join();

	delete mesh;
	return exit;
}
