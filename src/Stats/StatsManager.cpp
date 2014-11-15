#include "StatsManager.h"

const std::string StatsManager::BONI_KEY = "boni";
const std::string StatsManager::DAMAGES_KEY = "damages";
const std::string StatsManager::DEATHS_KEY = "deaths";
const std::string StatsManager::SHEEPS_KEY = "sheeps";
const std::string StatsManager::MAGMACUBE_KEY = "magmaCubes";
const std::string StatsManager::BRISTLES_KEY = "bristles";

const std::string StatsManager::BONI_LABEL = "Boni collected";
const std::string StatsManager::DAMAGES_LABEL = "Damages taken";
const std::string StatsManager::DEATHS_LABEL = "Deaths";
const std::string StatsManager::SHEEPS_LABEL = "Sheeps killed";
const std::string StatsManager::MAGMACUBE_LABEL = "Magma cubes killed";
const std::string StatsManager::BRISTLES_LABEL = "Bristles killed";

StatsManager::StatsManager()
{
    reset();
}

StatsManager::~StatsManager()
{

}

StatsManager& StatsManager::getInstance()
{
    static StatsManager instance;
    return instance;
}

int StatsManager::getTotalBoni()
{
    return datas[BONI_KEY];
}

int StatsManager::getTotalDamages()
{
    return datas[DAMAGES_KEY];
}

int StatsManager::getTotalDeaths()
{
    return datas[DEATHS_KEY];
}

int StatsManager::getTotalSheeps()
{
    return datas[SHEEPS_KEY];
}

int StatsManager::getTotalMagmaCubes()
{
    return datas[MAGMACUBE_KEY];
}

int StatsManager::getTotalBristles()
{
    return datas[BRISTLES_KEY];
}

int StatsManager::getTotalEnemiesKilled()
{
    return datas[SHEEPS_KEY] + datas[MAGMACUBE_KEY] + datas[BRISTLES_KEY];
}

std::map<std::string, int>& StatsManager::getAllDatas()
{
    return datas;
}

std::vector< std::pair<std::string, int> > StatsManager::getLabelledValues()
{
    std::vector< std::pair<std::string, int> > namesValues;
    namesValues.push_back(std::make_pair(BONI_LABEL, datas[BONI_KEY]));
    namesValues.push_back(std::make_pair(DAMAGES_LABEL, datas[DAMAGES_KEY]));
    namesValues.push_back(std::make_pair(DEATHS_LABEL, datas[DEATHS_KEY]));
    namesValues.push_back(std::make_pair(SHEEPS_LABEL, datas[SHEEPS_KEY]));
    namesValues.push_back(std::make_pair(MAGMACUBE_LABEL, datas[MAGMACUBE_KEY]));
    namesValues.push_back(std::make_pair(BRISTLES_LABEL, datas[BRISTLES_KEY]));
    return namesValues;
}

std::vector<int> StatsManager::getAllValues()
{
    std::vector<int> values;
    values.push_back(datas[BONI_KEY]);
    values.push_back(datas[DAMAGES_KEY]);
    values.push_back(datas[DEATHS_KEY]);
    values.push_back(datas[SHEEPS_KEY]);
    values.push_back(datas[MAGMACUBE_KEY]);
    values.push_back(datas[BRISTLES_KEY]);
    return values;
}

void StatsManager::setTotalBoni(int totalBoni)
{
    datas[BONI_KEY] = totalBoni;
}

void StatsManager::setTotalDamages(int totalDamages)
{
    datas[DAMAGES_KEY]  = totalDamages;
}

void StatsManager::setTotalDeaths(int totalDeaths)
{
    datas[DEATHS_KEY] = totalDeaths;
}

void StatsManager::setTotalSheeps(int totalSheeps)
{
    datas[SHEEPS_KEY] = totalSheeps;
}

void StatsManager::setTotalMagmaCubes(int totalMagmaCubes)
{
    datas[MAGMACUBE_KEY] = totalMagmaCubes;
}

void StatsManager::setTotalBristles(int totalBristles)
{
    datas[BRISTLES_KEY] = totalBristles;
}

void StatsManager::setAllValues(std::vector<int>& values)
{
    reset();
    datas[BONI_KEY] = values[0];
    datas[DAMAGES_KEY] = values[1];
    datas[DEATHS_KEY] = values[2];
    datas[SHEEPS_KEY] = values[3];
    datas[MAGMACUBE_KEY] = values[4];
    datas[BRISTLES_KEY] = values[5];
}

void StatsManager::reset()
{
    datas.clear();
    datas.insert({BONI_KEY, 0});
    datas.insert({DAMAGES_KEY, 0});
    datas.insert({DEATHS_KEY, 0});
    datas.insert({SHEEPS_KEY, 0});
    datas.insert({MAGMACUBE_KEY, 0});
    datas.insert({BRISTLES_KEY, 0});
}
