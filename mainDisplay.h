#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "loginSystem.h"

class MainDisplay {
public:
    MainDisplay();
    void run();
    void playClick();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text mainText;
    sf::Text startButton;
    sf::Clock clock;
    sf::Texture texture;
    sf::Sprite sprite;

    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;
    
    void createDisplay();
    void handleEvents();
    void render();
};