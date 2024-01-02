#include "gameMode.h"

GameMode::GameMode(const std::string& level)
	: window(sf::VideoMode(1400, 700), "Game Display"),
	wordFallSpeed(35), // 35
	createTimer(0),
	createInterval(5.5), // 5.5
	gameTimeLimit(63),
	userLevel(level) {
	gameBox.setSize(sf::Vector2f(1300, 490));
	sf::FloatRect boxRect = gameBox.getLocalBounds();
	gameBox.setPosition((window.getSize().x - boxRect.width) / 2, (window.getSize().y - boxRect.height) / 2 + 100);
	gameBox.setFillColor(sf::Color(0, 0, 0, 145));
	gameBox.setOutlineThickness(2);
	gameBox.setOutlineColor(sf::Color::White);
	run();
}

void GameMode::run() {
	createDisplay();
	createBox();
	render();
	createDictionary();
	initializeRandomSeed();
	sound();
	while (window.isOpen()) {
		germanBoxContent.setOrigin(germanBoxContent.getLocalBounds().width / 2 - 150, germanBoxContent.getLocalBounds().height / 2 - 12); // always on the middle
		updateFallingWords(wordClock.restart().asSeconds());
		handleEvents();
		render();
	}
}

void GameMode::sound() {
	if (!correctBuffer.loadFromFile("media/point.ogg")) {
		std::cerr << "Failed to load point.ogg!" << std::endl;
	}
	if (!bombBuffer.loadFromFile("media/bomb.ogg")) {
		std::cerr << "Failed to load bomb.ogg!" << std::endl;
	}
	if (!musicBuffer.loadFromFile("media/music.ogg")) {
		std::cerr << "Failed to load music.ogg!" << std::endl;
	}
	musicSound.setBuffer(musicBuffer);
	musicSound.setVolume(60);
	musicSound.play();
}

void GameMode::createDictionary() {
	std::ifstream file("words/words.txt");
	std::vector<std::string> sentences;

	std::string line;
	bool isCorrectLevel = false;

	while (std::getline(file, line)) {
		if (line == userLevel) {
			isCorrectLevel = true;
		}
		else if (isCorrectLevel && line.empty()) {
			break;
		}
		else if (isCorrectLevel) {
			line = line.substr(line.find_first_of(" ") + 1);
			size_t delimiterPos = line.find(" - ");
			std::string german = line.substr(0, delimiterPos);
			std::string english = line.substr(delimiterPos + 3);

			dictionary[german] = english;
		}
		else if (userLevel == "All" &&
			(line.find("A1") != std::string::npos ||
				line.find("A2") != std::string::npos ||
				line.find("B2") != std::string::npos ||
				line.find("B1") != std::string::npos ||
				line.find("C1") != std::string::npos ||
				line.empty())) {
			continue;
		}
		else if (userLevel == "All" &&
			!(line.find("A1") != std::string::npos ||
				line.find("A2") != std::string::npos ||
				line.find("B2") != std::string::npos ||
				line.find("B1") != std::string::npos ||
				line.find("C1") != std::string::npos ||
				line.empty())) {
			size_t delimiterPos = line.find(" - ");
			std::string german = line.substr(0, delimiterPos);
			std::string english = line.substr(delimiterPos + 3);
			dictionary[german] = english;
		}
	}
	std::cerr << "Create dictionary of " << userLevel << std::endl;
}

void GameMode::createDisplay() {
	if (!bombTexture.loadFromFile("media/bomb.png")) {
		std::cerr << "Failed to load profile.png!" << std::endl;
	}
	bombSprite.setTexture(bombTexture);
	bombSprite.setScale(0.9f, 0.9f);
	bombSprite.setPosition(-130, -200); // right, down

	if (!m_font.loadFromFile("font/hangthedj.ttf")) {
		std::cerr << "Failed to load font!" << std::endl;
	}
	mainText.setString("Word Bomb");
	mainText.setFont(m_font);
	mainText.setCharacterSize(70);
	mainText.setFillColor(sf::Color::White);
	sf::FloatRect textRect = mainText.getLocalBounds();
	mainText.setPosition((window.getSize().x - textRect.width) / 2, (window.getSize().y - textRect.height) / 2 - 270);
	subText.setString("   Input the correct German word & article \n before the English word falls to the ground  ");
	subText.setFont(m_font);
	subText.setCharacterSize(30);
	subText.setFillColor(sf::Color::White);
	sf::FloatRect managerRect = subText.getLocalBounds();
	subText.setPosition((window.getSize().x - managerRect.width) / 2, (window.getSize().y - managerRect.height) / 2 - 190);

	scoreBoxContent.setString("0");
	// Back button
	backButton.setString("BACK");
	backButton.setFont(m_font);
	backButton.setCharacterSize(30);
	backButton.setFillColor(sf::Color::White);
	sf::FloatRect loginButtonRect = backButton.getLocalBounds();        // left                                                  // up
	backButton.setPosition((window.getSize().x - loginButtonRect.width) - 100, (window.getSize().y - loginButtonRect.height) / 2 - 270);
	borderRect.setSize(sf::Vector2f(loginButtonRect.width + 10, loginButtonRect.height + 10));
	borderRect.setPosition((window.getSize().x - loginButtonRect.width) - 103, (window.getSize().y - loginButtonRect.height) / 2 - 270);
	borderRect.setFillColor(sf::Color::Transparent);
	borderRect.setOutlineThickness(4);
	borderRect.setOutlineColor(sf::Color::White);
}

