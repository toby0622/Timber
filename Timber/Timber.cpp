// SFML Libraries
#include <SFML/Graphics.hpp>
#include <sstream>
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

	// Track Game Running
	bool paused = true;

	// Text Draw
	int score = 0;
	Text messageText;
	Text scoreText;

	// Font Selection
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	// Font Setup for Texts
	messageText.setFont(font);
	scoreText.setFont(font);

	// Assign Messages
	messageText.setString("Press Enter To Start!");
	scoreText.setString("Score = 0");

	// Font Size Selection
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	// Font Color Selection
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	// Text Positioning
	// Set the Center of "messageText" to the Center of The Screen
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	// Changing the Message Changes the Size of "messageText"
	// The Origin Needs to be Recalculated
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	while (window.isOpen()) {
		// Game Exit Key Command
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		// Game Start Key Command
		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			paused = false;
		}
		
		if (!paused) {
			// Time Measurement
			Time deltaTime = clock.restart();

			// Bee Setup
			if (!beeActive) {
				// How Fast the Bee
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;

				// How High the Bee
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else {
				// Move the Bee
				spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * deltaTime.asSeconds()), spriteBee.getPosition().y);

				// Edge Limitation
				if (spriteBee.getPosition().x < (-100)) {
					// New Bee Object Waiting to Setup
					beeActive = false;
				}
			}

			// Cloud Setup
			// Cloud 1
			if (!cloud1Active) {
				// How Fast the Cloud
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				// How High the Cloud
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}
			else {
				// Move the Cloud
				spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * deltaTime.asSeconds()), spriteCloud1.getPosition().y);

				// Edge Limitation
				if (spriteCloud1.getPosition().x > 1920) {
					// New Cloud Object Waiting to Setup
					cloud1Active = false;
				}
			}

			// Cloud 2
			if (!cloud2Active) {
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else {
				spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * deltaTime.asSeconds()), spriteCloud2.getPosition().y);

				if (spriteCloud2.getPosition().x > 1920) {
					cloud2Active = false;
				}
			}

			// Cloud 3
			if (!cloud3Active) {
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else {
				spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * deltaTime.asSeconds()), spriteCloud3.getPosition().y);

				if (spriteCloud3.getPosition().x > 1920) {
					cloud3Active = false;
				}
			}

			// Update Score Text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());
		} // End of Paused

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
