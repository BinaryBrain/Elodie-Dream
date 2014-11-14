#include "ScoreManager.h"

const int ScoreManager::BONUS_NODAMAGES = 500;

ScoreManager::ScoreManager() : statsManager(StatsManager::getInstance()) {
    for (size_t i = 0; i < NUMLEVELS; ++i) {
        Score score;
        gameScore.push_back(score);
    }
}

ScoreManager::~ScoreManager() {
}

// Gets the instance of the entityManger
ScoreManager& ScoreManager::getInstance() {
    static ScoreManager instance;
    return instance;
}

int ScoreManager::getKillPoints() {
    return killPoints;
}

int ScoreManager::getLevelPoints() {
    return killPoints + currentScore.getBoni() * Bonus::POINTS - currentScore.getDamagesTaken();
}

std::string ScoreManager::getScoreString() {
    return scoreString;
}

Score& ScoreManager::getScore(int level) {
    return gameScore[level];
}

Score& ScoreManager::getCurrentScore() {
    return currentScore;
}

std::vector<Score>& ScoreManager::getGameScore() {
    return gameScore;
}

std::vector< std::vector<int> > ScoreManager::getAllDatas() {
    std::vector< std::vector<int> > datas;

    for (size_t i = 0; i < gameScore.size(); ++i) {
        std::vector<int> score;
        score.push_back(gameScore[i].getLevelId());
        score.push_back(gameScore[i].getTotalPoints());
        score.push_back(gameScore[i].getBoni());
        score.push_back(gameScore[i].getDamagesTaken());
        score.push_back(gameScore[i].getEnemiesKilled());
        score.push_back(gameScore[i].getLargestKillingSpree());
        score.push_back(gameScore[i].getSheeps());
        score.push_back(gameScore[i].getMagmaCubes());
        score.push_back(gameScore[i].getBristles());
        datas.push_back(score);
    }

    return datas;
}

void ScoreManager::setAllDatas(std::vector< std::vector<int> > datas) {
    for (size_t i = 0; i < datas.size(); ++i) {
        gameScore[i].setLevelId(datas[i][0]);
        gameScore[i].setTotalPoints(datas[i][1]);
        gameScore[i].setBoni(datas[i][2]);
        gameScore[i].setDamagesTaken(datas[i][3]);
        gameScore[i].setEnemiesKilled(datas[i][4]);
        gameScore[i].setLargestKillingSpree(datas[i][5]);
        gameScore[i].setSheeps(datas[i][6]);
        gameScore[i].setMagmaCubes(datas[i][7]);
        gameScore[i].setBristles(datas[i][8]);
    }
}

void ScoreManager::setLevel(int level) {
    currentScore.setLevelId(level);
}

void ScoreManager::setLevelScore(int level, int totalPoints) {
    gameScore[level].setTotalPoints(totalPoints);
}

void ScoreManager::takeBonus() {
    currentScore.setBoni(currentScore.getBoni() + 1);
    statsManager.setTotalBoni(statsManager.getTotalBoni() + 1);
}

void ScoreManager::takeDamage(int damage) {
    currentScore.setDamagesTaken(currentScore.getDamagesTaken() + damage);
    if (damage > 0) {
        nKillsInARow = 0;
    }
}

void ScoreManager::addEnemyKilled(EnemyType type) {
    ++nKillsInARow;
    if (nKillsInARow > currentScore.getLargestKillingSpree()) {
        currentScore.setLargestKillingSpree(nKillsInARow);
    }
    currentScore.setEnemiesKilled(currentScore.getEnemiesKilled() + 1);

    switch (type) {
        case EnemyType::SHEEP:
            killPoints += Sheep::DAMAGE * nKillsInARow;
            currentScore.setSheeps(currentScore.getSheeps() + 1);
            statsManager.setTotalSheeps(statsManager.getTotalSheeps() + 1);
            break;
        case EnemyType::MAGMACUBE:
            killPoints += MagmaCube::DAMAGE * nKillsInARow;
            currentScore.setMagmaCubes(currentScore.getMagmaCubes() + 1);
            statsManager.setTotalMagmaCubes(statsManager.getTotalMagmaCubes() + 1);
            break;
        case EnemyType::BRISTLE:
            killPoints += Bristle::DAMAGE * nKillsInARow;
            currentScore.setBristles(currentScore.getBristles() + 1);
            statsManager.setTotalBristles(statsManager.getTotalBristles() + 1);
            break;
        default:
            break;
    }
}

void ScoreManager::computeTotalPoints() {
    int totalPoints = getLevelPoints();
    if (currentScore.getDamagesTaken() == 0) {
        totalPoints += BONUS_NODAMAGES;
    }
    currentScore.setTotalPoints(totalPoints);
}

void ScoreManager::saveCurrentScore() {
    int level = currentScore.getLevelId();
    bool registered = gameScore[level].isRegistered();
    bool betterScore = gameScore[level].getTotalPoints() < currentScore.getTotalPoints();

    if (!registered || betterScore) {
        gameScore[level] = currentScore;
        gameScore[level].setRegistered(true);
        scoreString = "(new record! :3)";
    } else {
        scoreString = "(best score: " + Utils::itos(gameScore[level].getTotalPoints()) + ")";
    }
}

void ScoreManager::resetCurrentScore() {
    killPoints = 0;
    nKillsInARow = 0;
    scoreString = "";
    currentScore.reset();
}

void ScoreManager::resetAllScores() {
    for (size_t i = 0; i < NUMLEVELS; ++i) {
        gameScore[i].reset();
    }
}
