#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include "../env.h"

class Score
{
public:
    static const std::string LEVELID_KEY;
    static const std::string TOTALPOINTS_KEY;
    static const std::string BONI_KEY;
    static const std::string DAMAGESTAKEN_KEY;
    static const std::string ENEMIESKILLED_KEY;
    static const std::string LARGESTKILLINGSPREE_KEY;
    static const std::string SHEEPS_KEY;
    static const std::string MAGMACUBES_KEY;
    static const std::string BRISTLES_KEY;

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
    const std::map<std::string, int>& getDatas();
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
    void setDatas(const std::map<std::string, int>& datas);
    void setRegistered(bool firstTimeSet);

    void reset();

private:
    std::map<std::string, int> datas;
    bool registered;
};

#endif // SCORE_H_INCLUDED
