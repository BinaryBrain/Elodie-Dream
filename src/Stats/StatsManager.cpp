#include "StatsManager.h"

const std::string StatsManager::DAMAGES_KEY = "damages";
const std::string StatsManager::DEATHS_KEY = "deaths";

const std::string StatsManager::BONI_LABEL = "Boni collected";
const std::string StatsManager::DAMAGES_LABEL = "Damages taken";
const std::string StatsManager::DEATHS_LABEL = "Deaths";
const std::string StatsManager::SHEEPS_LABEL = "Sheeps killed";
const std::string StatsManager::MAGMACUBES_LABEL = "Magma cubes killed";
const std::string StatsManager::BRISTLES_LABEL = "Bristles killed";
const std::string StatsManager::RAVENS_LABEL = "Ravens killed";
const std::string StatsManager::METEORITES_LABEL = "Meteorites killed";
const std::string StatsManager::ALIENS_LABEL = "Aliens killed";

StatsManager::StatsManager()
{
    keysLabels.push_back({DAMAGES_KEY, DAMAGES_LABEL});
    keysLabels.push_back({DEATHS_KEY, DEATHS_LABEL});
    keysLabels.push_back({Score::BONI_KEY, BONI_LABEL});
    keysLabels.push_back({Score::SHEEPS_KEY, SHEEPS_LABEL});
    keysLabels.push_back({Score::MAGMACUBES_KEY, MAGMACUBES_LABEL});
    keysLabels.push_back({Score::BRISTLES_KEY, BRISTLES_LABEL});
    keysLabels.push_back({Score::RAVENS_KEY, RAVENS_LABEL});
    keysLabels.push_back({Score::METEORITES_KEY, METEORITES_LABEL});
    keysLabels.push_back({Score::ALIENS_KEY, ALIENS_LABEL});
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
    return datas[Score::BONI_KEY];
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
    return datas[Score::SHEEPS_KEY];
}

int StatsManager::getTotalMagmaCubes()
{
    return datas[Score::MAGMACUBES_KEY];
}

int StatsManager::getTotalBristles()
{
    return datas[Score::BRISTLES_KEY];
}

int StatsManager::getTotalRavens()
{
    return datas[Score::RAVENS_KEY];
}

int StatsManager::getTotalAliens()
{
    return datas[Score::ALIENS_KEY];
}

int StatsManager::getTotalMeteorites()
{
    return datas[Score::METEORITES_KEY];
}

int StatsManager::getTotalEnemiesKilled()
{
    return datas[Score::SHEEPS_KEY] + datas[Score::MAGMACUBES_KEY] + datas[Score::BRISTLES_KEY];
}

const std::map<std::string, int>& StatsManager::getAllDatas()
{
    return datas;
}

std::vector< std::pair<std::string, int> > StatsManager::getLabelledValues()
{
    std::vector< std::pair<std::string, int> > labelsValues;
    for (size_t i = 0; i < keysLabels.size(); ++i) {
        labelsValues.push_back(std::make_pair(keysLabels[i].second, datas[keysLabels[i].first]));
    }
    return labelsValues;
}

std::vector<int> StatsManager::getAllValues()
{
    std::vector<int> values;
    for (size_t i = 0; i < keysLabels.size(); ++i) {
        values.push_back(datas[keysLabels[i].first]);
    }
    return values;
}

std::vector<std::string> StatsManager::getAllKeys() {
    std::vector<std::string> keys;
    for (size_t i = 0; i < keysLabels.size(); ++i) {
        keys.push_back(keysLabels[i].first);
    }
    return keys;
}

void StatsManager::setTotalDamages(int totalDamages)
{
    datas[DAMAGES_KEY]  = totalDamages;
}

void StatsManager::setTotalDeaths(int totalDeaths)
{
    datas[DEATHS_KEY] = totalDeaths;
}

void StatsManager::setTotalBoni(int totalBoni)
{
    datas[Score::BONI_KEY] = totalBoni;
}

void StatsManager::setTotalSheeps(int totalSheeps)
{
    datas[Score::SHEEPS_KEY] = totalSheeps;
}

void StatsManager::setTotalMagmaCubes(int totalMagmaCubes)
{
    datas[Score::MAGMACUBES_KEY] = totalMagmaCubes;
}

void StatsManager::setTotalBristles(int totalBristles)
{
    datas[Score::BRISTLES_KEY] = totalBristles;
}

void StatsManager::setTotalRavens(int totalRavens)
{
    datas[Score::RAVENS_KEY] = totalRavens;
}

void StatsManager::setTotalAliens(int totalAliens)
{
    datas[Score::ALIENS_KEY] = totalAliens;
}

void StatsManager::setTotalMeteorites(int totalMeteorites)
{
    datas[Score::METEORITES_KEY] = totalMeteorites;
}

void StatsManager::setAllDatas(const std::map<std::string, int>& datas)
{
    this->datas = datas;
}

void StatsManager::reset()
{
    datas.clear();
    for (size_t i = 0; i < keysLabels.size(); ++i) {
        datas.insert({keysLabels[i].first, 0});
    }
}
