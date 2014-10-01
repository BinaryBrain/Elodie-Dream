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

void ScoreManager::takeBonus() {
    currentScore.bonus += 1;
}

void ScoreManager::addScore(int score) {
    currentScore.score += score;
}

void ScoreManager::addDamage(int damage) {
    currentScore.damage += damage;
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

void ScoreManager::computeTotalScore() {
    int points = currentScore.score - currentScore.damage + currentScore.bonus*BONUS_POINTS;

    if(currentScore.damage == 0) {
        points += BONUS_NODAMAGES;
    }
    currentScore.totalScore = points;
}

void ScoreManager::saveScore(int level) {
    lastSavedScore = currentScore;

    std::cout << "Score for level " << level << ": " << currentScore.totalScore << std::endl;

    // if the player has done a better score
    if (gameScore[level].totalScore < currentScore.totalScore) {
        gameScore[level].score = currentScore.score;
        gameScore[level].totalScore = currentScore.totalScore;
        gameScore[level].bonus = currentScore.bonus;
        gameScore[level].damage = currentScore.damage;
        gameScore[level].enemiesKilled = currentScore.enemiesKilled;
        gameScore[level].sheeps = currentScore.sheeps;
        gameScore[level].magmacubes = currentScore.magmacubes;
        gameScore[level].bristles = currentScore.bristles;
    }
    resetCurrentScore();
}

// TODO
void ScoreManager::setLevelScore(int level, int score) {
    gameScore[level].score = score;
}

void ScoreManager::resetCurrentScore() {
    currentScore.score = 0;
    currentScore.totalScore = 0;
    currentScore.bonus = 0;
    currentScore.damage = 0;
    currentScore.enemiesKilled = 0;
    currentScore.sheeps = 0;
    currentScore.magmacubes = 0;
    currentScore.bristles = 0;
}

void ScoreManager::resetAllScores() {
    for (size_t i = 0; i < NUMLEVELS; ++i) {
        gameScore[i].score = 0;
        gameScore[i].totalScore = 0;
        gameScore[i].bonus = 0;
        gameScore[i].damage = 0;
        gameScore[i].enemiesKilled = 0;
        gameScore[i].sheeps = 0;
        gameScore[i].magmacubes = 0;
        gameScore[i].bristles = 0;
    }
}
