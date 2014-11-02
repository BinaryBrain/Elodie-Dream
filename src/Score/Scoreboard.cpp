#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(GameView* gameView) : Displayable(gameView) {
    float viewX(WINDOW_WIDTH);
    float viewY(WINDOW_HEIGHT);

    rect.setSize(sf::Vector2f(viewX, viewY));
    rect.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xFF));
    rect.setPosition(0, 0);

    damagesTakenText.setFont(globalFont);
    damagesTakenText.setCharacterSize(SCORES_CHAR_SIZE);

    enemiesKilledText.setFont(globalFont);
    enemiesKilledText.setCharacterSize(SCORES_CHAR_SIZE);

    boniText.setFont(globalFont);
    boniText.setCharacterSize(SCORES_CHAR_SIZE);

    pointsText.setFont(globalFont);
    pointsText.setCharacterSize(SCORES_CHAR_SIZE);


    gameView->addView(ViewLayer::SCORE, this);
}

ScoreBoard::~ScoreBoard() {

}

void ScoreBoard::display() {
    gameView->addDrawable(ViewLayer::SCORE, &rect);
    gameView->addDrawable(ViewLayer::SCORE, &damagesTakenText);
    gameView->addDrawable(ViewLayer::SCORE, &enemiesKilledText);
    gameView->addDrawable(ViewLayer::SCORE, &boniText);
    gameView->addDrawable(ViewLayer::SCORE, &pointsText);
}

void ScoreBoard::prepareText() {
    ScoreManager* scoreManager = ScoreManager::getInstance();
    float viewX(WINDOW_WIDTH);

    int boni = scoreManager->getCurrentScore().getBoni();
    int damages = scoreManager->getCurrentScore().getDamagesTaken();
    int sheeps = scoreManager->getCurrentScore().getSheeps();
    int magmaCubes = scoreManager->getCurrentScore().getMagmaCubes();
    int bristles = scoreManager->getCurrentScore().getBristles();
    int enemiesKilled = scoreManager->getCurrentScore().getEnemiesKilled();
    int totalPoints = scoreManager->getCurrentScore().getTotalPoints();
    int levelId = scoreManager->getCurrentScore().getLevelId();
    int bestScore = scoreManager->getGameScore()[levelId].getTotalPoints();

    std::string s = "";
    std::string m = "";
    std::string b = "";
    if(sheeps > 0) {
        s = "\nSheeps: " + Utils::itos(sheeps) + " => " + Utils::itos(sheeps*SHEEP_DAMAGE) + " pts";
    }
    if(magmaCubes > 0) {
        m = "\nMagma cubes: " + Utils::itos(magmaCubes) + " => " + Utils::itos(magmaCubes*MAGMACUBE_DAMAGE) + " pts";
    }
    if(bristles > 0) {
        b = "\nBristles: " + Utils::itos(bristles) + " => " + Utils::itos(bristles*BRISTLE_DAMAGE) + " pts";
    }
    std::string enemiesString = "Enemies killed: " + Utils::itos(enemiesKilled) + s + m + b;

    std::string p = "";
    if(damages == 0) {
        p = "Bonus 0 damages taken: "+ Utils::itos(BONUS_NODAMAGES) +" pts !\n";
    }

    p += "Points obtained: " + Utils::itos(totalPoints) + " pts";

    if (totalPoints > bestScore) {
        p += " (new record! :3)";
    } else {
        p += " (best score: " + Utils::itos(bestScore) + ")";
    }

    damagesTakenText.setString("Damages taken: " + Utils::itos(damages));
    enemiesKilledText.setString(enemiesString);
    boniText.setString("Boni collected: "+ Utils::itos(boni)+" => " + Utils::itos(boni*BONUS_POINTS) + " pts");
    pointsText.setString(p);

    damagesTakenText.setPosition(viewX/2-damagesTakenText.getLocalBounds().width/2, SCORES_STARTY);
    enemiesKilledText.setPosition(viewX/2-enemiesKilledText.getLocalBounds().width/2, SCORES_STARTY + damagesTakenText.getLocalBounds().height + SCORES_INTERSPACE);
    boniText.setPosition(viewX/2-boniText.getLocalBounds().width/2, SCORES_STARTY + damagesTakenText.getLocalBounds().height + enemiesKilledText.getLocalBounds().height + 2*SCORES_INTERSPACE);
    pointsText.setPosition(viewX/2-pointsText.getLocalBounds().width/2, SCORES_STARTY + damagesTakenText.getLocalBounds().height + enemiesKilledText.getLocalBounds().height + boniText.getLocalBounds().height +3*SCORES_INTERSPACE);
}
