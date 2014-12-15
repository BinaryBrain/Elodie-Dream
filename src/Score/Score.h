#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include "../env.h"

class Score
{
public:
    static const std::string TOTALPOINTS_KEY;
    static const std::string BONI_KEY;
    static const std::string DAMAGESTAKEN_KEY;
    static const std::string ENEMIESKILLED_KEY;
    static const std::string LARGESTKILLINGSPREE_KEY;
    static const std::string SHEEPS_KEY;
    static const std::string MAGMACUBES_KEY;
    static const std::string BRISTLES_KEY;
    static const std::string RAVENS_KEY;
    static const std::string METEORITES_KEY;
    static const std::string ALIENS_KEY;

    Score();
    ~Score();

    const std::vector<int>& getLevelId();
    int getTotalPoints();
    int getBoni();
    int getDamagesTaken();
    int getEnemiesKilled();
    int getLargestKillingSpree();
    int getSheeps();
    int getMagmaCubes();
    int getBristles();
    int getRavens();
    int getMeteorites();
    int getAliens();
    const std::map<std::string, int>& getDatas();
    bool isRegistered();

    void setLevelId(const std::vector<int>& levelId);
    void setTotalPoints(int totalPoints);
    void setBoni(int boni);
    void setDamagesTaken(int damagesTaken);
    void setEnemiesKilled(int enemiesKilled);
    void setLargestKillingSpree(int largestKillingSpree);
    void setSheeps(int sheeps);
    void setMagmaCubes(int magmaCubes);
    void setBristles(int bristles);
    void setRavens(int ravens);
    void setMeteorites(int meteorites);
    void setAliens(int aliens);
    void setDatas(const std::map<std::string, int>& datas);
    void setRegistered(bool firstTimeSet);

    void reset();

private:
    std::map<std::string, int> datas;
    std::vector<int> levelId;
    bool registered;
};

#endif // SCORE_H_INCLUDED
