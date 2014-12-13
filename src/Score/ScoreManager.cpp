#include "ScoreManager.h"

const int ScoreManager::BONUS_NODAMAGES = 500;

ScoreManager::ScoreManager() : statsManager(StatsManager::getInstance())
{
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

void ScoreManager::init(const std::vector<int>& envPerSubworld) {
    this->envPerSubworld = envPerSubworld;
    totalWords = 0;

    for (size_t i = 0; i < envPerSubworld.size(); ++i)
    {
        std::vector<Score> subWorld;
        for (int j = 0; j < envPerSubworld[i]; ++j)
        {
            Score score;
            subWorld.push_back(score);
            ++totalWords;
        }
        gameScore.push_back(subWorld);
    }
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

Score& ScoreManager::getScore(const std::vector<int>& level)
{
    return gameScore[level[0]][level[1]];
}

Score& ScoreManager::getCurrentScore()
{
    return currentScore;
}

std::vector< std::map<std::string, int> > ScoreManager::getAllDatas()
{
    std::vector< std::map<std::string, int> > datas;

    for (size_t i = 0; i < envPerSubworld.size(); ++i)
    {
        for (int j = 0; j < envPerSubworld[i]; ++j)
        {
            datas.push_back(gameScore[i][j].getDatas());
        }
    }

    return datas;
}

std::vector<std::string> ScoreManager::getAllKeys()
{
    std::vector<std::string> keys;
    keys.push_back(Score::TOTALPOINTS_KEY);
    keys.push_back(Score::BONI_KEY);
    keys.push_back(Score::DAMAGESTAKEN_KEY);
    keys.push_back(Score::ENEMIESKILLED_KEY);
    keys.push_back(Score::LARGESTKILLINGSPREE_KEY);
    keys.push_back(Score::SHEEPS_KEY);
    keys.push_back(Score::MAGMACUBES_KEY);
    keys.push_back(Score::BRISTLES_KEY);
    keys.push_back(Score::CROWS_KEY);
    keys.push_back(Score::REDLIGHTS_KEY);
    keys.push_back(Score::METEORITES_KEY);
    keys.push_back(Score::ALIENS_KEY);
    keys.push_back(Score::LASERS_KEY);
    return keys;
}

void ScoreManager::setAllDatas(const std::vector< std::map<std::string, int> >& datas)
{
    int nWorldsBefore = 0;
    for (size_t i = 0; i < envPerSubworld.size(); ++i)
    {
        for (int j = 0; j < envPerSubworld[i]; ++j)
        {
            (gameScore[i][j]).setDatas(datas[nWorldsBefore]);
            ++nWorldsBefore;
        }
    }
}

void ScoreManager::setLevel(const std::vector<int>& level)
{
    currentScore.setLevelId(level);
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
    // todo other cases
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
    std::vector<int> level = currentScore.getLevelId();
    bool registered = (gameScore[level[0]][level[1]]).isRegistered();
    bool betterScore = (gameScore[level[0]][level[1]]).getTotalPoints() < currentScore.getTotalPoints();

    if (!registered || betterScore)
    {
        gameScore[level[0]][level[1]] = currentScore;
        (gameScore[level[0]][level[1]]).setRegistered(true);
        scoreString = "(new record! :3)";
    }
    else
    {
        scoreString = "(best score: " + Utils::itos((gameScore[level[0]][level[1]]).getTotalPoints()) + ")";
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
    for (size_t i = 0; i < envPerSubworld.size(); ++i)
    {
        for (int j = 0; j < envPerSubworld[i]; ++j)
        {
            gameScore[i][j].reset();
        }
    }
}
