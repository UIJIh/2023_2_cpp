#include "gameDisplay.h"

GameDisplay::GameDisplay() : window(sf::VideoMode(1400, 700), "Game Display") { }

void GameDisplay::run() {
    createDisplay();
    createButton();
    while (window.isOpen()) {
        handleEvents();
        render();
        subText.setString(" ! Choose your level ! ");
        subText.setFont(m_font);
        subText.setCharacterSize(30);
        subText.setFillColor(sf::Color::White);
        sf::FloatRect managerRect = subText.getLocalBounds();
        subText.setPosition((window.getSize().x - managerRect.width) / 2, (window.getSize().y - managerRect.height) / 2 - 170);
    }
}

void GameDisplay::createDisplay() {
    if (!m_font.loadFromFile("font/hangthedj.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    mainText.setString("Word Challenge");
    mainText.setFont(m_font);
    mainText.setCharacterSize(70);
    mainText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = mainText.getLocalBounds();
    mainText.setPosition((window.getSize().x - textRect.width) / 2, (window.getSize().y - textRect.height) / 2 - 240);
  
    // Back button
    backButton.setString("BACK");
    backButton.setFont(m_font);
    backButton.setCharacterSize(30);
    backButton.setFillColor(sf::Color::White);
    sf::FloatRect loginButtonRect = backButton.getLocalBounds();        // left                                                  // down
    backButton.setPosition((window.getSize().x - loginButtonRect.width) - 250, (window.getSize().y - loginButtonRect.height) / 2 + 200);
    borderRect.setSize(sf::Vector2f(loginButtonRect.width + 10, loginButtonRect.height + 10));
    borderRect.setPosition((window.getSize().x - loginButtonRect.width) - 253, (window.getSize().y - loginButtonRect.height) / 2 + 200);
    borderRect.setFillColor(sf::Color::Transparent);
    borderRect.setOutlineThickness(4);
    borderRect.setOutlineColor(sf::Color::White);
}

void GameDisplay::createButton() {
    if (!font.loadFromFile("font/RobotoSlab-Bold.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    // A1
    buttonA1.setString("A1");
    buttonA1.setFont(font);
    buttonA1.setCharacterSize(50);
    buttonA1.setFillColor(sf::Color::White);
    sf::FloatRect buttonA1Rect = buttonA1.getLocalBounds();
    buttonA1.setPosition((window.getSize().x - buttonA1Rect.width) / 2 - 100, (window.getSize().y - buttonA1Rect.height) / 2 - 90);
    // A2
    buttonA2.setString("A2");
    buttonA2.setFont(font);
    buttonA2.setCharacterSize(50);
    buttonA2.setFillColor(sf::Color::White);
    sf::FloatRect buttonA2Rect = buttonA2.getLocalBounds();
    buttonA2.setPosition((window.getSize().x - buttonA2Rect.width) / 2 + 100, (window.getSize().y - buttonA2Rect.height) / 2 - 90);

    // B1
    buttonB1.setString("B1");
    buttonB1.setFont(font);
    buttonB1.setCharacterSize(50);
    buttonB1.setFillColor(sf::Color::White);
    sf::FloatRect buttonB1Rect = buttonB1.getLocalBounds();
    buttonB1.setPosition((window.getSize().x - buttonB1Rect.width) / 2 - 100, (window.getSize().y - buttonB1Rect.height) / 2 + 50);

    // B2
    buttonB2.setString("B2");
    buttonB2.setFont(font);
    buttonB2.setCharacterSize(50);
    buttonB2.setFillColor(sf::Color::White);
    sf::FloatRect buttonB2Rect = buttonB2.getLocalBounds();
    buttonB2.setPosition((window.getSize().x - buttonB2Rect.width) / 2 + 100, (window.getSize().y - buttonB2Rect.height) / 2 + 50);

    // C1
    buttonC1.setString("C1");
    buttonC1.setFont(font);
    buttonC1.setCharacterSize(50);
    buttonC1.setFillColor(sf::Color::White);
    sf::FloatRect buttonC1Rect = buttonC1.getLocalBounds();
    buttonC1.setPosition((window.getSize().x - buttonC1Rect.width) / 2 - 100, (window.getSize().y - buttonC1Rect.height) / 2 + 190);

    // All
    buttonAll.setString("All");
    buttonAll.setFont(font);
    buttonAll.setCharacterSize(50);
    buttonAll.setFillColor(sf::Color::White);
    sf::FloatRect buttonAllRect = buttonAll.getLocalBounds();
    buttonAll.setPosition((window.getSize().x - buttonAllRect.width) / 2 + 100, (window.getSize().y - buttonAllRect.height) / 2 + 190);
}

void GameDisplay::playClick() {
    if (clickBuffer.loadFromFile("media/click_sound.wav")) {
        clickSound.setBuffer(clickBuffer);
        clickSound.play();
    }
    else {
        std::cerr << "Failed to load click sound file!" << std::endl;
    }
}

void GameDisplay::handleButtonClick(sf::Text& button) {
    playClick();
    std::cout << "Button clicked! Opening new window..." << std::endl;
    window.close();
}

void GameDisplay::handleMouseOver(sf::Text& button) {
    button.setFillColor(sf::Color::Red);
}

void GameDisplay::handleMouseOut(sf::Text& button) {
    button.setFillColor(sf::Color::White);
}

void GameDisplay::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (buttonA1.getGlobalBounds().contains(mousePos)) {
                handleButtonClick(buttonA1);
                GameMode gameMode("A1");
            }
            else if (buttonA2.getGlobalBounds().contains(mousePos)) {
                handleButtonClick(buttonA2);
                GameMode gameMode("A2");
            }
            else if (buttonB1.getGlobalBounds().contains(mousePos)) {
                handleButtonClick(buttonB1);
                GameMode gameMode("B1");
            }
            else if (buttonB2.getGlobalBounds().contains(mousePos)) {
                handleButtonClick(buttonB2);
                GameMode gameMode("B2");
            }
            else if (buttonC1.getGlobalBounds().contains(mousePos)) {
                handleButtonClick(buttonC1);
                GameMode gameMode("C1");
            }
            else if (buttonAll.getGlobalBounds().contains(mousePos)) {
                handleButtonClick(buttonAll);
                GameMode gameMode("All");
            }
            else if (backButton.getGlobalBounds().contains(mousePos)) {
                playClick();
                std::cout << "BACK button clicked! Opening previous window..." << std::endl;
                window.close();
                UserMenu userMenu;
                userMenu.run();
            }
        }
        else if (event.type == sf::Event::MouseMoved) {
            if (buttonA1.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                handleMouseOver(buttonA1);
            }
            else {
                handleMouseOut(buttonA1);
            }

            if (buttonA2.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                handleMouseOver(buttonA2);
            }
            else {
                handleMouseOut(buttonA2);
            }

            if (buttonB1.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                handleMouseOver(buttonB1);
            }
            else {
                handleMouseOut(buttonB1);
            }

            if (buttonB2.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                handleMouseOver(buttonB2);
            }          
            else {
                handleMouseOut(buttonB2);
            }

            if (buttonC1.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                handleMouseOver(buttonC1);
            }
            else {
                handleMouseOut(buttonC1);
            }

            if (buttonAll.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                handleMouseOver(buttonAll);
            }
            else {
                handleMouseOut(buttonAll);
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
    if (clock.getElapsedTime().asSeconds() > 0.8) {
        subText.setFillColor(sf::Color::Transparent);
    }
    if (clock.getElapsedTime().asSeconds() > 0.9) { clock.restart(); }
}

void GameDisplay::render() {
    window.clear();
    window.draw(mainText);
    window.draw(subText);
    window.draw(backButton);
    window.draw(borderRect);

    window.draw(buttonA1);
    window.draw(buttonA2);
    window.draw(buttonB1);
    window.draw(buttonB2);
    window.draw(buttonC1);
    window.draw(buttonAll);
    window.display();
}
