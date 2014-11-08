#include "ConfigManager.h"

ConfigManager::ConfigManager() {

}

ConfigManager::~ConfigManager() {

}

void ConfigManager::load(const std::string& configPath) {
    accessor.load(configPath);
    language = accessor.getString("language");
    accessor.close();
}

const std::string& ConfigManager::getLanguage() {
    return language;
}
