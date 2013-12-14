#include "Scoreboard.h"

Scoreboard::Scoreboard(GameView* view) : Displayable(view) {
    ScoreManager* scoreManager = ScoreManager::getInstance();

    float viewX(WINDOW_WIDTH);
    float viewY(WINDOW_HEIGHT);

    rect.setSize(sf::Vector2f(viewX, viewY));
    rect.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xFF));
    rect.setPosition(0, 0);

    damagesTakenText.setFont(globalFont);
    damagesTakenText.setCharacterSize(SCORES_CHAR_SIZE);

    enemiesKilledText.setFont(globalFont);
    enemiesKilledText.setCharacterSize(SCORES_CHAR_SIZE);

    pointsText.setFont(globalFont);
    pointsText.setCharacterSize(SCORES_CHAR_SIZE);


    view->addView(ViewLayer::SCORE, this);
}

Scoreboard::~Scoreboard() {

}

void Scoreboard::display() {
    ScoreManager* scoreManager = ScoreManager::getInstance();
    float viewX(WINDOW_WIDTH);
    float viewY(WINDOW_HEIGHT);

    int damages = scoreManager->getLastSavedScore().damage;

    int sheeps = scoreManager->getLastSavedScore().sheeps;
    int magmacubes = scoreManager->getLastSavedScore().magmacubes;
    int bristles = scoreManager->getLastSavedScore().bristles;
    int enemiesKilled = scoreManager->getLastSavedScore().enemiesKilled;
    std::string s("");
    std::string m("");
    std::string b("");
    if(sheeps > 0) {
        s = "\nSheeps: " + Utils::itos(sheeps) + " => " + Utils::itos(sheeps*SHEEP_DAMAGE) + " pts";
    }
    if(magmacubes > 0) {
        m = "\nMagma cubes: " + Utils::itos(magmacubes) + " => " + Utils::itos(magmacubes*MAGMACUBE_DAMAGE) + " pts";
    }
    if(bristles > 0) {
        b = "\nBristles: " + Utils::itos(bristles) + " => " + Utils::itos(bristles*BRISTLE_DAMAGE) + " pts";
    }
    std::string enemiesString = "Enemies killed: " + Utils::itos(enemiesKilled) + s + m + b;
    int points = scoreManager->getLastSavedScore().score;

    points = points-damages;

    damagesTakenText.setString("Damages taken: " + Utils::itos(damages));
    enemiesKilledText.setString(enemiesString);
    pointsText.setString("Points obtained: " + Utils::itos(points));

    damagesTakenText.setPosition(viewX/2-damagesTakenText.getLocalBounds().width/2, SCORES_STARTY);
    enemiesKilledText.setPosition(viewX/2-enemiesKilledText.getLocalBounds().width/2, SCORES_STARTY + damagesTakenText.getLocalBounds().height + SCORES_INTERSPACE);
    pointsText.setPosition(viewX/2-pointsText.getLocalBounds().width/2, SCORES_STARTY + damagesTakenText.getLocalBounds().height + enemiesKilledText.getLocalBounds().height + 2*SCORES_INTERSPACE);

    gameView->addDrawable(ViewLayer::SCORE, &rect);
    gameView->addDrawable(ViewLayer::SCORE, &damagesTakenText);
    gameView->addDrawable(ViewLayer::SCORE, &enemiesKilledText);
    gameView->addDrawable(ViewLayer::SCORE, &pointsText);
}
