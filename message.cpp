#include "message.h"
#include <iostream>
#include <fstream>
#include <sstream>

Message::Message(const std::string& currentId, const std::string& othersId) : window(sf::VideoMode(1400, 700), "Message") {

    std::ifstream inFile("message.txt");

    if (!inFile.is_open()) {
        std::cout << "Make a new file" << std::endl;
        std::ofstream newFile("message.txt", std::ios::app);
        inFile.close();
        return;
    }
    othersID = othersId;
}

void Message::playClick() {
    if (clickBuffer.loadFromFile("media/click_sound.wav")) {
        clickSound.setBuffer(clickBuffer);
        clickSound.play();
    }
    else {
        std::cerr << "Failed to load click sound file!" << std::endl;
    }
}

void Message::createDisplay() {
    if (!mainfont.loadFromFile("font/hangthedj.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    else if (!searchfont.loadFromFile("font/RobotoSlab-Bold.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    mainText.setString("< Message > ");
    mainText.setFont(mainfont);
    mainText.setCharacterSize(50);
    mainText.setFillColor(sf::Color::White);
    sf::FloatRect maintextRect = mainText.getLocalBounds();
    mainText.setPosition((window.getSize().x - maintextRect.width) / 2, (window.getSize().y - maintextRect.height) / 2 - 230);

    messageText.setString("Write Message :");
    messageText.setFont(searchfont);
    messageText.setCharacterSize(30);
    messageText.setFillColor(sf::Color::White);
    sf::FloatRect messagetextRect = messageText.getLocalBounds();
    messageText.setPosition(200, (window.getSize().y - messagetextRect.height) / 2 - 85);

    messageBox.setSize(sf::Vector2f(500, 40));
    messageBox.setFillColor(sf::Color(225, 225, 225));
    messageBox.setPosition((window.getSize().x - messageBox.getSize().x) / 2, (window.getSize().y - messageBox.getSize().y) / 2 - 77);


    saveButton.setString("SEND");
    saveButton.setFont(mainfont);
    saveButton.setCharacterSize(40);
    saveButton.setFillColor(sf::Color::White);
    sf::FloatRect buttonRect = saveButton.getLocalBounds();
    saveButton.setPosition(1050, 250);

    // Input
    messageBoxContent.setFont(searchfont);
    messageBoxContent.setCharacterSize(25);
    messageBoxContent.setFillColor(sf::Color::Black);
    messageBoxContent.setPosition((window.getSize().x - messageBox.getSize().x) / 2 + 3, (window.getSize().y - messageBox.getSize().y) / 2 - 75);

    // Back button
    backButton.setString("BACK");
    backButton.setFont(mainfont);
    backButton.setCharacterSize(30);
    backButton.setFillColor(sf::Color::White);
    sf::FloatRect backButtonRect = backButton.getLocalBounds();        // left                                                  // down
    backButton.setPosition((window.getSize().x - backButtonRect.width) - 250, (window.getSize().y - backButtonRect.height) / 2 + 200);
    borderRect.setSize(sf::Vector2f(backButtonRect.width + 10, backButtonRect.height + 10));
    borderRect.setPosition((window.getSize().x - backButtonRect.width) - 253, (window.getSize().y - backButtonRect.height) / 2 + 200);
    borderRect.setFillColor(sf::Color::Transparent);
    borderRect.setOutlineThickness(4);
    borderRect.setOutlineColor(sf::Color::White);

}

void Message::displayMessages() {
    std::ifstream file("message.txt");
    std::string line;
    std::string setmessage = "";
    int lineCount = 0;

    messages.setString("");
    while (std::getline(file, line)) {
        size_t pos = line.find(" - ");
        if (pos != std::string::npos) {
            std::string token1 = line.substr(0, pos);               // a
            std::string token2 = line.substr(pos + 3);              // b - c
            size_t pos2 = token2.find(" - ");
            std::string token2_a = token2.substr(0, pos2);          // b
            std::string token2_c = token2.substr(pos2 + 3);         // c

            // Display the message in the window
            //sf::Text messages;
            if (token2_a == othersID) {
                messages.setFont(searchfont);
                messages.setCharacterSize(20);
                messages.setFillColor(sf::Color::White);
                setmessage += token1 + " :  " + token2_c + "\n";
                messages.setString(setmessage);

                lineCount++;

                if (lineCount > 12) {
                    break;
                }
            }
            
        }
    }
    if (lineCount < 12) {
        messages.setPosition(200, 350);
        window.draw(messages);
    }
    else {
        messages.setPosition(200, 350);
        window.draw(messages);

        ellipsis.setPosition(800, 350);
        ellipsis.setString("...more");
        ellipsis.setFont(searchfont);
        ellipsis.setCharacterSize(20);
        ellipsis.setFillColor(sf::Color::White);
        window.draw(ellipsis);

    }
}

void Message::handleTextEntered(sf::Event event) {
    const int maxInputLength = 30;

    if (messageBoxActive) {
        if (event.text.unicode == 8 && !messageInput.empty()) { // Back space
            messageInput.pop_back();
        }
        else if (event.text.unicode == 8 && messageInput.empty()) {
            // nothing
        }
        else if (event.text.unicode < 128 && messageInput.size() < maxInputLength) {
            messageInput += static_cast<char>(event.text.unicode);
        }
        messageBoxContent.setString(messageInput);
    }
}


void Message::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (messageBox.getGlobalBounds().contains(mousePos)) {
                playClick();
                messageBoxActive = true;
                saveButtonActive = false;
                std::cout << "message box clicked!" << std::endl;
            }

            else if (saveButton.getGlobalBounds().contains(mousePos)) {
                playClick();
                messageBoxActive = false;
                saveButtonActive = true;
                std::cout << "SAVE button clicked!" << std::endl;
                std::string messageInput = messageBoxContent.getString();
                //save
                std::ofstream outFile("message.txt", std::ios::app);
                if (outFile.is_open()) {
                    currentID = LoginSystem::currentID[0];
                    outFile << currentID << " - " << othersID << " - " << messageInput << "\n";
                    outFile.close();
                    message = "";
                    std::cout << "saved" << std::endl;
                    displayMessages();
                    messageInput.clear();
                    messageBoxContent.setString("");                    
                    /*window.draw(messages);
                    window.draw(ellipsis);*/
                }
                else {
                    std::cerr << "Error opening message.txt for writing\n";
                }

            }
            else if (backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                std::cout << "BACK button clicked!" << std::endl;
                playClick();
                window.close();
                ShowProfile showProfile("accounts.txt");
                showProfile.run();
            }
            else {
                messageBoxActive = false;
                saveButtonActive = false;

                std::cout << "somewhereelse is clicked!" << std::endl;

            }

        }
        else if (event.type == sf::Event::MouseMoved) {

            if (backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                backButton.setFillColor(sf::Color::Red);
                borderRect.setOutlineColor(sf::Color::Red);
            }
            else {
                backButton.setFillColor(sf::Color::White);
                borderRect.setOutlineColor(sf::Color::White);
            }
            if (saveButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                saveButton.setFillColor(sf::Color::Red);
            }
            else {
                saveButton.setFillColor(sf::Color::White);
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            if (messageBoxActive) {
                handleTextEntered(event);
            }
        }
    }
}

void Message::run() {
    while (window.isOpen()) {
        createDisplay();
        handleEvents();
        //displayMessages();
        render();
    }
}

void Message::render() {
    window.clear();
    window.draw(mainText);

    window.draw(messageText);
    window.draw(messageBox);
    window.draw(saveButton);
    window.draw(messageBoxContent);

    window.draw(backButton);
    window.draw(borderRect);
    
    displayMessages();

    window.draw(messages);
    window.draw(ellipsis);

    window.display();
}