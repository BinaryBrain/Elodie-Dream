#ifndef STATSMANAGER_H
#define STATSMANAGER_H

class StatsManager {
public:
    static StatsManager& getInstance();

    int getTotalBoni();
    int getTotalDamages();
    int getTotalDeaths();

    int getTotalSheeps();
    int getTotalMagmaCubes();
    int getTotalBristles();
    int getTotalEnemiesKilled();

    void setTotalBoni(int totalBoni);
    void setTotalDamages(int totalDamages);
    void setTotalDeaths(int totalDeaths);

    void setTotalSheeps(int totalSheeps);
    void setTotalMagmaCubes(int totalMagmaCubes);
    void setTotalBristles(int totalBristles);

    void reset();

private:
    StatsManager();
    ~StatsManager();

    StatsManager(const StatsManager&);
    StatsManager& operator= (StatsManager const&);

    int totalBoni;
    int totalDamages;
    int totalDeaths;
    int totalSheeps;
    int totalMagmaCubes;
    int totalBristles;
};

#endif // STATSMANAGER_H
