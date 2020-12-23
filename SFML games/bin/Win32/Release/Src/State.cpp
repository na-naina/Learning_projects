#include "State.h"

//State : GameSession



GameSession::GameSession(float Width, float Height, int Size, int WinCondition, int PlayerNumber)
    : isEnded(false), width(Width), height(Height)
{
    this->GameGrid = new GraphMatrix(Size, std::min(Width, Height), WinCondition, PlayerNumber);

    font.loadFromFile("Src/resources/OpenSans-Regular.ttf");

    WinnerText.setFont(font);
    WinnerText.setString(" ");


    GameEnded.openFromFile("Src/resources/Congratulations-sound.ogg");
    GameEnded.setVolume(50);

    EndScrBackground = sf::RectangleShape(sf::Vector2f(Width, Height));

    EndScrBackground.setFillColor(sf::Color(220, 200, 240));


    WinnerText.setFillColor(sf::Color(100, 0, 200));
    WinnerText.setCharacterSize(80);


}


GameSession::~GameSession()
{
	delete this->GameGrid;
}

void GameSession::render(sf::RenderWindow* window)
{
    if (isEnded == 0)
        this->GameGrid->DrawMatrix(window);
    else
        drawEndScreen(window);


}



void GameSession::drawEndScreen(sf::RenderWindow* window)
{
    window->draw(EndScrBackground);
    window->draw(WinnerText);
      
}

void GameSession::update()
{

    this->GameGrid->UpdateMatrix();


    int a = this->GameGrid->GetGrid()->GameFinished();

    if(isEnded == 0)
    if (a >= 0) {
        if (a == 0) {
            WinnerText.setString("Tie");
            sf::FloatRect bound = WinnerText.getLocalBounds();
            WinnerText.setPosition(sf::Vector2f((width / 2) - bound.width / 2, 0.4 * (height)));
            isEnded = true;
            GameEnded.play();
        }
        else {
            isEnded = true;
            WinnerText.setString("Winner is player " + std::to_string(a));
            sf::FloatRect bound = WinnerText.getLocalBounds();
            WinnerText.setPosition(sf::Vector2f((width / 2) - bound.width / 2, 0.4 * (height)));
            GameEnded.play();
        }
    }

}


void GameSession::updateSFEvents(sf::Event sfEvent)
{
    if (sfEvent.type == sf::Event::MouseMoved)
    {
        this->GameGrid->UpdateHoverOverTile(sfEvent);
    }


    if (sfEvent.type == sf::Event::MouseButtonPressed)
    {
        if (sfEvent.mouseButton.button == sf::Mouse::Left)
            this->GameGrid->ClickOnTile();
    }

}



//State : Title Screen

TitleScreen::TitleScreen(float Width, float Height)
    :isEnded(0)
{

    BackgroundMusic.openFromFile("Src/resources/1234.ogg");
    BackgroundMusic.setVolume(0.2);
    BackgroundMusic.play();
    BackgroundImg.loadFromFile("Src/resources/Background.jpg");
    BackgroundSprite.setTexture(BackgroundImg);
    PlayerInput = "";


    font.loadFromFile("Src/resources/OpenSans-Regular.ttf");
    Title.setFont(font);
    Title.setString("NxN by D.G.");
    Title.setCharacterSize(48);
    Title.setLineSpacing(0.7);
    Input.setFont(font);
    EnterValues.setFont(font);
    EnterValues.setString("Enter your values as in the example:");
    Example.setCharacterSize(20);
    Example.setString("Example:\n 10, 4, 8\n(where 10 is Grid Size, 4 is Player number, 8 is win condition)");
    Example.setFont(font);
    InputField.setSize(sf::Vector2f(3 * Width / 4, 0.2 * Height));
    InputField.setOutlineColor(sf::Color(255, 255, 255));
    InputField.setOutlineThickness(3);
    Input.setCharacterSize(70);
    Input.setString("Start typing...");
    Input.setFillColor(sf::Color(0, 0, 0));
    Error.setString("Entered input doesn't correspond to the example, try again");
    Error.setFont(font);
    Error.setFillColor(sf::Color(255, 0, 0, 0));


    sf::FloatRect bound = Title.getLocalBounds();
    Title.setPosition(sf::Vector2f((Width / 2) - bound.width / 2, 0.1 * (Height)));

    bound = EnterValues.getLocalBounds();
    EnterValues.setPosition(sf::Vector2f(Width/2 - bound.width/2, 0.2*Height));


    bound = Example.getLocalBounds();
    Example.setPosition(sf::Vector2f(Width / 2 - bound.width / 2, 0.3 * Height));

    InputField.setPosition(sf::Vector2f(Width / 8, 0.5 * Height));
    Input.setPosition(sf::Vector2f(Width / 8 + 10.f, (0.5 * Height + 10.f)));

    bound = Error.getLocalBounds();
    Error.setPosition(sf::Vector2f(Width/2 - bound.width / 2, Height * 0.8));
   
}

