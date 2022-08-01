// SFML Libraries
#include <SFML/Graphics.hpp>
// Using Namespace "sf"
using namespace sf;

int main() {
	// VideoMode Object Create
	VideoMode vm(1920, 1080);

	// Game Window Create
	RenderWindow window(vm, "Timber!!! Imitation", Style::Fullscreen);

	// Graphic Texture Holder Create
	Texture textureBackground;

	// Load Graphic to Texture
	textureBackground.loadFromFile("graphics/background.png");

	// Sprite Create
	Sprite spriteBackground;

	// Attack Texture to Sprite
	spriteBackground.setTexture(textureBackground);

	// Screen Cover with spriteBackground
	spriteBackground.setPosition(0, 0);

	while (window.isOpen()) {
		// Player Input Handle
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		
		// Scene Update

		// Last Frame Clear
		window.clear();

		// Scene Draw
		window.draw(spriteBackground);
		
		// Game Display
		window.display();
	}

	return 0;
}
