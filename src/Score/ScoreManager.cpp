#include "ScoreManager.h"

// Initialisation of the singleton to NULL
ScoreManager* ScoreManager::managerInstance = NULL;

ScoreManager::ScoreManager() {
    for (size_t i = 0; i < NUMLEVELS; ++i) {
        Score score;
        gameScore.push_back(score);
    }
}

ScoreManager::~ScoreManager() {
}

// Gets the instance of the entityManger
ScoreManager* ScoreManager::getInstance() {
    if(!managerInstance) managerInstance = new ScoreManager();
    return managerInstance;
}

void ScoreManager::kill() {
    if(managerInstance) {
        delete managerInstance;
        managerInstance = NULL;
    }
}

Score ScoreManager::getScore(int level) {
    return gameScore[level];
}

std::vector<Score> ScoreManager::getGameScore() {
    return gameScore;
}

Score ScoreManager::getLastSavedScore() {
    return lastSavedScore;
}

Score ScoreManager::getCurrentScore() {
    return currentScore;
}

void ScoreManager::setLevel(int level) {
    currentScore.levelId = level;
}

void ScoreManager::takeBonus() {
    currentScore.bonus += 1;
}

void ScoreManager::addKillPoints(int points) {
    currentScore.killPoints += points;
}

void ScoreManager::addDamage(int damage) {
    currentScore.damagesTaken += damage;
}

void ScoreManager::addEnemyKilled() {
    currentScore.enemiesKilled += 1;
}

void ScoreManager::addKilledSheep() {
    currentScore.sheeps += 1;
}

void ScoreManager::addKilledMagmacube() {
    currentScore.magmacubes += 1;
}

void ScoreManager::addKilledBristle() {
    currentScore.bristles += 1;
}

void ScoreManager::computeTotalPoints() {
    int points = currentScore.killPoints - currentScore.damagesTaken + currentScore.bonus*BONUS_POINTS;

    if(currentScore.damagesTaken == 0) {
        points += BONUS_NODAMAGES;
    }
    currentScore.totalPoints = points;
}

void ScoreManager::saveCurrentScore() {
    int level = currentScore.levelId;
    lastSavedScore = currentScore;

    // if the player has done a better score
    if (gameScore[level].totalPoints < currentScore.totalPoints) {
        gameScore[level].killPoints = currentScore.killPoints;
        gameScore[level].totalPoints = currentScore.totalPoints;
        gameScore[level].bonus = currentScore.bonus;
        gameScore[level].damagesTaken = currentScore.damagesTaken;
        gameScore[level].enemiesKilled = currentScore.enemiesKilled;
        gameScore[level].sheeps = currentScore.sheeps;
        gameScore[level].magmacubes = currentScore.magmacubes;
        gameScore[level].bristles = currentScore.bristles;
    }
    resetCurrentScore();
}

// TODO
void ScoreManager::setLevelScore(int level, int totalPoints) {
    gameScore[level].totalPoints = totalPoints;
}

void ScoreManager::resetCurrentScore() {
    currentScore.levelId = 0;
    currentScore.killPoints = 0;
    currentScore.totalPoints = 0;
    currentScore.bonus = 0;
    currentScore.damagesTaken = 0;
    currentScore.enemiesKilled = 0;
    currentScore.sheeps = 0;
    currentScore.magmacubes = 0;
    currentScore.bristles = 0;
}

void ScoreManager::resetAllScores() {
    for (size_t i = 0; i < NUMLEVELS; ++i) {
        gameScore[i].levelId = 0;
        gameScore[i].killPoints = 0;
        gameScore[i].totalPoints = 0;
        gameScore[i].bonus = 0;
        gameScore[i].damagesTaken = 0;
        gameScore[i].enemiesKilled = 0;
        gameScore[i].sheeps = 0;
        gameScore[i].magmacubes = 0;
        gameScore[i].bristles = 0;
    }
}
