#ifndef STATSMANAGER_H
#define STATSMANAGER_H

class StatsManager {
public:
    StatsManager();
    ~StatsManager();

    int getTotalDeaths();
    int getTotalSheeps();
    int getTotalMagmaCubes();
    int getTotalBristles();

private:
    int totalDeaths;
    int totalSheeps;
    int totalMagmaCubes;
    int totalBristles;
};

#endif // STATSMANAGER_H
