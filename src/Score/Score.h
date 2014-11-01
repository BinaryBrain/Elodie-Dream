#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

class Score {
public:
    Score();
    ~Score();

    int getLevelId();
    int getLevelPoints();
    int getTotalPoints();
    int getBoni();
    int getDamagesTaken();
    int getEnemiesKilled();
    int getSheeps();
    int getMagmaCubes();
    int getBristles();

    void setLevelId(int levelId);
    void setLevelPoints(int levelPoints);
    void setTotalPoints(int totalPoints);
    void setBoni(int boni);
    void setDamagesTaken(int damagesTaken);
    void setEnemiesKilled(int enemiesKilled);
    void setSheeps(int sheeps);
    void setMagmaCubes(int magmaCubes);
    void setBristles(int bristles);

    void reset();

private:
    int levelId = 0;
    int levelPoints = 0;
    int totalPoints = 0;
    int boni = 0;
    int damagesTaken = 0;
    int enemiesKilled = 0;
    int sheeps = 0;
    int magmaCubes = 0;
    int bristles = 0;
};

#endif // SCORE_H_INCLUDED
