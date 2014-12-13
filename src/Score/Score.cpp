#include "Score.h"

const std::string Score::LEVELID_KEY = "levelid";
const std::string Score::TOTALPOINTS_KEY = "totalpoints";
const std::string Score::BONI_KEY = "boni";
const std::string Score::DAMAGESTAKEN_KEY = "damagestaken";
const std::string Score::ENEMIESKILLED_KEY = "enemieskilled";
const std::string Score::LARGESTKILLINGSPREE_KEY = "largestkillingspree";
const std::string Score::SHEEPS_KEY = "sheeps";
const std::string Score::MAGMACUBES_KEY = "magmacubes";
const std::string Score::BRISTLES_KEY = "bristles";
const std::string Score::CROWS_KEY = "crows";
const std::string Score::REDLIGHTS_KEY = "redlights";
const std::string Score::METEORITES_KEY = "meteorites";
const std::string Score::ALIENS_KEY = "aliens";
const std::string Score::LASERS_KEY = "lasers";


Score::Score()
{
    reset();
}

Score::~Score()
{

}

int Score::getLevelId()
{
    return datas[LEVELID_KEY];
}

int Score::getTotalPoints()
{
    return datas[TOTALPOINTS_KEY];
}

int Score::getBoni()
{
    return datas[BONI_KEY];
}

int Score::getDamagesTaken()
{
    return datas[DAMAGESTAKEN_KEY];
}

int Score::getEnemiesKilled()
{
    return datas[ENEMIESKILLED_KEY];
}

int Score::getLargestKillingSpree()
{
    return datas[LARGESTKILLINGSPREE_KEY];
}

int Score::getSheeps()
{
    return datas[SHEEPS_KEY];
}

int Score::getMagmaCubes()
{
    return datas[MAGMACUBES_KEY];
}

int Score::getBristles()
{
    return datas[BRISTLES_KEY];
}

int Score::getCrows()
{
    return datas[CROWS_KEY];
}

int Score::getRedLights()
{
    return datas[REDLIGHTS_KEY];
}

int Score::getMeteorites()
{
    return datas[METEORITES_KEY];
}

int Score::getAliens()
{
    return datas[ALIENS_KEY];
}

int Score::getLasers()
{
    return datas[LASERS_KEY];
}

const std::map<std::string, int>& Score::getDatas() {
    return datas;
}

bool Score::isRegistered()
{
    return registered;
}

void Score::setLevelId(int levelId)
{
    datas[LEVELID_KEY] = levelId;
}

void Score::setTotalPoints(int totalPoints)
{
    datas[TOTALPOINTS_KEY] = totalPoints;
}

void Score::setBoni(int boni)
{
    datas[BONI_KEY] = boni;
}

void Score::setDamagesTaken(int damagesTaken)
{
    datas[DAMAGESTAKEN_KEY] = damagesTaken;
}

void Score::setEnemiesKilled(int enemiesKilled)
{
    datas[ENEMIESKILLED_KEY] = enemiesKilled;
}

void Score::setLargestKillingSpree(int largestKillingSpree)
{
    datas[LARGESTKILLINGSPREE_KEY] = largestKillingSpree;
}

void Score::setSheeps(int sheeps)
{
    datas[SHEEPS_KEY] = sheeps;
}

void Score::setMagmaCubes(int magmaCubes)
{
    datas[MAGMACUBES_KEY] = magmaCubes;
}

void Score::setBristles(int bristles)
{
    datas[BRISTLES_KEY] = bristles;
}

void Score::setCrows(int crows)
{
    datas[CROWS_KEY] = crows;
}

void Score::setRedLights(int redLights)
{
    datas[REDLIGHTS_KEY] = redLights;
}

void Score::setMeteorites(int meteorites)
{
    datas[METEORITES_KEY] = meteorites;
}

void Score::setAliens(int aliens)
{
    datas[ALIENS_KEY] = aliens;
}

void Score::setLasers(int lasers)
{
    datas[LASERS_KEY] = lasers;
}

void Score::setDatas(const std::map<std::string, int>& datas) {
    this->datas = datas;
}

void Score::setRegistered(bool registered)
{
    this->registered = registered;
}

void Score::reset()
{
    datas.clear();
    datas.insert({LEVELID_KEY, 0});
    datas.insert({TOTALPOINTS_KEY, 0});
    datas.insert({BONI_KEY, 0});
    datas.insert({DAMAGESTAKEN_KEY, 0});
    datas.insert({ENEMIESKILLED_KEY, 0});
    datas.insert({LARGESTKILLINGSPREE_KEY, 0});
    datas.insert({SHEEPS_KEY, 0});
    datas.insert({MAGMACUBES_KEY, 0});
    datas.insert({BRISTLES_KEY, 0});
    datas.insert({CROWS_KEY, 0});
    datas.insert({REDLIGHTS_KEY, 0});
    datas.insert({METEORITES_KEY, 0});
    datas.insert({ALIENS_KEY, 0});
    datas.insert({LASERS_KEY, 0});

    registered = false;
}
