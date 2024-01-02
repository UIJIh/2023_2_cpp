#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
//#include <chrono>
#include "gameDisplay.h"

class GameMode {
public:
    GameMode(const std::string& level);
    void playClick();

private:
    const std::string& userLevel;

    std::unordered_map<std::string, std::string> dictionary;
    sf::RenderWindow window;
    std::ifstream inputFile;
    sf::RectangleShape gameBox;
    sf::Texture bombTexture;
    sf::Sprite bombSprite;
    sf::Font m_font;
    sf::Font font;
    sf::Text mainText;
    sf::Text subText;
    sf::Text enterText;
    sf::Text backButton;
    sf::Text scoreText;
    sf::Text scoreBoxContent;
    sf::Text timeBoxContent;
    sf::Text germanBoxContent;
    sf::RectangleShape borderRect;
    sf::RectangleShape germanBox;
    sf::RectangleShape scoreBox;
    std::string germanInput;

    sf::SoundBuffer clickBuffer;
    sf::SoundBuffer musicBuffer;
    sf::SoundBuffer correctBuffer;
    sf::SoundBuffer bombBuffer;
    sf::Sound clickSound;
    sf::Sound musicSound;
    sf::Sound correctSound;
    sf::Sound bombSound;

    void run();
    void sound();
    void createDictionary();
    void createDisplay();
    void createBox();
    void handleTextEntered(sf::Event event);
    void handleEvents();
    void render();

    // For the game-process
    std::vector<sf::Text> fallingWords;
    float wordFallSpeed;
    float createTimer;
    float createInterval;
    float gameTimeLimit;
    sf::Clock wordClock;
    sf::Clock gameClock;
    void updateFallingWords(float deltaTime);
    void createWord();
    void initializeRandomSeed();
};

#endif
