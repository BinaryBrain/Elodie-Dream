#include "ScoreBoard.h"

const int ScoreBoard::CHAR_SIZE = 25;
const float ScoreBoard::INTERSPACE = 100;
const float ScoreBoard::STARTY = 100;

ScoreBoard::ScoreBoard(GameView& gameView) : Displayable(gameView)
{
    float viewX(WINDOW_WIDTH);
    float viewY(WINDOW_HEIGHT);

    rect.setSize(sf::Vector2f(viewX, viewY));
    rect.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xFF));
    rect.setPosition(0, 0);

    damagesTakenText.setFont(globalFont);
    damagesTakenText.setCharacterSize(CHAR_SIZE);

    enemiesKilledText.setFont(globalFont);
    enemiesKilledText.setCharacterSize(CHAR_SIZE);

    boniText.setFont(globalFont);
    boniText.setCharacterSize(CHAR_SIZE);

    pointsText.setFont(globalFont);
    pointsText.setCharacterSize(CHAR_SIZE);


    gameView.addView(ViewLayer::SCORE, this);
}

ScoreBoard::~ScoreBoard()
{

}

void ScoreBoard::display()
{
    gameView.addDrawable(ViewLayer::SCORE, &rect);
    gameView.addDrawable(ViewLayer::SCORE, &damagesTakenText);
    gameView.addDrawable(ViewLayer::SCORE, &enemiesKilledText);
    gameView.addDrawable(ViewLayer::SCORE, &boniText);
    gameView.addDrawable(ViewLayer::SCORE, &pointsText);
}

void ScoreBoard::prepareText()
{
    ScoreManager& scoreManager = ScoreManager::getInstance();
    float viewX(WINDOW_WIDTH);

    Score score = scoreManager.getCurrentScore();
    int boni = score.getBoni();
    int damages = score.getDamagesTaken();
    int totalPoints = score.getTotalPoints();

    std::string enemiesString = "Enemies killed: " + Utils::itos(score.getEnemiesKilled()) + " => " + Utils::itos(scoreManager.getKillPoints()) + " pts";

    std::string p = "";
    if (damages == 0)
    {
        p = "Bonus 0 damages taken: "+ Utils::itos(ScoreManager::BONUS_NODAMAGES) +" pts !\n";
    }

    p += "Points obtained: " + Utils::itos(totalPoints) + " pts " + scoreManager.getScoreString();

    damagesTakenText.setString("Damages taken: " + Utils::itos(damages));
    enemiesKilledText.setString(enemiesString);
    boniText.setString("Boni collected: "+ Utils::itos(boni)+" => " + Utils::itos(boni * Bonus::POINTS) + " pts");
    pointsText.setString(p);

    damagesTakenText.setPosition(viewX/2-damagesTakenText.getLocalBounds().width/2, STARTY);
    enemiesKilledText.setPosition(viewX/2-enemiesKilledText.getLocalBounds().width/2, STARTY + damagesTakenText.getLocalBounds().height + INTERSPACE);
    boniText.setPosition(viewX/2-boniText.getLocalBounds().width/2, STARTY + damagesTakenText.getLocalBounds().height + enemiesKilledText.getLocalBounds().height + 2*INTERSPACE);
    pointsText.setPosition(viewX/2-pointsText.getLocalBounds().width/2, STARTY + damagesTakenText.getLocalBounds().height + enemiesKilledText.getLocalBounds().height + boniText.getLocalBounds().height +3*INTERSPACE);
}
