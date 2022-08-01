// SFML Libraries
#include <SFML/Graphics.hpp>
// Using Namespace "sf"
using namespace sf;

int main() {
	// VideoMode Object Create
	VideoMode vm(1920, 1080);

	// Game Window Create
	RenderWindow window(vm, "Timber!!! Imitation", Style::Fullscreen);

	while (window.isOpen()) {
		// Player Input Handle
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		
		// Scene Update

		// Scene Draw

		// Last Frame Clear
		window.clear();

		// Scene Draw
		
		// Game Display
		window.display();
	}

	return 0;
}
