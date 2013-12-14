#ifndef SCOREMANAGER_H_INCLUDED
#define SCOREMANAGER_H_INCLUDED

#include <string>
#include <map>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Score.h"

class ScoreManager {
public:
    static ScoreManager* getInstance();
    static void kill();

    void loadScore(int level, int score, int bonus);
    void loadScore(std::vector< int > scores, std::vector< int > bonuses);

    Score getScore(int level);
    Score getCurrentScore();
    Score getLastSavedScore();
    void takeBonus();
    void addScore(int score);
    void addDamage(int damage);
    void addEnemyKilled();
    void addKilledSheep();
    void addKilledMagmacube();
    void addKilledBristle();
    void saveScore(int level);
    void resetCurrentScore();
protected:
private:
    ScoreManager();
    virtual ~ScoreManager();

    static ScoreManager* managerInstance;
    ScoreManager& operator= (ScoreManager const&); // Makes operator= private

    Score currentScore;
    Score lastSavedScore;
    std::map< int, Score > gameScore;
};


#endif // SCOREMANAGER_H_INCLUDED