TitleScreen::TitleScreen()
  : isEnded(0)
{
    BackgroundImg.loadFromFile("Src/resources/Background.jpg");
    BackgroundSprite.setTexture(BackgroundImg);
  
  

    font.loadFromFile("Src/resources/OpenSans-Regular.ttf");
    Title.setFont(font);
    Title.setString("Emberessing project\n by Dmytro Golodnikov\ a.k.a. tarantulala");
    Title.setCharacterSize(48); 
    Input.setFont(font);
    EnterValues.setFont(font);
    EnterValues.setString("Enter your values as in the example:");
    Example.setString("Example:\n 10, 4, 8\n\n where 10 is Grid Size, 4 is Player number, 8 is win condition");
    Example.setFont(font);

 
}


void TitleScreen::render(sf::RenderWindow* window)
{
    window->draw(BackgroundSprite);

    window->draw(Title);
    window->draw(EnterValues);
    window->draw(Example);
    window->draw(InputField);
    window->draw(Input);
    window->draw(Error);

}

void TitleScreen::updateSFEvents(sf::Event sfEvent)
{
    if (sfEvent.type == sf::Event::TextEntered)
    {
        if (sfEvent.text.unicode == '\b') {
            if (PlayerInput.size() > 0)
                PlayerInput.erase(PlayerInput.size() - 1, 1);
        }
        else if ((sfEvent.text.unicode < 128))
            PlayerInput += static_cast<char>(sfEvent.text.unicode);

        Input.setString(PlayerInput);
    }

    if (sfEvent.type == sf::Event::KeyPressed)
    {
        if (sfEvent.key.code == sf::Keyboard::Key::Enter) {
            if (InputIsValid(PlayerInput)) {
                isEnded = true;
            }
            else {
                Error.setFillColor(sf::Color(255, 0, 0));
            }
        }
    }
}

std::string TitleScreen::GetInput()
{
    return PlayerInput;
}

bool TitleScreen::InputIsValid(std::string InputString)
{
    int CommaCount = 0;

    for (int i = 0; i < InputString.size(); i++) {
        if ((isdigit(InputString[i]) || (InputString[i] == ' ')))
            continue;
        else if ((InputString[i] == ',')) {
            CommaCount++;
            continue;
        } else
            return false;
    }

    if (CommaCount != 2)
        return false;
    
    if (InputString[0] == ',')
        return false;

    for (int i = 0; CommaCount != -1; i++) {


        if (InputString[i] == ',') {
            if (!isdigit(InputString[i - 1]))
                return false;
            CommaCount--;
        }

        if (CommaCount == 0) {
            bool metDigit = 0;
            while (i < InputString.size()) {
                if (isdigit(InputString[i]))
                    metDigit = true;
                i++;
            }
            if (metDigit == 0)
                return false;
            CommaCount--;
        }
    }
    return true;
}

int TitleScreen::GetGridSize()
{
    int i = 0;
    while (PlayerInput[i] != ',')
        i++;
    i--;
    int ans = 0;
    int NumberSize = 0;
    while (isdigit(PlayerInput[i])&& i >= 0) {
        NumberSize++;
        i--;
    }
    std::string a = PlayerInput.substr(i+1, NumberSize);
    ans += std::stoi(a);

    return ans;
}

int TitleScreen::GetPlayerNumber()
{
    int i = 0;
    while (PlayerInput[i] != ',')
        i++;
    i++;
    while (PlayerInput[i] != ',')
        i++;

    i--;
    int ans = 0;
    int NumberSize = 0;
    while (isdigit(PlayerInput[i]) && PlayerInput[i] != ',') {
        NumberSize++;
        i--;
    }

    std::string a = PlayerInput.substr(i + 1, NumberSize);
    ans += std::stoi(a);

    return ans;
}

int TitleScreen::GetWinCondition()
{
    int i = 0;
    while (PlayerInput[i] != ',')
        i++;
    i++;
    while (PlayerInput[i] != ',')
        i++;
    i++;
    int ans = 0;

    std::string a = PlayerInput.substr(i, PlayerInput.length()-i);
    ans += std::stoi(a);

    return ans;
}
