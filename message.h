#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include <SFML/Graphics.hpp>
#include "loginSystem.h"
#include "showProfiles.h"

class Message {
public:
    Message(const std::string& currentId, const std::string& othersId);

    std::string currentID;
    //std::string othersID;

    void playClick();
    void run();

private:
    
    void createDisplay();
    void displayMessages();

    void handleTextEntered(sf::Event event);
    void handleEvents();
    void render();

    sf::Font mainfont;
    sf::Font searchfont;

    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    //std::string currentId;
    std::string othersID;
    std::string message;

    sf::Text messages;
    sf::Text ellipsis;


    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;

    sf::RectangleShape messageBox;
    sf::Text messageBoxContent;
    std::string messageInput;

    sf::Text mainText;
    sf::Text messageText;
    sf::Text saveButton;
    sf::Text backButton;
    sf::RectangleShape borderRect;

    bool messageBoxActive = false;
    bool saveButtonActive = false;


};

#endif // MESSAGE_H
