#pragma once

#ifndef SHOW_PROFILE_H
#define SHOW_PROFILE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <thread>
#include "currentProfile.h"
#include "message.h"
#include "managerMenu.h"

class ManagerProfile {
public:
    ManagerProfile(const std::string& filename);
    std::string currentID;
    std::string othersID;

    void run();
    void playClick();

    sf::RenderWindow window;

    std::vector<std::string> lines;
    std::size_t currentIndex;
    std::size_t i;
    std::string displayedText;
    int initialYPosition = 310;
    int lineHeight = 20;

    std::size_t spacePos1; //name
    std::size_t spacePos2;  // pw
    std::size_t spacePos3;  // gender
    std::size_t spacePos4;  // residence
    std::size_t spacePos5;  // level
    std::size_t spacePos6;  // follower and last:following

    std::string othersId;
    std::string othersLevel;
    std::string othersFollower;
    std::string othersFollowing;
    std::string othersGender;
    std::string othersResidence;

    AccountManager accountManager;
    std::vector<Account> accounts;

    sf::Font font;
    sf::Font buttonfont;

    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;

    sf::Texture profileTexture;
    sf::Sprite profileSprite;

    sf::Text text;
    sf::Text maintext;
    sf::Text nextButton;
    sf::Text beforeButton;
    sf::Text backButton;
    sf::RectangleShape borderRect1;

    // Profile-card
    sf::RectangleShape myprofileBox;
    sf::RectangleShape othersprofileBox;
    sf::Text myprofile;
    sf::Text detailClick;

    //sf::CircleShape followButton;
    sf::RectangleShape followButton;
    sf::Text followButtonText;
    sf::Text followClickText;

    sf::Text othersIdText1;
    sf::Text othersIdText2;
    sf::Text othersLevelText1;
    sf::Text othersLevelText2;
    sf::Text othersFollowingText1;
    sf::Text othersFollowingText2;
    sf::Text othersFollowerText1;
    sf::Text othersFollowerText2;
    sf::Text othersGenderText1;
    sf::Text othersGenderText2;
    sf::Text othersResidenceText1;
    sf::Text othersResidenceText2;
    //sf::Text residenceText2;
    sf::Text messageText1;
    sf::Text messageText2;
    sf::RectangleShape messageBox1;
    sf::RectangleShape messageBox2;

    bool nextButtonActive = false;
    bool beforeButtonActive = false;
    bool myprofileActive = false;
    bool othersIdTextActive = false;
    bool followButtonActive = false;
    bool messageBox1Active = false;
    bool isFollowing = true;

    void loadTextFromFile(const std::string& filename);
    void loadFontandPng();
    void updateDisplayedText();
    void drawMyProfile();


    void setDisplay(sf::Text& text, const std::string& content, const sf::Font& font, int characterSize, const sf::Color& fillColor, float x, float y);
    void following(const std::string& currentId, const std::string& othersId);
    void follower(const std::string& othersId, const std::string& currentId);

    void handleMouseOver(sf::Text& button);
    void handleMouseOut(sf::Text& button);

    void createDisplay();
    void handleEvents();
    void render();
    void clickDisplay();


};

#endif 