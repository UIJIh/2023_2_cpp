#include "menu.h"
#include "loginSystem.h"

Menu::Menu() : window(sf::VideoMode(1400, 700), "Menu Display") { }

void Menu::createDisplay() {
    if (!font.loadFromFile("font/hangthedj.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    mainText.setString("let's practice together");
    mainText.setFont(font);
    mainText.setCharacterSize(70);
    mainText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = mainText.getLocalBounds();
    mainText.setPosition((window.getSize().x - textRect.width) / 2, (window.getSize().y - textRect.height) / 2 - 240);

    // Back button
    backButton.setString("BACK");
    backButton.setFont(font);
    backButton.setCharacterSize(30);
    backButton.setFillColor(sf::Color::White);
    sf::FloatRect loginButtonRect = backButton.getLocalBounds();        // left                                                  // down
    backButton.setPosition((window.getSize().x - loginButtonRect.width) - 250, (window.getSize().y - loginButtonRect.height) / 2 + 180);
    borderRect.setSize(sf::Vector2f(loginButtonRect.width + 10, loginButtonRect.height + 10));
    borderRect.setPosition((window.getSize().x - loginButtonRect.width) - 253, (window.getSize().y - loginButtonRect.height) / 2 + 180);
    borderRect.setFillColor(sf::Color::Transparent);
    borderRect.setOutlineThickness(4);
    borderRect.setOutlineColor(sf::Color::White);
}

void Menu::createButton() {
    if (!m_font.loadFromFile("font/RobotoSlab-Bold.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    // 1
    buttonFirst.setString("1. VOCABULARY");
    buttonFirst.setFont(m_font);
    buttonFirst.setCharacterSize(50);
    buttonFirst.setFillColor(sf::Color::White);
    sf::FloatRect buttonFirstRect = buttonFirst.getLocalBounds();        // left                                                 
    buttonFirst.setPosition((window.getSize().x - buttonFirstRect.width) / 2, (window.getSize().y - buttonFirstRect.height) / 2 - 70);
}

void Menu::playClick() {
    if (clickBuffer.loadFromFile("media/click_sound.wav")) {
        clickSound.setBuffer(clickBuffer);
        clickSound.play();
    }
    else {
        std::cerr << "Failed to load click sound file!" << std::endl;
    }
}