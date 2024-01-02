#include "editProfile.h"

EditProfile::EditProfile() : window(sf::VideoMode(1400, 700), "Edit Profile") {
	if (!profileTexture.loadFromFile("media/profile.png")) {
		std::cerr << "Failed to load profile.png!" << std::endl;
	}
	if (!font.loadFromFile("font/hangthedj.ttf")) {
		std::cerr << "Font not found!" << std::endl;
	}
	profileSprite.setTexture(profileTexture);
	profileSprite.setScale(0.8f, 0.8f);
	profileSprite.setPosition(170, 200); // right, down
	accountManager.loadAccounts();

	run();
}

void EditProfile::run() {
	createDisplay();
	while (window.isOpen()) {
		createCard();
		render();
		handleEvents();
	}
}

void EditProfile::createDisplay() {
	mainText.setString("[PROFILE CARD]");
	mainText.setFont(font);
	mainText.setCharacterSize(80);
	mainText.setFillColor(sf::Color::White);
	sf::FloatRect mainRect = mainText.getLocalBounds();
	mainText.setPosition((window.getSize().x - mainRect.width) / 2, (window.getSize().y - mainRect.height) / 2 - 240);

	// Back button
	backButton.setString("BACK");
	backButton.setFont(font);
	backButton.setCharacterSize(30);
	backButton.setFillColor(sf::Color::White);
	sf::FloatRect backRect = backButton.getLocalBounds();        // left                                                  // down
	backButton.setPosition((window.getSize().x - backRect.width) - 100, (window.getSize().y - backRect.height) / 2 + 220);
	borderRect1.setSize(sf::Vector2f(backRect.width + 10, backRect.height + 10));
	borderRect1.setPosition((window.getSize().x - backRect.width) - 103, (window.getSize().y - backRect.height) / 2 + 220);
	borderRect1.setFillColor(sf::Color::Transparent);
	borderRect1.setOutlineThickness(4);
	borderRect1.setOutlineColor(sf::Color::White);

	// Save button
	saveButton.setString("SAVE");
	saveButton.setFont(font);
	saveButton.setCharacterSize(30);
	saveButton.setFillColor(sf::Color::White);
	sf::FloatRect saveRect = saveButton.getLocalBounds();
	saveButton.setPosition((window.getSize().x - saveRect.width) - 100, (window.getSize().y - saveRect.height) / 2 + 160);
	borderRect2.setSize(sf::Vector2f(saveRect.width + 10, saveRect.height + 10));
	borderRect2.setPosition((window.getSize().x - saveRect.width) - 103, (window.getSize().y - saveRect.height) / 2 + 160);
	borderRect2.setFillColor(sf::Color::Transparent);
	borderRect2.setOutlineThickness(4);
	borderRect2.setOutlineColor(sf::Color::White);
}

