#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "account.h"

class LoginSystem {
public:
    LoginSystem();
    void run();
    void playClick();
    const std::string& getPwInput() const {
        return pwInput;
    }
    static std::vector<std::string> currentID;

private:
    sf::RenderWindow window;
    sf::Font mainFont;
    sf::Text mainText;
    sf::Text loginButton;
    sf::Font loginFont;
    sf::RectangleShape borderRect;
    sf::Text idText;
    sf::Text pwText;
    sf::String pwHidden;
    sf::RectangleShape idBox;
    sf::RectangleShape pwBox;

    std::string idInput;
    std::string pwInput;

    sf::Text idBoxContent;
    sf::Text pwBoxContent;
    sf::Clock clock;

    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;

    bool idBoxActive;
    bool pwBoxActive;

    void createDisplay();
    void createLogin();
    void handleTextEntered(sf::Event event);
    void handleEvents();
    void render();

    AccountManager accountManager;
};
