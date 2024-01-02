#include "currentProfile.h"
#include "showFollwing.h"
#include "showProfiles.h"

CurrentProfile::CurrentProfile() : window(sf::VideoMode(1400, 700), "Edit Profile") {
	if (!profileTexture.loadFromFile("media/profile.png")) {
		std::cerr << "Failed to load profile.png!" << std::endl;
	}
	if (!font.loadFromFile("font/hangthedj.ttf")) {
		std::cerr << "Font not found!" << std::endl;
	}
	if (!c_font.loadFromFile("font/RobotoSlab-Bold.ttf")) {
		std::cerr << "Font not found!" << std::endl;
	}
	profileSprite.setTexture(profileTexture);
	profileSprite.setScale(0.8f, 0.8f);
	profileSprite.setPosition(170, 200); // right, down
	accountManager.loadAccounts();
}

void CurrentProfile::run() {
	createDisplay();
	while (window.isOpen()) {
		createCard();
		handleEvents();
		render();
	}
}

void CurrentProfile::createDisplay() {
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
	editButton.setString("EDIT");
	editButton.setFont(font);
	editButton.setCharacterSize(30);
	editButton.setFillColor(sf::Color::White);
	sf::FloatRect saveRect = editButton.getLocalBounds();
	editButton.setPosition((window.getSize().x - saveRect.width) - 100, (window.getSize().y - saveRect.height) / 2 + 160);
	borderRect2.setSize(sf::Vector2f(saveRect.width + 10, saveRect.height + 10));
	borderRect2.setPosition((window.getSize().x - saveRect.width) - 103, (window.getSize().y - saveRect.height) / 2 + 160);
	borderRect2.setFillColor(sf::Color::Transparent);
	borderRect2.setOutlineThickness(4);
	borderRect2.setOutlineColor(sf::Color::White);
}

void CurrentProfile::createCard() {
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

	auto ID = currentID;
	auto it = std::find_if(accountManager.accounts.begin(), accountManager.accounts.end(),
		[ID](const Account& acc) { return acc.id == ID; });
	if (it != accountManager.accounts.end()) {
		levelBoxContent.setString(it->interestLevel);
		levelBoxContent.setFont(c_font);
		levelBoxContent.setCharacterSize(27);
		levelBoxContent.setFillColor(sf::Color::Cyan);
		levelBoxContent.setPosition(970, 310);

		genderBoxContent.setString(it->gender);
		genderBoxContent.setFont(c_font);
		genderBoxContent.setCharacterSize(27);
		genderBoxContent.setFillColor(sf::Color::Cyan);
		genderBoxContent.setPosition(970, 490);

		residenceBoxContent.setString(it->residence);
		residenceBoxContent.setFont(c_font);
		residenceBoxContent.setCharacterSize(27);
		residenceBoxContent.setFillColor(sf::Color::Cyan);
		residenceBoxContent.setPosition(970, 550);

		followingText2.setString(std::to_string(it->following));
		followingText2.setFont(c_font);
		followingText2.setCharacterSize(27);
		followingText2.setFillColor(sf::Color::Cyan);
		followingText2.setPosition(970, 370);

		followerText2.setString(std::to_string(it->followers));
		followerText2.setFont(c_font);
		followerText2.setCharacterSize(27);
		followerText2.setFillColor(sf::Color::Cyan);
		followerText2.setPosition(970, 430);
	}
}

void CurrentProfile::playClick() {
	if (clickBuffer.loadFromFile("media/click_sound.wav")) {
		clickSound.setBuffer(clickBuffer);
		clickSound.play();
	}
	else {
		std::cerr << "Failed to load click sound file!" << std::endl;
	}
}

void CurrentProfile::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			if (editButton.getGlobalBounds().contains(mousePos)) {
				playClick();
				playClick();
				std::cout << "Edit button clicked!" << std::endl;
				window.close();
				EditProfile editProfile;
				editProfile;
			}
			else if (backButton.getGlobalBounds().contains(mousePos)) {
				playClick();
				std::cout << "BACK button clicked! Opening previous window..." << std::endl;
				window.close();
				ShowProfile showProfile("accounts.txt");
				showProfile.run();
			}
			else if (followingText2.getGlobalBounds().contains(mousePos)) {
				playClick();
				std::cout << "Following Text clicked! Opening following window..." << std::endl;
				ShowFollowing showFollowing(currentID, "following.txt");
				showFollowing.run();
				std::cout << "Show following" << std::endl;
			}
			else if (followerText2.getGlobalBounds().contains(mousePos)) {
				playClick();
				std::cout << "Follower Text clicked! Opening follower window..." << std::endl;
				ShowFollowing showFollowing(currentID, "follower.txt");
				showFollowing.run();
				std::cout << "Show followers" << std::endl;
			}
		}
		else if (event.type == sf::Event::MouseMoved) {
			if (editButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
				editButton.setFillColor(sf::Color::Red);
				borderRect2.setOutlineColor(sf::Color::Red);
			}
			else {
				editButton.setFillColor(sf::Color::White);
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
			if (followingText2.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
				followingText2.setFillColor(sf::Color::Red);
			}
			else {
				followingText2.setFillColor(sf::Color::White);
			}
			if (followerText2.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
				followerText2.setFillColor(sf::Color::Red);
			}
			else {
				followerText2.setFillColor(sf::Color::White);
			}
		}
	}
}

void CurrentProfile::render() {
	window.clear();
	window.draw(mainText);
	window.draw(profileSprite);
	window.draw(editButton);
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