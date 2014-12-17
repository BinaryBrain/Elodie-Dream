#ifndef SCOREMANAGER_H_INCLUDED
#define SCOREMANAGER_H_INCLUDED

#include <string>
#include <map>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Score.h"
#include "../env.h"
#include "../Entity/Enemy/Sheep.h"
#include "../Entity/Enemy/MagmaCube.h"
#include "../Entity/Enemy/Bristle.h"
#include "../Entity/Enemy/Raven.h"
#include "../Entity/Enemy/Alien.h"
#include "../Entity/Enemy/Meteorite.h"
#include "../Entity/Bonus.h"
#include "../Stats/StatsManager.h"

class ScoreManager
{
public:
    static const int BONUS_NODAMAGES;

    static ScoreManager& getInstance();

    void init(const std::vector<int>& envPerSubworld);

    int getKillPoints();
    int getLevelPoints();
    std::string getScoreString();
    const std::vector<int>& getLevelsPerSubworld();

    Score& getScore(const std::vector<int>& level);
    Score& getCurrentScore();
    /**
    * \brief Returns in a vector of map of string and int (representing a vector of all the Scores). Used to prepare datas for the save.
    * \return A vector of vector of int containing each value of a Score, in the same order as in Score.h.
    */
    std::vector< std::map<std::string, int> > getVectMapDatas();
    std::vector< std::vector <std::map<std::string, int> > > get2DVectMapDatas();
    std::vector<std::string> getAllKeys();
    const std::vector< std::vector<Score> >& getGameScore();

    void setRegisteredScoresTo(const std::vector<int>& LDL);
    void setVectMapDatas(const std::vector< std::map<std::string, int> >& datas);
    void setLevel(const std::vector<int>& level);
    void setKillPoints(int points);

    void takeBonus();
    void takeDamage(int damage);
    void addEnemyKilled(EnemyType type);
    void computeTotalPoints();
    void saveCurrentScore();
    void resetCurrentScore();
    void resetAllScores();

private:
    ScoreManager();
    virtual ~ScoreManager();

    ScoreManager(const ScoreManager&);
    ScoreManager& operator= (ScoreManager const&); // Makes operator= private

    std::vector<int> levelsPerSubworld = {0,0};
    Score currentScore;
    std::vector< std::vector<Score> > gameScore;

    StatsManager& statsManager;

    int killPoints = 0;
    int nKillsInARow = 0;
    std::string scoreString = "";
};


#endif // SCOREMANAGER_H_INCLUDED