void GameMode::createBox() {
	if (!font.loadFromFile("font/RobotoSlab-Bold.ttf")) {
		std::cerr << "Font not found!" << std::endl;
	}
	GameDisplay gameDisplay;
	scoreBox.setSize(sf::Vector2f(50, 45));
	scoreBox.setFillColor(sf::Color::Transparent);
	scoreBox.setPosition(170, (window.getSize().y - scoreBox.getSize().y) / 2 - 110);
	scoreText.setString("SCORE \nTIME");
	scoreText.setFont(m_font);
	scoreText.setCharacterSize(27);
	scoreText.setFillColor(sf::Color::Cyan);
	scoreText.setPosition(70, (window.getSize().y - scoreBox.getSize().y) / 2 - 110);
	scoreBoxContent.setFont(m_font);
	scoreBoxContent.setCharacterSize(27);
	scoreBoxContent.setFillColor(sf::Color::Cyan);
	scoreBoxContent.setPosition(175, (window.getSize().y - scoreBox.getSize().y) / 2 - 110);
	timeBoxContent.setFont(m_font);
	timeBoxContent.setCharacterSize(27);
	timeBoxContent.setFillColor(sf::Color::Cyan);
	timeBoxContent.setPosition(175, (window.getSize().y - scoreBox.getSize().y) / 2 - 83);

	germanBox.setSize(sf::Vector2f(300, 45));
	germanBox.setFillColor(sf::Color(225, 225, 225, 160));                   // - left + down
	germanBox.setPosition((window.getSize().x - germanBox.getSize().x) / 2, (window.getSize().y - germanBox.getSize().y) / 2 + 310);
	germanBoxContent.setFont(font);
	germanBoxContent.setCharacterSize(25);
	germanBoxContent.setFillColor(sf::Color::Black);
	germanBoxContent.setPosition((window.getSize().x - germanBox.getSize().x) / 2, (window.getSize().y - germanBox.getSize().y) / 2 + 315);
}

void GameMode::updateFallingWords(float deltaTime) { // wordClock.restart().asSeconds() - restart(); initializing the time
	//auto startTime = std::chrono::high_resolution_clock::now();
	if (gameClock.getElapsedTime().asSeconds() < gameTimeLimit) {
		for (auto& word : fallingWords) {
			// Because sf::Text object cannot be mutable -> const_cast
			sf::Text& mutableWord = const_cast<sf::Text&>(word);
			mutableWord.move(0, wordFallSpeed * deltaTime); // Update the location
			// sf::Transformable class -> (inherit) -> move function
			// Vertical (Y-axis) falling speed (wordFallSpeed) x the elapsed time (deltaTime): how much the word descends per frame!

			class TextEqual {
			public: const sf::Text& text;

				  TextEqual(const sf::Text& t) : text(t) {}

				  bool operator()(const sf::Text& other) const {
					  return text.getString() == other.getString();
				  }
			};

			// Wrong
			if (mutableWord.getPosition().y >= (window.getSize().y - germanBox.getSize().y) / 2 + 330) {
				bombSound.setBuffer(bombBuffer);
				bombSound.setVolume(15);
				bombSound.play();
				mutableWord.setFillColor(sf::Color::Transparent);
				TextEqual textEqual(mutableWord); // functor
				auto fallingWordIt = std::find_if(fallingWords.begin(), fallingWords.end(), textEqual);
				if (fallingWordIt != fallingWords.end()) {
					fallingWords.erase(fallingWordIt);
				}
				int currentScore = std::stoi(scoreBoxContent.getString().toAnsiString());
				currentScore -= 10;
				scoreBoxContent.setString(std::to_string(currentScore));
				std::cout << "Lose! Current Score: " << scoreBoxContent.getString().toAnsiString() << std::endl;
				continue;
			}

			// Correct
			std::string enteredWord = germanBoxContent.getString().toAnsiString();
			auto it = dictionary.find(enteredWord);
			if (it != dictionary.end()) {
				std::string enteredEnglish = it->second;
				if (enteredEnglish == mutableWord.getString().toAnsiString()) {
					correctSound.setBuffer(correctBuffer);
					correctSound.play();
					mutableWord.setFillColor(sf::Color::Transparent);
					int currentScore = std::stoi(scoreBoxContent.getString().toAnsiString());
					currentScore += 20;
					scoreBoxContent.setString(std::to_string(currentScore));
					std::cout << "Get! Current Score: " << scoreBoxContent.getString().toAnsiString() << std::endl;

					dictionary.erase(it);
					TextEqual textEqual(mutableWord);
					auto fallingWordIt = std::find_if(fallingWords.begin(), fallingWords.end(), textEqual);
					if (fallingWordIt != fallingWords.end()) {
						fallingWordIt->setFillColor(sf::Color::Transparent);
						fallingWords.erase(fallingWordIt);
					}
					germanInput.clear();
					germanBoxContent.setString("");

					continue;
				}
			}
		}
		// New word created with calculating the time
		createTimer += deltaTime; // Save how much time passed so far
		if (createTimer > createInterval) {
			createWord();
			createTimer = 0;
		}		
		int remainedTime = static_cast<int>(gameTimeLimit - gameClock.getElapsedTime().asSeconds());
		timeBoxContent.setString(std::to_string(remainedTime));
	}
	else {
		musicSound.stop();
		sf::RenderWindow newWindow(sf::VideoMode(650, 200), "GAME OVER");
		sf::Text newMessage("		           TIME OUT !\n\n           Press ENTER to go back.", m_font, 25);
		newMessage.setFillColor(sf::Color::Red);
		newMessage.setPosition(-15, 60);

		sf::Clock clock;

		while (newWindow.isOpen()) {
			sf::Event newEvent;
			while (newWindow.pollEvent(newEvent)) {
				if (newEvent.type == sf::Event::Closed) {
					newWindow.close();
					window.close();
					GameDisplay gameDisplay;
					gameDisplay.run();
				}
				else if (newEvent.type == sf::Event::KeyPressed && newEvent.key.code == sf::Keyboard::Enter) {
					newWindow.close();
					window.close();
					GameDisplay gameDisplay;
					gameDisplay.run();
				}
			}
			if (clock.getElapsedTime().asSeconds() > 0.8) {
				newMessage.setFillColor(sf::Color(255 - newMessage.getFillColor().r, 255 - newMessage.getFillColor().g, 255 - newMessage.getFillColor().b));
				clock.restart();
			}
			newWindow.clear();
			newWindow.draw(newMessage);
			newWindow.display();
		}
	}
}

