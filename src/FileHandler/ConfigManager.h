#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "FileHandler.h"
#include "../Json/JsonAccessor.h"

class ConfigManager
{
public:
    static const std::string LANGUAGE_KEY;
    static const std::string DEFAULT_LANGUAGE;

    ConfigManager();
    ~ConfigManager();
    void load(const std::string& configPath);
    const std::string& getLanguage();

private:
    std::string language;
    JsonAccessor accessor;
};

#endif // CONFIGMANAGER_H
