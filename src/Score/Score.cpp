#include "Score.h"

Score::Score() {
    reset();
}

Score::~Score() {

}

int Score::getLevelId() {
    return levelId;
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

int Score::getLargestKillingSpree() {
    return largestKillingSpree;
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

bool Score::isRegistered() {
    return registered;
}

void Score::setLevelId(int levelId) {
    this->levelId = levelId;
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

void Score::setLargestKillingSpree(int largestKillingSpree) {
    this->largestKillingSpree = largestKillingSpree;
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

void Score::setRegistered(bool registered) {
    this->registered = registered;
}

void Score::reset() {
    levelId = 0;
    totalPoints = 0;
    boni = 0;
    damagesTaken = 0;
    enemiesKilled = 0;
    largestKillingSpree = 0;
    sheeps = 0;
    magmaCubes = 0;
    bristles = 0;

    registered = false;
}
