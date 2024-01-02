#pragma once
#ifndef MANAGERMENU_H
#define MANAGERMENU_H
#include "menu.h"

class Menu;

class ManagerMenu : public Menu {
public:
    ManagerMenu();
    void run() override;
    void render() override;
    void handleEvents() override;

protected:
    sf::Text subText;
    sf::Text buttonSecond;
    sf::RectangleShape borderSecond;
};
#endif 