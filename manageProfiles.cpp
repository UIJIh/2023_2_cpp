#include "manageProfiles.h"

ManageProfile::ManageProfile(const std::string& filename) {
    loadFontandPng();
    //loadTextFromFile(filename);
    currentIndex = 0;
    accountManager.loadAccounts();
}

void ManageProfile::run() {
    window.create(sf::VideoMode(1400, 700), "Show Profile");

    while (window.isOpen()) {
        createDisplay();
        updateDisplayedText();
        handleEvents();
        render();
    }
}

void ManageProfile::loadFontandPng() {
    if (!font.loadFromFile("font/RobotoSlab-Bold.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    else if (!buttonfont.loadFromFile("font/hangthedj.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    if (!profileTexture.loadFromFile("media/profile.png")) {
        std::cerr << "Failed to load profile.png!" << std::endl;
    }
}

void ManageProfile::playClick() {
    if (clickBuffer.loadFromFile("media/click_sound.wav")) {
        clickSound.setBuffer(clickBuffer);
        clickSound.play();
    }
    else {
        std::cerr << "Failed to load click sound file!" << std::endl;
    }
}

void ManageProfile::setDisplay(sf::Text& text, const std::string& content, const sf::Font& font, int characterSize, const sf::Color& fillColor, float x, float y) {
    text.setString(content);
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setFillColor(fillColor);
    text.setPosition(x, y);
}

void ManageProfile::createDisplay() {

    currentID = LoginSystem::currentID[0];

    //profile image
    profileSprite.setTexture(profileTexture);
    profileSprite.setScale(0.4f, 0.4f);
    profileSprite.setPosition(150, 260);

    myprofileBox.setSize(sf::Vector2f(300, 350));
    myprofileBox.setFillColor(sf::Color(225, 225, 225));
    myprofileBox.setPosition(100, 220);

    othersprofileBox.setSize(sf::Vector2f(850, 350));
    othersprofileBox.setFillColor(sf::Color(225, 225, 225));
    othersprofileBox.setPosition(450, 220);

    sf::FloatRect maintextRect = maintext.getLocalBounds();
    sf::FloatRect nextRect = nextButton.getLocalBounds();
    sf::FloatRect beforeRect = beforeButton.getLocalBounds();
    sf::FloatRect backRect = backButton.getLocalBounds();
    sf::FloatRect myprofileRect = myprofile.getLocalBounds();

    setDisplay(maintext, "[USER PROFILES]", buttonfont, 50, sf::Color::White, (window.getSize().x - maintextRect.width) / 2, (window.getSize().y - maintextRect.height) / 2 - 250);
    setDisplay(nextButton, "NEXT", buttonfont, 30, sf::Color::White, 1200, 620);
    setDisplay(beforeButton, "BEFORE", buttonfont, 30, sf::Color::White, 50, 620);
    setDisplay(backButton, "BACK", buttonfont, 30, sf::Color::White, (window.getSize().x - backRect.width) / 2 + 3, 620);
    setDisplay(myprofile, "< MY PROFILE >", buttonfont, 30, sf::Color::Black, 110, 475);
    setDisplay(detailClick, "click for more info", font, 18, sf::Color::Red, 170, 520);
    setDisplay(othersIdText1, "Name : ", buttonfont, 25, sf::Color::Black, 480, 250);
    setDisplay(othersLevelText1, "Currently Learning : ", buttonfont, 25, sf::Color::Black, 480, 290);
    setDisplay(othersFollowingText1, "Following : ", buttonfont, 25, sf::Color::Black, 480, 330);
    setDisplay(othersFollowerText1, "Followers : ", buttonfont, 25, sf::Color::Black, 480, 370);
    setDisplay(othersGenderText1, "Gender : ", buttonfont, 25, sf::Color::Black, 480, 410);
    setDisplay(othersResidenceText1, "Based on : ", buttonfont, 25, sf::Color::Black, 480, 450);
    setDisplay(messageText1, "Message  ", buttonfont, 25, sf::Color::Black, 480, 490);
    setDisplay(messageText2, "Click here to send Message", buttonfont, 25, sf::Color::Black, 850, 490);

    borderRect1.setSize(sf::Vector2f(backRect.width + 10, backRect.height + 10));
    borderRect1.setPosition((window.getSize().x - backRect.width) / 2, 620);
    borderRect1.setFillColor(sf::Color::Transparent);
    borderRect1.setOutlineThickness(4);
    borderRect1.setOutlineColor(sf::Color::White);

}


void ManageProfile::updateDisplayedText() {

    std::ifstream file("accounts.txt");
    if (file.is_open()) {
        lines.clear();
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    else {
        std::cerr << "Failed to open file account.txt" << std::endl;
    }

    for (i = currentIndex; i < currentIndex + 1 && i < lines.size(); ++i) {

        spacePos1 = lines[i].find(' '); //name
        spacePos2 = lines[i].find(' ', spacePos1 + 1);  // pw
        spacePos3 = lines[i].find(' ', spacePos2 + 1);  // gender
        spacePos4 = lines[i].find(' ', spacePos3 + 1);  // residence
        spacePos5 = lines[i].find(' ', spacePos4 + 1);  // level
        spacePos6 = lines[i].find(' ', spacePos5 + 1);  // follower and last:following

        if (lines[i].substr(0, spacePos1) == currentID) {
            if (i == lines.size() - 1)
                break;
            else
                i++;
        }

        othersId = lines[i].substr(0, spacePos1);
        othersID = othersId;
        othersLevel = lines[i].substr(spacePos4 + 1, spacePos5 - spacePos4 - 1);
        othersFollowing = lines[i].substr(spacePos6 + 1);
        othersFollower = lines[i].substr(spacePos5 + 1, spacePos6 - spacePos5 - 1);
        othersGender = lines[i].substr(spacePos2 + 1, spacePos3 - spacePos2 - 1);
        othersResidence = lines[i].substr(spacePos3 + 1, spacePos4 - spacePos3 - 1);
    }

    displayedText = othersId + "\n";

    setDisplay(followButtonText, "Click here", buttonfont, 20, sf::Color::Black, 1079, 345);

    //from here
    std::ifstream inFile("following.txt");

    auto idMatchIt = std::find_if(accountManager.accounts.begin(), accountManager.accounts.end(),
        [this](const Account& acc) { return acc.id == currentID; });

    bool fileExists = inFile.is_open();

    if (!fileExists) {
        std::cout << "Make a new file" << std::endl;
        std::ofstream newFile("following.txt", std::ios::app);
        return;
    }
    std::string line;
    bool userExists = false;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string userId;
        iss >> userId;

        if (userId == currentID) {
            userExists = true;
            isFollowing = line.find(othersId) != std::string::npos;
        }
    }
    if (!userExists) {
        isFollowing = false;
    }
    inFile.close();


    sf::Color Pink(255, 192, 203);
    followButtonText.setString(isFollowing ? "click here\n\nto unfollow" : "click here\n\nto follow");
    followButton.setSize(sf::Vector2f(170, 100));
    followButton.setFillColor(Pink);
    followButton.setPosition(1070, 330);

    setDisplay(othersIdText2, othersId, font, 25, sf::Color::Black, 850, 250);
    setDisplay(othersLevelText2, othersLevel, font, 25, sf::Color::Black, 850, 290);
    setDisplay(othersFollowingText2, othersFollowing, font, 25, sf::Color::Black, 850, 330);
    setDisplay(othersFollowerText2, othersFollower, font, 25, sf::Color::Black, 850, 370);
    setDisplay(othersGenderText2, othersGender, font, 25, sf::Color::Black, 850, 410);
    setDisplay(othersResidenceText2, othersResidence, font, 25, sf::Color::Black, 850, 450);
}


void ManageProfile::following(const std::string& currentId, const std::string& othersId) {
    std::ifstream inFile("following.txt");
    std::ofstream outFile("following_tmp.txt");

    auto idMatchIt = std::find_if(accountManager.accounts.begin(), accountManager.accounts.end(),
        [this](const Account& acc) { return acc.id == currentID; });

    bool fileExists = inFile.is_open();

    if (!fileExists) {
        std::cout << "Make a new file" << std::endl;
        std::ofstream newFile("following.txt", std::ios::app);
        return;
    }

    std::string line;
    bool userExists = false;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string userId;
        iss >> userId;

        if (userId == currentId) {
            userExists = true;
            isFollowing = line.find(othersId) != std::string::npos;

            if (!isFollowing) {
                if (!line.empty() && line.back() != ' ') {
                    line += " ";
                }
                line += othersId;
                std::cout << "Now " << userId << " follows " << othersId << std::endl;
            }
            else {
                size_t pos = line.find(othersId);
                if (pos != std::string::npos) {
                    line.erase(pos, othersId.length());
                }

                std::cout << "Unfollow " << othersId << std::endl;
            }

            if (idMatchIt != accountManager.accounts.end()) {
                if (!isFollowing) {
                    idMatchIt->following += 1;
                }
                else {
                    idMatchIt->following -= 1;
                }
                accountManager.saveAccounts();
            }
        }
        outFile << line << std::endl;
    }

    if (!userExists) {
        outFile << currentId + " " + othersId << std::endl;
        std::cout << "Add " << currentId << " in following.txt" << std::endl;

        if (idMatchIt != accountManager.accounts.end()) {
            idMatchIt->following += 1;
            accountManager.saveAccounts();
            isFollowing = false;
        }
    }

    outFile.close();
    inFile.close();

    if (fileExists) {
        // Rename the temporary file to replace the original file
        std::remove("following.txt");
        std::rename("following_tmp.txt", "following.txt");
    }
}

void ManageProfile::follower(const std::string& othersId, const std::string& currentId) {
    std::ifstream inFile("follower.txt");
    std::ofstream outFile("follower_tmp.txt");

    auto idMatchIt = std::find_if(accountManager.accounts.begin(), accountManager.accounts.end(),
        [this](const Account& acc) { return acc.id == othersID; });

    bool fileExists = inFile.is_open();

    if (!fileExists) {
        std::cout << "Make a new file" << std::endl;
        std::ofstream newFile("follower.txt", std::ios::app);
        return;
    }

    std::string line;
    bool userExists = false;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string userId;
        iss >> userId;

        if (userId == othersId) {
            userExists = true;
            bool isFollower = line.find(currentId) != std::string::npos;

            if (!isFollower) {
                if (!line.empty() && line.back() != ' ') {
                    line += " ";
                }
                line += currentId;
            }
            else {
                size_t pos = line.find(currentId);
                if (pos != std::string::npos) {
                    line.erase(pos, currentId.length());
                }
            }

            if (idMatchIt != accountManager.accounts.end()) {
                if (!isFollower) {
                    idMatchIt->followers += 1;
                }
                else {
                    idMatchIt->followers -= 1;
                }
                accountManager.saveAccounts();
            }
        }

        outFile << line << std::endl;
    }

    if (!userExists) {
        outFile << othersId + " " + currentId << std::endl;
        std::cout << "Add " << othersId << " in follower.txt" << std::endl;

        if (idMatchIt != accountManager.accounts.end()) {
            idMatchIt->followers += 1;
            accountManager.saveAccounts();
        }
    }

    outFile.close();
    inFile.close();

    if (fileExists) {
        // Rename the temporary file to replace the original file
        std::remove("follower.txt");
        std::rename("follower_tmp.txt", "follower.txt");
    }
}

