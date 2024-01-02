#include "mainDisplay.h"

MainDisplay::MainDisplay() : window(sf::VideoMode(1400, 700), "Main Display") {
    if (!texture.loadFromFile("media/german.png")) {
        std::cerr << "Failed to load profile.png!" << std::endl;
    }
    if (!font.loadFromFile("font/hangthedj.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.8f, 0.8f);
    sprite.setPosition(700, 0); // right, down
}

void MainDisplay::run() {
    while (window.isOpen()) {
        createDisplay();
        handleEvents();
        render();
    }
}

void MainDisplay::createDisplay() {
    mainText.setString("Welcome! Learn German!");
    mainText.setFont(font);
    mainText.setCharacterSize(80);
    mainText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = mainText.getLocalBounds();
    mainText.setPosition((window.getSize().x - textRect.width) / 2, (window.getSize().y - textRect.height) / 2 - 100);

    startButton.setString("START");
    startButton.setFont(font);
    startButton.setCharacterSize(50);
    startButton.setFillColor(sf::Color::White);
    sf::FloatRect buttonRect = startButton.getLocalBounds();
    startButton.setPosition((window.getSize().x - buttonRect.width) / 2, (window.getSize().y - buttonRect.height) / 2 + 50);
}

void MainDisplay::playClick() {
    if (clickBuffer.loadFromFile("media/click_sound.wav")) {
        clickSound.setBuffer(clickBuffer);
        clickSound.play();
    }
    else {
        std::cerr << "Failed to load click sound file!" << std::endl;
    }
}

void MainDisplay::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (startButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                playClick();
                std::cout << "START button clicked! Opening login window..." << std::endl;
                window.close();
                LoginSystem loginSystem;
                loginSystem.run();
            }
        }
        else if (event.type == sf::Event::MouseMoved) {
            if (startButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                startButton.setFillColor(sf::Color::Red);
            }
            else {
                startButton.setFillColor(sf::Color::White);
            }
        }
    }
    if (clock.getElapsedTime().asSeconds() > 0.8) {
        startButton.setFillColor(sf::Color::Transparent);
    }
    if (clock.getElapsedTime().asSeconds() > 0.9) { clock.restart(); }
}

void MainDisplay::render() {
    window.clear();
    window.draw(mainText);
    window.draw(sprite);
    window.draw(startButton);
    window.display();
}
