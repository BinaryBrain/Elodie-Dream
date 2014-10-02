#ifndef SCOREMANAGER_H_INCLUDED
#define SCOREMANAGER_H_INCLUDED

#include <string>
#include <map>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Score.h"
#include "../const.h"

class ScoreManager {
public:
    static ScoreManager* getInstance();
    static void kill();

    void takeBonus();
    void addKillPoints(int points);
    void addDamage(int damage);
    void addEnemyKilled();
    void addKilledSheep();
    void addKilledMagmacube();
    void addKilledBristle();
    void computeTotalPoints();
    /**
    * Save the current score to the gameScore if  the total points are better than the ones in it.
    */
    void saveCurrentScore();
    void setLevelScore(int level, int totalPoints);
    void resetCurrentScore();
    void resetAllScores();

    Score getScore(int level);
    std::vector<Score> getGameScore();
    Score getCurrentScore();
    Score getLastSavedScore();

    void setLevel(int level);

protected:
private:
    ScoreManager();
    virtual ~ScoreManager();

    static ScoreManager* managerInstance;
    ScoreManager& operator= (ScoreManager const&); // Makes operator= private

    Score currentScore;
    Score lastSavedScore;
    std::vector<Score> gameScore;
};


#endif // SCOREMANAGER_H_INCLUDED