void ManageProfile::handleMouseOver(sf::Text& button) {
    button.setFillColor(sf::Color::Red);
}

void ManageProfile::handleMouseOut(sf::Text& button) {
    button.setFillColor(sf::Color::White);
}

void ManageProfile::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (nextButton.getGlobalBounds().contains(mousePos) && !nextButtonActive) {
                playClick();
                nextButtonActive = true;
                beforeButtonActive = false;
                myprofileActive = false;
                followButtonActive = false;
                messageBox1Active = false;


                std::cout << "NEXT button clicked!" << std::endl;
                if (currentIndex + 1 < lines.size()) {
                    currentIndex += 1;
                    updateDisplayedText();
                }
            }
            else if (beforeButton.getGlobalBounds().contains(mousePos) && !beforeButtonActive) {
                playClick();
                nextButtonActive = false;
                beforeButtonActive = true;
                myprofileActive = false;
                followButtonActive = false;
                messageBox1Active = false;


                std::cout << "BEFORE button clicked!" << std::endl;
                if (currentIndex >= 1) {
                    currentIndex -= 1;
                    updateDisplayedText();
                }
            }
            else if (backButton.getGlobalBounds().contains(mousePos)) {
                playClick();
                std::cout << "BACK button clicked! Opening previous window..." << std::endl;
                window.close();
                UserMenu userMenu;
                userMenu.run(); // later must be replaced
            }
            else if (myprofile.getGlobalBounds().contains(mousePos) && !myprofileActive) {
                playClick();
                nextButtonActive = false;
                beforeButtonActive = false;
                myprofileActive = true;
                followButtonActive = false;
                messageBox1Active = false;

                std::cout << "my profile clicked!" << std::endl;
                window.close();
                CurrentProfile currentProfile;
                currentProfile.run();

            }
            else if (followButton.getGlobalBounds().contains(mousePos) && !followButtonActive) {
                playClick();
                nextButtonActive = false;
                beforeButtonActive = false;
                myprofileActive = false;
                followButtonActive = true;
                messageBox1Active = false;

                std::cout << "follow button clicked! " << std::endl;

                following(currentID, othersId);
                follower(othersId, currentID);
                updateDisplayedText();
            }
            else if (messageText2.getGlobalBounds().contains(mousePos) && !othersIdTextActive) {
                playClick();
                nextButtonActive = false;
                beforeButtonActive = false;
                myprofileActive = false;
                followButtonActive = false;
                messageBox1Active = true;
                window.close();

                Message message(currentID, othersID);
                message.run();

                std::cout << "Message Box clicked!" << displayedText << std::endl;
            }
        }
        else if (event.type == sf::Event::MouseMoved) {
            // Make it Red 
            if (nextButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                handleMouseOver(nextButton);
            }
            else {
                handleMouseOut(nextButton);
            }
            if (beforeButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                handleMouseOver(beforeButton);
            }
            else {
                handleMouseOut(beforeButton);
            }
            if (backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                handleMouseOver(backButton);
                borderRect1.setOutlineColor(sf::Color::Red);
            }
            else {
                handleMouseOut(backButton);
                borderRect1.setOutlineColor(sf::Color::White);

            }
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        nextButtonActive = false;
        beforeButtonActive = false;
        myprofileActive = false;
        othersIdTextActive = false;
        followButtonActive = false;
        messageBox1Active = false;
    }
}


void ManageProfile::render() {
    window.clear();

    window.draw(myprofileBox);
    window.draw(myprofile);
    window.draw(detailClick);
    window.draw(profileSprite);

    window.draw(maintext);
    window.draw(nextButton);
    window.draw(beforeButton);
    window.draw(backButton);
    window.draw(borderRect1);

    window.draw(othersprofileBox);
    window.draw(othersIdText1);
    window.draw(othersIdText2);
    window.draw(othersLevelText1);
    window.draw(othersLevelText2);
    window.draw(othersFollowingText1);
    window.draw(othersFollowingText2);
    window.draw(othersFollowerText1);
    window.draw(othersFollowerText2);
    window.draw(othersGenderText1);
    window.draw(othersGenderText2);
    window.draw(othersResidenceText1);
    window.draw(othersResidenceText2);
    window.draw(followButton);
    window.draw(followButtonText);
    window.draw(messageText1);
    window.draw(messageText2);

    window.display();
}
