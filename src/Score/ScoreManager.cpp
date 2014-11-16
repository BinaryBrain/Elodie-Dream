#include "ScoreManager.h"

const int ScoreManager::BONUS_NODAMAGES = 500;

ScoreManager::ScoreManager() : statsManager(StatsManager::getInstance())
{
    for (size_t i = 0; i < NUMLEVELS; ++i)
    {
        Score score;
        gameScore.push_back(score);
    }
}

ScoreManager::~ScoreManager()
{
}

// Gets the instance of the entityManger
ScoreManager& ScoreManager::getInstance()
{
    static ScoreManager instance;
    return instance;
}

int ScoreManager::getKillPoints()
{
    return killPoints;
}

int ScoreManager::getLevelPoints()
{
    return killPoints + currentScore.getBoni() * Bonus::POINTS - currentScore.getDamagesTaken();
}

std::string ScoreManager::getScoreString()
{
    return scoreString;
}

Score& ScoreManager::getScore(int level)
{
    return gameScore[level];
}

Score& ScoreManager::getCurrentScore()
{
    return currentScore;
}

std::vector<Score>& ScoreManager::getGameScore()
{
    return gameScore;
}

std::vector< std::map<std::string, int> > ScoreManager::getAllDatas()
{
    std::vector< std::map<std::string, int> > datas;

    for (size_t i = 0; i < gameScore.size(); ++i)
    {
        datas.push_back(gameScore[i].getDatas());
    }

    return datas;
}

std::vector<std::string> ScoreManager::getAllKeys() {
    std::vector<std::string> keys;
    keys.push_back(Score::LEVELID_KEY);
    keys.push_back(Score::TOTALPOINTS_KEY);
    keys.push_back(Score::BONI_KEY);
    keys.push_back(Score::DAMAGESTAKEN_KEY);
    keys.push_back(Score::ENEMIESKILLED_KEY);
    keys.push_back(Score::LARGESTKILLINGSPREE_KEY);
    keys.push_back(Score::SHEEPS_KEY);
    keys.push_back(Score::MAGMACUBES_KEY);
    keys.push_back(Score::BRISTLES_KEY);
    return keys;
}

void ScoreManager::setAllDatas(const std::vector< std::map<std::string, int> >& datas)
{
    for (size_t i = 0; i < datas.size(); ++i)
    {
        gameScore[i].setDatas(datas[i]);
    }
}

void ScoreManager::setLevel(int level)
{
    currentScore.setLevelId(level);
}

void ScoreManager::setLevelScore(int level, int totalPoints)
{
    gameScore[level].setTotalPoints(totalPoints);
}

void ScoreManager::takeBonus()
{
    currentScore.setBoni(currentScore.getBoni() + 1);
    statsManager.setTotalBoni(statsManager.getTotalBoni() + 1);
}

void ScoreManager::takeDamage(int damage)
{
    currentScore.setDamagesTaken(currentScore.getDamagesTaken() + damage);
    if (damage > 0)
    {
        nKillsInARow = 0;
    }
    statsManager.setTotalDamages(statsManager.getTotalDamages() + damage);
}

void ScoreManager::addEnemyKilled(EnemyType type)
{
    ++nKillsInARow;
    if (nKillsInARow > currentScore.getLargestKillingSpree())
    {
        currentScore.setLargestKillingSpree(nKillsInARow);
    }
    currentScore.setEnemiesKilled(currentScore.getEnemiesKilled() + 1);

    switch (type)
    {
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

void ScoreManager::computeTotalPoints()
{
    int totalPoints = getLevelPoints();
    if (currentScore.getDamagesTaken() == 0)
    {
        totalPoints += BONUS_NODAMAGES;
    }
    currentScore.setTotalPoints(totalPoints);
}

void ScoreManager::saveCurrentScore()
{
    int level = currentScore.getLevelId();
    bool registered = gameScore[level].isRegistered();
    bool betterScore = gameScore[level].getTotalPoints() < currentScore.getTotalPoints();

    if (!registered || betterScore)
    {
        gameScore[level] = currentScore;
        gameScore[level].setRegistered(true);
        scoreString = "(new record! :3)";
    }
    else
    {
        scoreString = "(best score: " + Utils::itos(gameScore[level].getTotalPoints()) + ")";
    }
}

void ScoreManager::resetCurrentScore()
{
    killPoints = 0;
    nKillsInARow = 0;
    scoreString = "";
    currentScore.reset();
}

void ScoreManager::resetAllScores()
{
    for (size_t i = 0; i < NUMLEVELS; ++i)
    {
        gameScore[i].reset();
    }
}
