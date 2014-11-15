#include "ConfigManager.h"

const std::string ConfigManager::LANGUAGE_KEY = "language";
const std::string ConfigManager::DEFAULT_LANGUAGE = "EN";

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager()
{

}

void ConfigManager::load(const std::string& configPath)
{
    accessor.loadJsonFrom(configPath);
    language = accessor.getStringWithDefault(LANGUAGE_KEY, DEFAULT_LANGUAGE);
}

const std::string& ConfigManager::getLanguage()
{
    return language;
}
