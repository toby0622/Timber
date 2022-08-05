#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
using namespace sf;

void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

// Position Description for Branches and Player
enum class side {
	LEFT, RIGHT, NONE
};
side branchPositions[NUM_BRANCHES];

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

	// Time Indicator Bar
	RectangleShape timeBar; // Create Simple Rectangle
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight)); // Center in Horizontal Fashion
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

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

	// Branches Prepare
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	// Set Texture for Branches
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}

	// Player Creation
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);

	// Player Starting Point
	side playerSide = side::LEFT;

	// Gravestone Creation
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	// Axe Creation
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	// Line Up the Axe with the Tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	// Flying Log Creation
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	// Log Related Variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	// Player Input Control
	bool acceptInput = false;

	// Audio Effect Preparation

	// Tree Chopping Sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	// Meet the End (Player Squished)
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	// Meet the End (Time Out)
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	while (window.isOpen()) {
		Event event;

		while (window.pollEvent(event)) {
			if (event.type == Event::KeyReleased && !paused) {
				// Continue the Next Key Press
				acceptInput = true;

				// Hide the Axe
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}
		
		// Game Exit Key Command
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		// Game Start Key Command
		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			paused = false;

			// New Game Start (Reseting the Time and Score)
			score = 0;
			timeRemaining = 6;

			// Remove All the Branches Starting in the Second Position
			for (int i = 1; i < NUM_BRANCHES; i++) {
				branchPositions[i] = side::NONE;
			}

			// Hide the Gravestone
			spriteRIP.setPosition(675, 2000);

			// Move the Player to the Starting Position
			spritePlayer.setPosition(580, 720);

			acceptInput = true;
		}

		// Player Control Enable (Accept Input)
		if (acceptInput) {
			// Handle the Right Cursor Key
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				// Make Sure the Player is on the Right
				playerSide = side::RIGHT;
				score++;

				// Add to the Amount of Time Remaining
				timeRemaining += (2 / score) + 0.15;
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200, 720);

				// Update the Branches
				updateBranches(score);

				// Setup the Flying Log to the Left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				// Play Sound Effect
				chop.play();
			}

			// Handel the Left Cursor Key
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				// Make Sure the Player is on the Left
				playerSide = side::LEFT;
				score++;

				// Add to the Amount of Time Remaining
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(580, 720);

				// Update the Branches
				updateBranches(score);

				// Setup the Flying Log to the Left
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;

				// Play Sound Effect
				chop.play();
			}
		}

		if (!paused) {
			// Time Measurement
			Time deltaTime = clock.restart();

			// Remaining Time Setup
			timeRemaining -= deltaTime.asSeconds(); // Subtract the Time Player has Used
			// Adjust the Bar Size Based on Remaining Time
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight)); 

			// Running Out of Time
			if (timeRemaining <= 0.0f) {
				// Game Pause
				paused = true;

				// Change the Message
				messageText.setString("Out of time!!!");

				// New Size Text Reposition
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				// Play Sound Effect
				outOfTime.play();
			}

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

			// Update Branch Sprites
			for (int i = 0; i < NUM_BRANCHES; i++) {
				float height = i * 150;

				if (branchPositions[i] == side::LEFT) {
					// Move Sprite to the Left
					branches[i].setPosition(610, height);

					// Flip the Sprite Round the Other Way
					branches[i].setRotation(180);
				} else if (branchPositions[i] == side::RIGHT) {
					// Move Sprite to the Right
					branches[i].setPosition(1330, height);

					// Set Sprite Rotation to Normal
					branches[i].setRotation(0);
				} else {
					// Hide Branches
					branches[i].setPosition(3000, height);
				}
			}

			// Handle the Flying Log
			if (logActive) {
				spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * deltaTime.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * deltaTime.asSeconds()));

				// Log Reach the Edge
				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000) {
					// Setup a New Log
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			// Player Squished by the Branch
			if (branchPositions[5] == playerSide) {
				// Game Over
				paused = true;
				acceptInput = false;

				// Draw the GraveStone
				spriteRIP.setPosition(525, 760);

				// Hide the Player
				spritePlayer.setPosition(2000, 660);

				// Change the Message
				messageText.setString("SQUISHED!!");

				// Center the New Message
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				// Play Sound Effect
				death.play();
			}
		}

		// Last Frame Clear
		window.clear();

		// Game Scene Draw
		window.draw(spriteBackground);

		// Cloud Object Draw (Cloud Behind Tree)
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		// Branches Draw
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}

		// Draw the Tree
		window.draw(spriteTree);

		// Draw the Player
		window.draw(spritePlayer);

		// Draw the Axe
		window.draw(spriteAxe);

		// Draw the Flying Log
		window.draw(spriteLog);

		// Draw the Gravestone
		window.draw(spriteRIP);

		// Draw the Bee
		window.draw(spriteBee);

		// Score HUD Output
		window.draw(scoreText);

		// Time Bar Draw
		window.draw(timeBar);

		if (paused) {
			// Message Output
			window.draw(messageText);
		}

		// Game Display
		window.display();
	}

	return 0;
}

void updateBranches(int seed) {
	// Move All Branches Down One Place
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}

	// Spawn New Branch at Position '0'
	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}
