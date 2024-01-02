#include "loginSystem.h"
#include "userMenu.h"
#include "managerMenu.h"

std::vector<std::string> LoginSystem::currentID;

LoginSystem::LoginSystem() : window(sf::VideoMode(1400, 700), "Login & Register") {
    if (!loginFont.loadFromFile("font/RobotoSlab-Bold.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    accountManager.loadAccounts();
}

void LoginSystem::run() {
    // Click button
    loginButton.setString("CLICK");
    loginButton.setFont(mainFont);
    loginButton.setCharacterSize(27);
    loginButton.setFillColor(sf::Color::White);
    sf::FloatRect loginButtonRect = loginButton.getLocalBounds();        // left                                                  // down
    loginButton.setPosition((window.getSize().x - loginButtonRect.width) - 438, (window.getSize().y - loginButtonRect.height) / 2 + 40);
    borderRect.setSize(sf::Vector2f(98, 37));
    borderRect.setPosition((window.getSize().x - loginButtonRect.width) - 441, (window.getSize().y - loginButtonRect.height) / 2 + 40);
    borderRect.setFillColor(sf::Color::Transparent);
    borderRect.setOutlineThickness(4);
    borderRect.setOutlineColor(sf::Color::White);

    while (window.isOpen()) {
        createDisplay();
        handleEvents();
        render();
    }
}

void LoginSystem::createDisplay() {
    if (!mainFont.loadFromFile("font/hangthedj.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    mainText.setString("Login & Register");
    mainText.setFont(mainFont);
    mainText.setCharacterSize(80);
    mainText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = mainText.getLocalBounds();
    mainText.setPosition((window.getSize().x - textRect.width) / 2, (window.getSize().y - textRect.height) / 2 - 160);

    createLogin();
}

void LoginSystem::createLogin() {
    // ID/NAME text box
    idBox.setSize(sf::Vector2f(200, 40));
    idBox.setFillColor(sf::Color(225, 225, 225));
    idBox.setPosition((window.getSize().x - idBox.getSize().x) / 2 + 130, (window.getSize().y - idBox.getSize().y) / 2 - 27);

    // PASSWORD text box
    pwBox.setSize(sf::Vector2f(200, 40));
    pwBox.setFillColor(sf::Color(225, 225, 225));
    pwBox.setPosition((window.getSize().x - pwBox.getSize().x) / 2 + 130, (window.getSize().y - pwBox.getSize().y) / 2 + 53);

    // Text
    idText.setString("ID / NAME   (up to 10)");
    idText.setFont(loginFont);
    idText.setCharacterSize(27);
    idText.setFillColor(sf::Color::White);
    sf::FloatRect idTextRect = idText.getLocalBounds();                // left
    idText.setPosition((window.getSize().x - idBox.getSize().x) / 2 - 260, (window.getSize().y - idBox.getSize().y) / 2 - 27);

    pwText.setString("PASSWORD (up to 10)");
    pwText.setFont(loginFont);
    pwText.setCharacterSize(27);
    pwText.setFillColor(sf::Color::White);
    sf::FloatRect pwTextRect = pwText.getLocalBounds();
    pwText.setPosition((window.getSize().x - pwBox.getSize().x) / 2 - 260, (window.getSize().y - pwBox.getSize().y) / 2 + 53);

    // Input
    idBoxContent.setFont(loginFont); 
    idBoxContent.setCharacterSize(25); 
    idBoxContent.setFillColor(sf::Color::Black);
    idBoxContent.setPosition((window.getSize().x - idBox.getSize().x) / 2 + 130, (window.getSize().y - idBox.getSize().y) / 2 - 27);
    pwBoxContent.setFont(loginFont); 
    pwBoxContent.setCharacterSize(25); 
    pwBoxContent.setFillColor(sf::Color::Black);
    pwBoxContent.setPosition((window.getSize().x - pwBox.getSize().x) / 2 + 130, (window.getSize().y - pwBox.getSize().y) / 2 + 53);
}

void LoginSystem::playClick() {
    if (clickBuffer.loadFromFile("media/click_sound.wav")) {
        clickSound.setBuffer(clickBuffer);
        clickSound.play();
    }
    else {
        std::cerr << "Failed to load click sound file!" << std::endl;
    }
}

void LoginSystem::handleTextEntered(sf::Event event) {
    const int maxInputLength = 10;

    if (idBoxActive) {
        if (event.text.unicode == 8 && !idInput.empty()) { // Back space
            idInput.pop_back();
        }
        else if (event.text.unicode == 8 && idInput.empty() || event.text.unicode == 13 || event.text.unicode == 32) {
            // nothing
        }
        else if (event.text.unicode < 128 && idInput.size() < maxInputLength) {
            idInput += static_cast<char>(event.text.unicode);
        }
        idBoxContent.setString(idInput);
    }

    else if (pwBoxActive) {
        if (event.text.unicode == 8 && !pwInput.empty()) {
            pwInput.pop_back();
            pwHidden = "";
            for (std::size_t i = 0; i < pwInput.size(); ++i) { // Hide pw
                pwHidden += '*';
            }
        }
        else if (event.text.unicode == 8 && pwInput.empty() || event.text.unicode == 13 || event.text.unicode == 32) {
            // nothing
        }
        else if (event.text.unicode < 128 && pwInput.size() < maxInputLength) {
            pwInput += static_cast<char>(event.text.unicode);
            pwHidden += '*';
        }
        pwBoxContent.setString(pwHidden);
    }
}

void LoginSystem::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        else if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            // If click the login box
            if (idBox.getGlobalBounds().contains(mousePos)) {
                playClick();
                idBoxActive = true;
                pwBoxActive = false;
                std::cout << "ID box clicked!" << std::endl;
            }
            else if (pwBox.getGlobalBounds().contains(mousePos)) {
                playClick();
                idBoxActive = false;
                pwBoxActive = true;
                std::cout << "PASSWORD box clicked!" << std::endl;
            }

            else if (loginButton.getGlobalBounds().contains(mousePos)) {
                playClick();
                idBoxActive = false;
                pwBoxActive = false;
                std::cout << "CLICK button clicked!" << std::endl;
                // Get input
                std::string idInput = idBoxContent.getString();
                std::string pwInput = getPwInput();
                // Check if nothing or only spaces (but i made a restriction for space-bar actually)
                if (idInput.find_first_not_of(' ') == std::string::npos || pwInput.find_first_not_of(' ') == std::string::npos) {
                    // Case: Spaces-only
                    std::cout << "Invalid input!" << std::endl;
                    sf::RenderWindow newWindow(sf::VideoMode(650, 200), "ERROR");
                    sf::Font font;
                    if (font.loadFromFile("font/hangthedj.ttf")) {
                        sf::Text errorMessage("                 Invalid input! \n\n          Press ENTER to go back.", font, 25);
                        errorMessage.setFillColor(sf::Color::Red);
                        errorMessage.setPosition(-10, 60);

                        while (newWindow.isOpen()) {
                            sf::Event newEvent;
                            while (newWindow.pollEvent(newEvent)) {
                                if (newEvent.type == sf::Event::Closed) {
                                    newWindow.close();
                                }
                                else if (newEvent.type == sf::Event::KeyPressed && newEvent.key.code == sf::Keyboard::Enter) {
                                    newWindow.close();
                                }
                            }
                            if (clock.getElapsedTime().asSeconds() > 0.8) {
                                errorMessage.setFillColor(sf::Color(255 - errorMessage.getFillColor().r, 255 - errorMessage.getFillColor().g, 255 - errorMessage.getFillColor().b));
                                clock.restart();
                            }
                            newWindow.clear();
                            newWindow.draw(errorMessage);
                            newWindow.display();
                        }
                    } return;
                }
                // Test if already exists
                auto it = std::find_if(accountManager.accounts.begin(), accountManager.accounts.end(),
                    [idInput](const Account& acc) { return acc.id == idInput; });

                if (it == accountManager.accounts.end()) {
                    // Case 1: register
                    sf::RenderWindow newWindow(sf::VideoMode(650, 200), "REGISTER");
                    sf::Font font;
                    if (font.loadFromFile("font/hangthedj.ttf")) {
                        sf::Text errorMessage("          Press ENTER to register \n\n          with this ID & password.", font, 25);
                        errorMessage.setFillColor(sf::Color::Red);
                        errorMessage.setPosition(-15, 60);

                        sf::Clock clock;

                        while (newWindow.isOpen()) {
                            sf::Event newEvent;
                            while (newWindow.pollEvent(newEvent)) {
                                // Not saved
                                if (newEvent.type == sf::Event::Closed) {
                                    newWindow.close();
                                }
                                // Save to account "ENTER"
                                else if (newEvent.type == sf::Event::KeyPressed && newEvent.key.code == sf::Keyboard::Enter) {
                                    Account newAccount;
                                    newAccount.id = idInput;
                                    newAccount.password = pwInput;
                                    newAccount.gender = "UNKNOWN";
                                    newAccount.residence = "UNKNOWN";
                                    newAccount.interestLevel = "UNKNOWN";
                                    newAccount.followers = 0;
                                    newAccount.following = 0;
                                    accountManager.accounts.push_back(newAccount);
                                    accountManager.saveAccounts();
                                    std::cout << "New account saved!" << std::endl;
                                    LoginSystem::currentID.clear();
                                    LoginSystem::currentID.push_back(idInput);

                                    newWindow.close();
                                    window.close();
                                    UserMenu userMenu;
                                    userMenu.run();
                                }
                            }
                            if (clock.getElapsedTime().asSeconds() > 0.8) {
                                errorMessage.setFillColor(sf::Color(255 - errorMessage.getFillColor().r, 255 - errorMessage.getFillColor().g, 255 - errorMessage.getFillColor().b));
                                clock.restart();
                            }

                            newWindow.clear();
                            newWindow.draw(errorMessage);
                            newWindow.display();
                        }
                    }
                }
                else {
                    // Check if both id and password match
                    auto matchIt = std::find_if(accountManager.accounts.begin(), accountManager.accounts.end(),
                        [idInput, pwInput](const Account& acc) { return acc.id == idInput && acc.password == pwInput; });

                    // Check if only id matches
                    auto idMatchIt = std::find_if(accountManager.accounts.begin(), accountManager.accounts.end(),
                        [idInput](const Account& acc) { return acc.id == idInput; });

                    // Case 2: ID && PW
                    if (matchIt != accountManager.accounts.end()) {
                        std::cout << "ID and password match! Proceed to the next screen." << std::endl;

                        // Check if the logged-in account is a manager
                        bool isManager = (idInput == "MANAGER");

                        // Open the corresponding display
                        if (isManager) {
                            LoginSystem::currentID.clear();
                            LoginSystem::currentID.push_back(idInput);
                            window.close();
                            ManagerMenu managerMenu;
                            managerMenu.run();
                        }
                        else {
                            LoginSystem::currentID.clear();
                            LoginSystem::currentID.push_back(idInput);
                            window.close();
                            UserMenu userMenu;
                            userMenu.run();
                        }
                    }                                                            
                    else {
                        // Case 3: ID
                        sf::RenderWindow newWindow(sf::VideoMode(650, 200), "ERROR");
                        sf::Font font;
                        if (font.loadFromFile("font/hangthedj.ttf")) {
                            sf::Text errorMessage("  ID already exists & Password is incorrect!\n\n             Press ENTER to go back.", font, 23);
                            errorMessage.setFillColor(sf::Color::Red);
                            errorMessage.setPosition(-15, 60);

                            sf::Clock clock;

                            while (newWindow.isOpen()) {
                                sf::Event newEvent;
                                while (newWindow.pollEvent(newEvent)) {
                                    if (newEvent.type == sf::Event::Closed) {
                                        newWindow.close();
                                    }
                                    else if (newEvent.type == sf::Event::KeyPressed && newEvent.key.code == sf::Keyboard::Enter) {
                                        newWindow.close();
                                    }
                                }
                                if (clock.getElapsedTime().asSeconds() > 0.8) {
                                    errorMessage.setFillColor(sf::Color(255 - errorMessage.getFillColor().r, 255 - errorMessage.getFillColor().g, 255 - errorMessage.getFillColor().b));
                                    clock.restart();
                                }

                                newWindow.clear();
                                newWindow.draw(errorMessage);
                                newWindow.display();
                            }
                        }
                    }
                }
            }
        }

        else if (event.type == sf::Event::MouseMoved) {
            if (loginButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                loginButton.setFillColor(sf::Color::Red);
                borderRect.setOutlineColor(sf::Color::Red);
            }
            else {
                loginButton.setFillColor(sf::Color::White);
                borderRect.setOutlineColor(sf::Color::White);
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            handleTextEntered(event);
        }
    }
}

void LoginSystem::render() {
    window.clear();
    window.draw(mainText);
    window.draw(loginButton);
    window.draw(borderRect);

    window.draw(idBox);
    window.draw(pwBox);
    window.draw(idText);
    window.draw(pwText);

    window.draw(idBoxContent);
    idBoxContent.setPosition(idBox.getPosition().x + 10, idBox.getPosition().y + 30);
    window.draw(pwBoxContent);
    pwBoxContent.setPosition(pwBox.getPosition().x + 10, pwBox.getPosition().y + 15);

    window.display();
}
