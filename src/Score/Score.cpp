#include "Score.h"

Score::Score() {

}

Score::~Score() {

}

int Score::getLevelId() {
    return levelId;
}

int Score::getKillPoints() {
    return killPoints;
}

int Score::getTotalPoints() {
    return totalPoints;
}

int Score::getBoni() {
    return boni;
}

int Score::getDamagesTaken() {
    return damagesTaken;
}

int Score::getEnemiesKilled() {
    return enemiesKilled;
}

int Score::getSheeps() {
    return sheeps;
}

int Score::getMagmaCubes() {
    return magmaCubes;
}

int Score::getBristles() {
    return bristles;
}

void Score::setLevelId(int levelId) {
    this->levelId = levelId;
}
void Score::setKillPoints(int killPoints) {
    this->killPoints = killPoints;
}
void Score::setTotalPoints(int totalPoints) {
    this->totalPoints = totalPoints;
}
void Score::setBoni(int boni) {
    this->boni = boni;
}

void Score::setDamagesTaken(int damagesTaken) {
    this->damagesTaken = damagesTaken;
}

void Score::setEnemiesKilled(int enemiesKilled) {
    this->enemiesKilled = enemiesKilled;
}

void Score::setSheeps(int sheeps) {
    this->sheeps = sheeps;
}

void Score::setMagmaCubes(int magmaCubes) {
    this->magmaCubes = magmaCubes;
}

void Score::setBristles(int bristles) {
    this->bristles = bristles;
}

void Score::reset() {
    levelId = 0;
    killPoints = 0;
    totalPoints = 0;
    boni = 0;
    damagesTaken = 0;
    enemiesKilled = 0;
    sheeps = 0;
    magmaCubes = 0;
    bristles = 0;
}
