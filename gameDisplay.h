#pragma once
#include "userMenu.h"
#include "gameMode.h"

#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

class GameDisplay {
public:
    GameDisplay();
    void run();
    void playClick();

private:
    void createDisplay();
    void createButton();
    void handleEvents();
    void handleButtonClick(sf::Text& button);
    void handleMouseOver(sf::Text& button);
    void handleMouseOut(sf::Text& button);
    void render();
   
    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;
    
    sf::RenderWindow window;
    sf::Font m_font;
    sf::Font font;
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