void EditProfile::createCard() {
	if (!c_font.loadFromFile("font/RobotoSlab-Bold.ttf")) {
		std::cerr << "Font not found!" << std::endl;
	}
	idText.setString("Name");
	idText.setFont(c_font);
	idText.setCharacterSize(27);
	idText.setFillColor(sf::Color::White);
	idText.setPosition(600, 250);

	currentID = LoginSystem::currentID[0];
	idText2.setString(currentID);
	idText2.setFont(c_font);
	idText2.setCharacterSize(27);
	idText2.setFillColor(sf::Color::Cyan);
	idText2.setPosition(970, 250);

	levelText.setString("Currently Learning");
	levelText.setFont(c_font);
	levelText.setCharacterSize(27);
	levelText.setFillColor(sf::Color::White);
	levelText.setPosition(600, 310);

	followingText.setString("Following");
	followingText.setFont(c_font);
	followingText.setCharacterSize(27);
	followingText.setFillColor(sf::Color::White);
	followingText.setPosition(600, 370);

	followerText.setString("Followers");
	followerText.setFont(c_font);
	followerText.setCharacterSize(27);
	followerText.setFillColor(sf::Color::White);
	followerText.setPosition(600, 430);

	auto ID = currentID;
	auto it = std::find_if(accountManager.accounts.begin(), accountManager.accounts.end(),
		[ID](const Account& acc) { return acc.id == ID; });
	if (it != accountManager.accounts.end()) {
		followingText2.setString(std::to_string(it->following));
		followingText2.setFont(c_font);
		followingText2.setCharacterSize(27);
		followingText2.setFillColor(sf::Color::Cyan);
		followingText2.setPosition(970, 370);

		followerText2.setString(std::to_string(it->following));
		followerText2.setFont(c_font);
		followerText2.setCharacterSize(27);
		followerText2.setFillColor(sf::Color::Cyan);
		followerText2.setPosition(970, 430);
	}

	genderText.setString("Gender");
	genderText.setFont(c_font);
	genderText.setCharacterSize(27);
	genderText.setFillColor(sf::Color::White);
	genderText.setPosition(600, 490);

	residenceText.setString("Based On");
	residenceText.setFont(c_font);
	residenceText.setCharacterSize(27);
	residenceText.setFillColor(sf::Color::White);
	residenceText.setPosition(600, 550);

	levelBox.setSize(sf::Vector2f(200, 38));
	levelBox.setPosition(950, 310);
	levelBox.setOutlineThickness(3);
	levelBox.setFillColor(sf::Color::Transparent);
	levelBox.setOutlineColor(sf::Color::White);

	genderBox.setSize(sf::Vector2f(200, 38));
	genderBox.setPosition(950, 490);
	genderBox.setOutlineThickness(3);
	genderBox.setFillColor(sf::Color::Transparent);
	genderBox.setOutlineColor(sf::Color::White);

	residenceBox.setSize(sf::Vector2f(200, 37));
	residenceBox.setPosition(950, 550);
	residenceBox.setOutlineThickness(3);
	residenceBox.setFillColor(sf::Color::Transparent);
	residenceBox.setOutlineColor(sf::Color::White);

	levelBoxContent.setFont(c_font);
	levelBoxContent.setCharacterSize(27);
	levelBoxContent.setFillColor(sf::Color::Cyan);
	levelBoxContent.setPosition(970, 310);

	genderBoxContent.setFont(c_font);
	genderBoxContent.setCharacterSize(27);
	genderBoxContent.setFillColor(sf::Color::Cyan);
	genderBoxContent.setPosition(970, 490);

	residenceBoxContent.setFont(c_font);
	residenceBoxContent.setCharacterSize(27);
	residenceBoxContent.setFillColor(sf::Color::Cyan);
	residenceBoxContent.setPosition(970, 550);
}

void EditProfile::handleTextEntered(sf::Event event) {
	const int maxInputLength = 10;

	if (levelBoxActive) {
		if (event.text.unicode == 8 && !levelInput.empty()) { // Back space
			levelInput.pop_back();
		}
		else if (event.text.unicode == 8 && levelInput.empty() || event.text.unicode == 13 || event.text.unicode == 32) {
			// nothing
		}
		else if (event.text.unicode < 128 && levelInput.size() < maxInputLength) {
			levelInput += static_cast<char>(event.text.unicode);
		}
		levelBoxContent.setString(levelInput);
	}
	else if (genderBoxActive) {
		if (event.text.unicode == 8 && !genderInput.empty()) {
			genderInput.pop_back();
		}
		else if (event.text.unicode == 8 && genderInput.empty() || event.text.unicode == 13 || event.text.unicode == 32) {
			// nothing
		}
		else if (event.text.unicode < 128 && genderInput.size() < maxInputLength) {
			genderInput += static_cast<char>(event.text.unicode);
		}
		genderBoxContent.setString(genderInput);
	}
	else if (residenceBoxActive) {
		if (event.text.unicode == 8 && !residenceInput.empty()) {
			residenceInput.pop_back();
		}
		else if (event.text.unicode == 8 && residenceInput.empty() || event.text.unicode == 13 || event.text.unicode == 32) {
			// nothing
		}
		else if (event.text.unicode < 128 && residenceInput.size() < maxInputLength) {
			residenceInput += static_cast<char>(event.text.unicode);
		}
		residenceBoxContent.setString(residenceInput);
	}
}

void EditProfile::playClick() {
	if (clickBuffer.loadFromFile("media/click_sound.wav")) {
		clickSound.setBuffer(clickBuffer);
		clickSound.play();
	}
	else {
		std::cerr << "Failed to load click sound file!" << std::endl;
	}
}

