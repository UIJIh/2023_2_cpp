#pragma once

#ifndef CURRENTPROFILE_H
#define CURRENTPROFILE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "account.h"
#include "loginSystem.h"
#include "editProfile.h"

class CurrentProfile {
public:
    CurrentProfile();
    void run();
    void playClick();
    std::string currentID;

private:
    AccountManager accountManager;
    std::vector<Account> accounts;

    sf::RenderWindow window;
    sf::Font font;
    sf::Font c_font;
    sf::Texture profileTexture;
    sf::Sprite profileSprite;
    sf::Text mainText;
    sf::Text editButton;
    sf::Text backButton;
    sf::RectangleShape borderRect1;
    sf::RectangleShape borderRect2;
    sf::Clock clock;

    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;

    // Profile-card
    sf::Text idText;
    sf::Text idText2;
    sf::Text residenceText;
    sf::Text genderText;
    sf::Text followerText;
    sf::Text followerText2;
    sf::Text followingText;
    sf::Text followingText2;
    sf::Text levelText;
    sf::Text levelText2;

    sf::RectangleShape idBox;
    sf::RectangleShape residenceBox;
    sf::RectangleShape genderBox;
    sf::RectangleShape followerBox;
    sf::RectangleShape followingBox;
    sf::RectangleShape levelBox;

    sf::Text residenceBoxContent;
    sf::Text genderBoxContent;
    sf::Text followerBoxContent;
    sf::Text followingBoxContent;
    sf::Text levelBoxContent;

    std::string residenceInput;
    std::string genderInput;
    std::string followerInput;
    std::string followingInput;
    std::string levelInput;

    bool residenceBoxActive;
    bool genderBoxActive;
    bool levelBoxActive;

    void createDisplay();
    void createCard();
    void handleEvents();
    void render();

};
#endif
