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

class ScoreManager {
public:
    static const int BONUS_NODAMAGES;

    static ScoreManager& getInstance();

    void takeBonus();
    void addToLevelPoints(int points);
    void addDamage(int damage);
    void addEnemyKilled(EnemyType type);
    void addKilledSheep();
    void addKilledMagmacube();
    void addKilledBristle();
    void computeTotalPoints();

    /**
    * \brief Save the current score to the gameScore if  the total points are better than the ones in it.
    */
    void saveCurrentScore();
    void setLevelScore(int level, int totalPoints);
    void resetCurrentScore();
    void resetAllScores();

    Score getScore(int level);
    std::vector<Score> getGameScore();

    /**
    * \brief Returns in a vector of vector of int all the values in the Scores. Used to prepare datas for the save.
    * \return A vector of vector of int containing each value of a Score, in the same order as in Score.h.
    */
    std::vector< std::vector<int> > getAllDatas();
    void setAllDatas(std::vector< std::vector<int> > datas);

    Score getCurrentScore();
    Score getLastSavedScore();

    void setLevel(int level);

private:
    ScoreManager();
    virtual ~ScoreManager();

    ScoreManager(const ScoreManager&);
    ScoreManager& operator= (ScoreManager const&); // Makes operator= private

    Score currentScore;
    Score lastSavedScore;
    std::vector<Score> gameScore;

    int nKillsInARow = 0;
};


#endif // SCOREMANAGER_H_INCLUDED
