#ifndef STATSMANAGER_H
#define STATSMANAGER_H

#include <map>
#include <vector>
#include <string>

#include "../Score/Score.h"

class StatsManager
{
public:
    static const std::string DAMAGES_KEY;
    static const std::string DEATHS_KEY;

    static const std::string DAMAGES_LABEL;
    static const std::string DEATHS_LABEL;
    static const std::string BONI_LABEL;
    static const std::string SHEEPS_LABEL;
    static const std::string MAGMACUBES_LABEL;
    static const std::string BRISTLES_LABEL;
    static const std::string RAVENS_LABEL;
    static const std::string METEORITES_LABEL;
    static const std::string ALIENS_LABEL;

    static StatsManager& getInstance();

    int getTotalBoni();
    int getTotalDamages();
    int getTotalDeaths();

    int getTotalSheeps();
    int getTotalMagmaCubes();
    int getTotalBristles();
    int getTotalRavens();
    int getTotalAliens();
    int getTotalMeteorites();
    int getTotalEnemiesKilled();

    const std::map<std::string, int>& getAllDatas();
    std::vector< std::pair<std::string, int> > getLabelledValues();
    std::vector<int> getAllValues();
    std::vector<std::string> getAllKeys();

    void setTotalDamages(int totalDamages);
    void setTotalDeaths(int totalDeaths);

    void setTotalBoni(int totalBoni);
    void setTotalSheeps(int totalSheeps);
    void setTotalMagmaCubes(int totalMagmaCubes);
    void setTotalBristles(int totalBristles);
    void setTotalRavens(int totalRavens);
    void setTotalAliens(int totalAliens);
    void setTotalMeteorites(int totalMeteorites);

    void setAllDatas(const std::map<std::string, int>& datas);

    void reset();

private:
    StatsManager();
    ~StatsManager();

    StatsManager(const StatsManager&);
    StatsManager& operator= (StatsManager const&);

    std::map<std::string, int> datas;
    std::vector< std::pair<std::string, std::string> > keysLabels;
};

#endif // STATSMANAGER_H
