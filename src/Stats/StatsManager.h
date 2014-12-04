#ifndef STATSMANAGER_H
#define STATSMANAGER_H

#include <map>
#include <vector>
#include <string>

class StatsManager
{
public:
    static const std::string BONI_KEY;
    static const std::string DAMAGES_KEY;
    static const std::string DEATHS_KEY;
    static const std::string SHEEPS_KEY;
    static const std::string MAGMACUBE_KEY;
    static const std::string BRISTLES_KEY;

    static const std::string BONI_LABEL;
    static const std::string DAMAGES_LABEL;
    static const std::string DEATHS_LABEL;
    static const std::string SHEEPS_LABEL;
    static const std::string MAGMACUBE_LABEL;
    static const std::string BRISTLES_LABEL;

    static StatsManager& getInstance();

    int getTotalBoni();
    int getTotalDamages();
    int getTotalDeaths();

    int getTotalSheeps();
    int getTotalMagmaCubes();
    int getTotalBristles();
    int getTotalEnemiesKilled();

    const std::map<std::string, int>& getAllDatas();
    std::vector< std::pair<std::string, int> > getLabelledValues();
    std::vector<int> getAllValues();
    std::vector<std::string> getAllKeys();

    void setTotalBoni(int totalBoni);
    void setTotalDamages(int totalDamages);
    void setTotalDeaths(int totalDeaths);

    void setTotalSheeps(int totalSheeps);
    void setTotalMagmaCubes(int totalMagmaCubes);
    void setTotalBristles(int totalBristles);

    void setAllDatas(const std::map<std::string, int>& datas);

    void reset();

private:
    StatsManager();
    ~StatsManager();

    StatsManager(const StatsManager&);
    StatsManager& operator= (StatsManager const&);

    std::map<std::string, int> datas;
};

#endif // STATSMANAGER_H
