#include "managerMenu.h"
#include "dictDisplay.h"

ManagerMenu::ManagerMenu() : Menu() {
}

void ManagerMenu::run() {
    createDisplay();
    createButton();
    subText.setString(" - manager mode - ");
    subText.setFont(font);
    subText.setCharacterSize(30);
    subText.setFillColor(sf::Color::White);
    sf::FloatRect managerRect = subText.getLocalBounds();
    subText.setPosition((window.getSize().x - managerRect.width) / 2, (window.getSize().y - managerRect.height) / 2 - 170);
    // 2
    buttonSecond.setString("2. MANAGEMENT");
    buttonSecond.setFont(m_font);
    buttonSecond.setCharacterSize(50);
    buttonSecond.setFillColor(sf::Color::White);
    sf::FloatRect buttonSecondRect = buttonSecond.getLocalBounds();        // left                                                  // down
    buttonSecond.setPosition((window.getSize().x - buttonSecondRect.width) / 2, (window.getSize().y - buttonSecondRect.height) / 2 + 20);
	while (window.isOpen()) {
		handleEvents();
		render();
	}
}

void ManagerMenu::handleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			if (buttonFirst.getGlobalBounds().contains(mousePos)) {
				playClick();
				std::cout << "First button clicked! Opening new window..." << std::endl;
				window.close();
				DictDisplay dictDisplay;
				dictDisplay.run();
			}
			else if (backButton.getGlobalBounds().contains(mousePos)) {
				playClick();
				std::cout << "BACK button clicked! Opening previous window..." << std::endl;
				window.close();
				LoginSystem loginSystem;
				loginSystem.run();
			}
			else if (buttonSecond.getGlobalBounds().contains(mousePos)) {
				playClick();
				std::cout << "Second button clicked! Opening new window..." << std::endl;
				window.close();
				ShowProfile showProfile("accounts.txt");
				showProfile.run();
			}
		}
		else if (event.type == sf::Event::MouseMoved) {
			if (buttonFirst.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
				buttonFirst.setFillColor(sf::Color::Red);
			}
			else {
				buttonFirst.setFillColor(sf::Color::White);
			}
			if (buttonSecond.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
				buttonSecond.setFillColor(sf::Color::Red);
			}
			else {
				buttonSecond.setFillColor(sf::Color::White);
			}			
			if (backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
				backButton.setFillColor(sf::Color::Red);
				borderRect.setOutlineColor(sf::Color::Red);
			}
			else {
				backButton.setFillColor(sf::Color::White);
				borderRect.setOutlineColor(sf::Color::White);
			}
		}
	}
}

void ManagerMenu::render() {
    window.clear();
    window.draw(mainText);
    window.draw(backButton);
    window.draw(borderRect);
    window.draw(buttonFirst);
    window.draw(borderFirst);
    window.draw(subText);
    window.draw(buttonSecond);
    window.display();
}