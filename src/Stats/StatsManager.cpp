#include "StatsManager.h"

StatsManager::StatsManager() {
    reset();
}

StatsManager::~StatsManager() {

}

StatsManager& StatsManager::getInstance() {
    static StatsManager instance;
    return instance;
}

int StatsManager::getTotalBoni() {
    return totalBoni;
}

int StatsManager::getTotalDamages() {
    return totalDamages;
}

int StatsManager::getTotalDeaths() {
    return totalDeaths;
}

int StatsManager::getTotalSheeps() {
    return totalSheeps;
}

int StatsManager::getTotalMagmaCubes() {
    return totalMagmaCubes;
}

int StatsManager::getTotalBristles() {
    return totalBristles;
}

int StatsManager::getTotalEnemiesKilled() {
    return totalSheeps + totalMagmaCubes + totalBristles;
}

void StatsManager::setTotalBoni(int totalBoni) {
    this->totalBoni = totalBoni;
}

void StatsManager::setTotalDamages(int totalDamages) {
    this->totalDamages = totalDamages;
}

void StatsManager::setTotalDeaths(int totalDeaths) {
    this->totalDeaths = totalDeaths;
}

void StatsManager::setTotalSheeps(int totalSheeps) {
    this->totalSheeps = totalSheeps;
}

void StatsManager::setTotalMagmaCubes(int totalMagmaCubes) {
    this->totalMagmaCubes = totalMagmaCubes;
}

void StatsManager::setTotalBristles(int totalBristles) {
    this->totalBristles = totalBristles;
}

void StatsManager::reset() {
    totalBoni = 0;
    totalDamages = 0;
    totalDeaths = 0;
    totalSheeps = 0;
    totalMagmaCubes = 0;
    totalBristles = 0;
}
