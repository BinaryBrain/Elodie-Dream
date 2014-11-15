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
#include "../Entity/Bonus.h"
#include "../Stats/StatsManager.h"

class ScoreManager
{
public:
    static const int BONUS_NODAMAGES;

    static ScoreManager& getInstance();
    int getKillPoints();
    int getLevelPoints();
    std::string getScoreString();
    Score& getScore(int level);
    Score& getCurrentScore();
    std::vector<Score>& getGameScore();
    /**
    * \brief Returns in a vector of vector of int: all the values in the Scores. Used to prepare datas for the save.
    * \return A vector of vector of int containing each value of a Score, in the same order as in Score.h.
    */
    std::vector< std::vector<int> > getAllDatas();

    /**
    * \brief Save the current score to the gameScore if  the total points are better than the ones in it.
    */
    void setAllDatas(std::vector< std::vector<int> > datas);
    void setLevel(int level);
    void setKillPoints(int points);
    void setLevelScore(int level, int totalPoints);

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

    Score currentScore;
    std::vector<Score> gameScore;

    StatsManager& statsManager;

    int killPoints = 0;
    int nKillsInARow = 0;
    std::string scoreString = "";
};


#endif // SCOREMANAGER_H_INCLUDED
