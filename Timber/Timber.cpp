// SFML Libraries
#include <SFML/Graphics.hpp>
// Using Namespace "sf"
using namespace sf;

int main() {
	// VideoMode Object Create
	VideoMode vm(1920, 1080);

	// Game Window Create
	RenderWindow window(vm, "Timber Man!!!", Style::Fullscreen);

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

	// Tree Sprite Create
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// Bee Create
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	// Bee Movement
	bool beeActive = false;

	// Bee Movement Speed
	float beeSpeed = 0.0f;

	// Cloud Create
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");

	// Three Cloud Sprites
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	// Cloud Positioning
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);

	// Cloud Movement
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	// Cloud Movement Speed
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Time Control
	Clock clock;

	while (window.isOpen()) {
		// Player Input Handle
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		
		// Time Measurement
		Time dt = clock.restart();

		// Last Frame Clear
		window.clear();

		// Game Scene Draw
		window.draw(spriteBackground);

		// Cloud Object Draw (Cloud Behind Tree)
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		
		// Tree Object Draw
		window.draw(spriteTree);

		// Bee Object Draw (Bee Ahead Tree)
		window.draw(spriteBee);

		// Game Display
		window.display();
	}

	return 0;
}
