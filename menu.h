#ifndef MENU_H
#define MENU_H

#include "currentProfile.h"

class Menu {
public:
    Menu();
    void playClick();

    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;

    void createDisplay();
    void createButton();

    virtual void run() = 0;
    virtual void handleEvents() = 0;
    virtual void render() = 0;

    sf::RenderWindow window;
    sf::Font font;
    sf::Text mainText;
    sf::Text backButton;
    sf::RectangleShape borderRect;
    bool isManager;
    sf::Font m_font;
    sf::Text buttonFirst;
    sf::RectangleShape borderFirst;
};

#endif 