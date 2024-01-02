#pragma once
#include "userMenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>


#ifndef GAMEDISPLAY_HH
#define GAMEDISPLAY_HH

class DictDisplay {
public:
    DictDisplay();
    void run();
    void playClick();
    std::string currentID;
private:
    void createDisplay();
    void createButton();
    void handleEvents();
    void handleButtonClick(sf::Text& button);
    void handleMouseOver(sf::Text& button);
    void handleMouseOut(sf::Text& button);
    void render();

    /* sf::SoundBuffer clickBuffer;
     sf::Sound clickSound;*/

protected:

    sf::RenderWindow window;
    sf::Font m_font;
    sf::Font font;


    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;

    sf::Text mainText;
    sf::Text subText;
    sf::Text backButton;
    sf::RectangleShape borderRect;
    sf::Text buttonA1;
    sf::Text buttonA2;
    sf::Text buttonB1;
    sf::Text buttonB2;
    sf::Text buttonC1;
    sf::Text buttonAll;
    sf::Clock clock;
};

#endif 