void EditProfile::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (levelBox.getGlobalBounds().contains(mousePos)) {
				playClick();
				levelBoxActive = true;
				genderBoxActive = false;
				residenceBoxActive = false;
				std::cout << "Level box clicked!" << std::endl;
			}
			else if (genderBox.getGlobalBounds().contains(mousePos)) {
				playClick();
				levelBoxActive = false;
				genderBoxActive = true;
				residenceBoxActive = false;
				std::cout << "Gender box clicked!" << std::endl;
			}
			else if (residenceBox.getGlobalBounds().contains(mousePos)) {
				playClick();
				levelBoxActive = false;
				genderBoxActive = false;
				residenceBoxActive = true;
				std::cout << "Residence box clicked" << std::endl;
			}
			if (saveButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
				playClick();
				std::cout << "Save button clicked!" << std::endl;
				// Check if nothing
				if (levelInput.find_first_not_of(' ') == std::string::npos || genderInput.find_first_not_of(' ') == std::string::npos || residenceInput.find_first_not_of(' ') == std::string::npos) {
					// Case: Spaces-only
					std::cout << "Invalid input!" << std::endl;
					sf::RenderWindow newWindow(sf::VideoMode(600, 200), "ERROR");
					sf::Font font;
					if (font.loadFromFile("font/hangthedj.ttf")) {
						sf::Text errorMessage("    Invalid input! Fill in all the info.\n\n          Press ENTER to go back.", font, 20);
						errorMessage.setFillColor(sf::Color::Red);
						errorMessage.setPosition(36, 60);
						while (newWindow.isOpen()) {
							sf::Event newEvent;
							while (newWindow.pollEvent(newEvent)) {
								if (newEvent.type == sf::Event::Closed) {
									newWindow.close();
								}
								else if (newEvent.type == sf::Event::KeyPressed && newEvent.key.code == sf::Keyboard::Return) {
									newWindow.close();
								}
							}
							if (clock.getElapsedTime().asSeconds() > 0.8) {
								errorMessage.setFillColor(sf::Color(255 - errorMessage.getFillColor().r, 255 - errorMessage.getFillColor().g, 255 - errorMessage.getFillColor().b));
								clock.restart();
							}
							newWindow.clear();
							newWindow.draw(errorMessage);
							newWindow.display();
						}
					}return;
				}
				else {
					levelBoxActive = false;
					genderBoxActive = false;
					residenceBoxActive = false;
					Account currentAccount;
					currentAccount.interestLevel = levelBoxContent.getString();
					currentAccount.gender = genderBoxContent.getString();
					currentAccount.residence = residenceBoxContent.getString();
					auto idMatchIt = std::find_if(accountManager.accounts.begin(), accountManager.accounts.end(),
						[this](const Account& acc) { return acc.id == currentID; });
					if (idMatchIt != accountManager.accounts.end()) {
						std::cout << "ID found! Update the info." << std::endl;
						idMatchIt->interestLevel = currentAccount.interestLevel;
						idMatchIt->gender = currentAccount.gender;
						idMatchIt->residence = currentAccount.residence;
						accountManager.saveAccounts();
					}
				}
			}
			else if (backButton.getGlobalBounds().contains(mousePos)) {
				playClick();
				std::cout << "BACK button clicked! Opening previous window..." << std::endl;
				window.close();
				CurrentProfile currentProfile;
				currentProfile.run();
			}
		}
		else if (event.type == sf::Event::MouseMoved) {
			if (saveButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
				saveButton.setFillColor(sf::Color::Red);
				borderRect2.setOutlineColor(sf::Color::Red);
			}
			else {
				saveButton.setFillColor(sf::Color::White);
				borderRect2.setOutlineColor(sf::Color::White);
			}

			if (backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
				backButton.setFillColor(sf::Color::Red);
				borderRect1.setOutlineColor(sf::Color::Red);
			}
			else {
				backButton.setFillColor(sf::Color::White);
				borderRect1.setOutlineColor(sf::Color::White);
			}
		}
		else if (event.type == sf::Event::TextEntered) {
			handleTextEntered(event);
		}
	}
}

void EditProfile::render() {
	window.clear();
	window.draw(mainText);
	window.draw(profileSprite);
	window.draw(saveButton);
	window.draw(backButton);
	window.draw(borderRect1);
	window.draw(borderRect2);

	window.draw(idText);
	window.draw(idText2);
	window.draw(idBox);

	window.draw(residenceText);
	window.draw(residenceBox);
	window.draw(residenceBoxContent);
	residenceBoxContent.setPosition(residenceBox.getPosition().x + 10, residenceBox.getPosition().y);

	window.draw(genderText);
	window.draw(genderBox);
	window.draw(genderBoxContent);
	genderBoxContent.setPosition(genderBox.getPosition().x + 10, genderBox.getPosition().y + 30);

	window.draw(followerText);
	window.draw(followerText2);
	window.draw(followerBox);

	window.draw(followingText);
	window.draw(followingText2);
	window.draw(followingBox);

	window.draw(levelText);
	window.draw(levelBox);
	window.draw(levelBoxContent);
	levelBoxContent.setPosition(levelBox.getPosition().x + 10, levelBox.getPosition().y + 30);

	window.display();
}
