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

void ScoreManager::init(const std::vector<int>& levelsPerSubworld) {
    this->levelsPerSubworld = levelsPerSubworld;

    for (size_t i = 0; i < levelsPerSubworld.size(); ++i)
    {
        std::vector<Score> subWorld;
        for (int j = 0; j < levelsPerSubworld[i]; ++j)
        {
            Score score;
            subWorld.push_back(score);
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

const std::vector<int>& ScoreManager::getLevelsPerSubworld()
{
    return levelsPerSubworld;
}

Score& ScoreManager::getScore(const std::vector<int>& level)
{
    return gameScore[level[0]][level[1]];
}

Score& ScoreManager::getCurrentScore()
{
    return currentScore;
}

std::vector< std::map<std::string, int> > ScoreManager::getVectMapDatas()
{
    std::vector< std::map<std::string, int> > datas;

    for (size_t i = 0; i < levelsPerSubworld.size(); ++i)
    {
        for (int j = 0; j < levelsPerSubworld[i]; ++j)
        {
            datas.push_back(gameScore[i][j].getDatas());
        }
    }

    return datas;
}

std::vector< std::vector <std::map<std::string, int> > > ScoreManager::get2DVectMapDatas()
{
    std::vector< std::vector <std::map<std::string, int> > > datas;

    for (size_t i = 0; i < levelsPerSubworld.size(); ++i)
    {
        std::vector< std::map <std::string, int> > subworldScores;
        for (int j = 0; j < levelsPerSubworld[i]; ++j)
        {
            subworldScores.push_back(gameScore[i][j].getDatas());
        }
        datas.push_back(subworldScores);
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
    keys.push_back(Score::RAVENS_KEY);
    keys.push_back(Score::METEORITES_KEY);
    keys.push_back(Score::ALIENS_KEY);
    return keys;
}

const std::vector< std::vector<Score> >& ScoreManager::getGameScore() {
    return gameScore;
}

void ScoreManager::setRegisteredScoresTo(const std::vector<int>& LDL) {
    int lastSubworld = LDL[0];
    int lastDiscoveredLevel = LDL[1];
    for (int i = 0; i <= lastSubworld; ++i)
    {
        int nLevels = levelsPerSubworld[i];
        for (int j = 0; j < nLevels; ++j)
        {
            if (i != lastSubworld || (i == lastSubworld && j < lastDiscoveredLevel))
            {
                gameScore[i][j].setRegistered(true);
            }
        }
    }
}

void ScoreManager::setVectMapDatas(const std::vector< std::map<std::string, int> >& datas)
{
    int nWorldsBefore = 0;
    for (size_t i = 0; i < levelsPerSubworld.size(); ++i)
    {
        for (int j = 0; j < levelsPerSubworld[i]; ++j)
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
    case EnemyType::RAVEN:
        killPoints += Raven::DAMAGE * nKillsInARow;
        currentScore.setRavens(currentScore.getRavens() + 1);
        statsManager.setTotalRavens(statsManager.getTotalRavens() + 1);
        break;
    case EnemyType::ALIEN:
        killPoints += Alien::DAMAGE * nKillsInARow;
        currentScore.setAliens(currentScore.getAliens() + 1);
        statsManager.setTotalAliens(statsManager.getTotalAliens() + 1);
        break;
    case EnemyType::METEORITE:
        killPoints += Meteorite::DAMAGE * nKillsInARow;
        currentScore.setMeteorites(currentScore.getMeteorites() + 1);
        statsManager.setTotalMeteorites(statsManager.getTotalMeteorites() + 1);
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
    for (size_t i = 0; i < levelsPerSubworld.size(); ++i)
    {
        for (int j = 0; j < levelsPerSubworld[i]; ++j)
        {
            gameScore[i][j].reset();
        }
    }
}