void GameMode::createWord() {
	if (gameClock.getElapsedTime().asSeconds() < gameTimeLimit) {
		if (!dictionary.empty()) {
			//std::cerr << "Number of elements in dictionary: " << dictionary.size() << std::endl;
			auto it = dictionary.begin();
			std::advance(it, rand() % dictionary.size()); // Shuffle within the range of dictionary
			sf::Text wordText(it->second, font, 25); // Only-eng
			wordText.setFillColor(sf::Color::White);
			sf::FloatRect boxRect = gameBox.getGlobalBounds();
			wordText.setPosition(rand() % 1000 + 100, (window.getSize().y - boxRect.height) / 2 + 100);

			fallingWords.push_back(wordText);
		}
	}
}

void GameMode::initializeRandomSeed() {
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Based on the current time(each time the program runs)
}

void GameMode::handleTextEntered(sf::Event event) {
	const int maxInputLength = 19;

	if (event.text.unicode == 8 && !germanInput.empty()) { // Back space
		germanInput.pop_back();
	}
	else if (event.text.unicode == 8 && germanInput.empty() || event.text.unicode == 13) {
		// nothing
	}
	else if (event.text.unicode < 128 && germanInput.size() < maxInputLength) {
		germanInput += static_cast<char>(event.text.unicode);
	}
	germanBoxContent.setString(germanInput);
}

void GameMode::playClick() {
	if (clickBuffer.loadFromFile("media/click_sound.wav")) {
		clickSound.setBuffer(clickBuffer);
		clickSound.play();
	}
	else {
		std::cerr << "Failed to load click sound file!" << std::endl;
	}
}

void GameMode::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

		if (event.type == sf::Event::Closed) {
			window.close();
			musicSound.stop();
		}
		/*if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
			enterText.setFillColor(sf::Color::Transparent);
		}*/
		else if (backButton.getGlobalBounds().contains(mousePos)) {
			playClick();
			std::cout << "BACK button clicked! Opening previous window..." << std::endl;
			window.close();
			musicSound.stop();
			GameDisplay gameDisplay;
			gameDisplay.run();
		}
		else if (event.type == sf::Event::MouseMoved) {
			if (backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
				backButton.setFillColor(sf::Color::Red);
				borderRect.setOutlineColor(sf::Color::Red);
			}
			else {
				backButton.setFillColor(sf::Color::White);
				borderRect.setOutlineColor(sf::Color::White);
			}
		}
		else if (event.type == sf::Event::TextEntered) {
			handleTextEntered(event);
		}
	}
}

void GameMode::render() {
	window.clear();
	window.draw(bombSprite);
	window.draw(gameBox);
	window.draw(mainText);
	window.draw(subText);
	window.draw(backButton);
	window.draw(borderRect);
	window.draw(germanBox);
	window.draw(germanBoxContent);
	window.draw(timeBoxContent);
	window.draw(scoreText);
	window.draw(scoreBox);
	window.draw(scoreBoxContent);
	for (const auto& word : fallingWords) {
		window.draw(word);
	}
	/*for (size_t i = 0; i < fallingWords.size(); ++i) {
		window.draw(fallingWords[i]);
	}
	std::for_each(fallingWords.begin(), fallingWords.end(), [&](const sf::Text& word) {
		window.draw(word);
		});*/
	window.display();
}
