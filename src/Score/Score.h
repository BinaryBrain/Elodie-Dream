#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

class Score
{
public:
    Score();
    ~Score();

    int getLevelId();
    int getTotalPoints();
    int getBoni();
    int getDamagesTaken();
    int getEnemiesKilled();
    int getLargestKillingSpree();
    int getSheeps();
    int getMagmaCubes();
    int getBristles();
    bool isRegistered();

    void setLevelId(int levelId);
    void setTotalPoints(int totalPoints);
    void setBoni(int boni);
    void setDamagesTaken(int damagesTaken);
    void setEnemiesKilled(int enemiesKilled);
    void setLargestKillingSpree(int largestKillingSpree);
    void setSheeps(int sheeps);
    void setMagmaCubes(int magmaCubes);
    void setBristles(int bristles);
    void setRegistered(bool firstTimeSet);

    void reset();

private:
    int levelId;
    int totalPoints;
    int boni;
    int damagesTaken;
    int enemiesKilled;
    int largestKillingSpree;
    int sheeps;
    int magmaCubes;
    int bristles;

    bool registered;
};

#endif // SCORE_H_INCLUDED
