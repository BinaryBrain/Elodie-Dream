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
    void addScore(int score);
    void addDamage(int damage);
    void addEnemyKilled();
    void addKilledSheep();
    void addKilledMagmacube();
    void addKilledBristle();
    void computeTotalScore();
    /**
    * Save the current score to the corresponding level in the gameScore if it's better than the one in it.
    * \param level The level whose score must be set as the current score if it's better.
    */
    void saveScore(int level);
    void setLevelScore(int level, int score);
    void resetCurrentScore();
    void resetAllScores();

    Score getScore(int level);
    std::vector<Score> getGameScore();
    Score getCurrentScore();
    Score getLastSavedScore();

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
