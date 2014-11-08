#include "JsonAccessor.h"

JsonAccessor::JsonAccessor() {

}

JsonAccessor::~JsonAccessor() {
    if (loaded) {
        fclose(pFile);
    }
    delete pFile;
}

rapidjson::Value& JsonAccessor::getAskedObject(std::string key) {
    std::string delimiter = " ";
    std::replace(key.begin(), key.end(), '.', ' ');
    std::istringstream iss(key);
    std::vector<std::string> tokens;
    std::copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter<std::vector<std::string> >(tokens));
    rapidjson::Value* obj = &values;
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        obj = &(*obj)[tokens[i].c_str()];
    }
    return *obj;
}

std::string JsonAccessor::getString(const std::string& key) {
    if (!loaded) {
        std::cerr << "Not loaded yet" << std::endl;
        return "";
    } else {
        const rapidjson::Value& a = getAskedObject(key);
        return a.GetString();
    }
}

int JsonAccessor::getInt(const std::string& key) {
    if (!this->loaded) {
        std::cerr << "Not loaded yet" << std::endl;
        return 0;
    } else {
        const rapidjson::Value& a = getAskedObject(key);
        return a.GetInt();
    }
}

double JsonAccessor::getDouble(const std::string& key) {
    if (!this->loaded) {
        std::cerr << "Not loaded yet" << std::endl;
        return 0;
    } else {
        const rapidjson::Value& a = getAskedObject(key);
        return a.GetDouble();
    }
}

std::vector<int>* JsonAccessor::getIntVector(const std::string& key) {
    if (!this->loaded) {
        std::cerr << "Not loaded yet" << std::endl;
        return 0;
    } else {
        std::vector<int>* vec = new std::vector<int>();
        const rapidjson::Value& a = getAskedObject(key);
        assert(a.IsArray());
        for (rapidjson::SizeType i = 0; i < a.Size(); i++) {
            vec->push_back(a[i].GetInt());
        }

        return vec;
    }
}

std::vector< std::vector<int>* >* JsonAccessor::getInt2DVector(const std::string& key) {
    if (!this->loaded) {
        std::cerr << "Not loaded yet" << std::endl;
        return 0;
    } else {
        std::vector< std::vector<int>* >* vec = new std::vector< std::vector<int>* >();
        const rapidjson::Value& a = getAskedObject(key);
        assert(a.IsArray());
        for (rapidjson::SizeType i = 0; i < a.Size(); ++i) {
            std::vector<int>* row = new std::vector<int>();
            assert(a[i].IsArray());
            for (rapidjson::SizeType j = 0; j < a[i].Size(); ++j) {
                row->push_back(a[i][j].GetInt());
            }
            vec->push_back(row);
        }

        return vec;
    }
}

EntityInfo* JsonAccessor::getEntityInfo() {
    if (!this->loaded) {
        std::cerr << "Not loaded yet" << std::endl;
        return 0;
    } else {
        EntityInfo* entity = new EntityInfo();
        entity->height = this->getInt("height");
        entity->width = this->getInt("width");

        const rapidjson::Value& anim = getAskedObject("anim");
        assert(anim.IsObject());

        for (rapidjson::Value::ConstMemberIterator itr = anim.MemberBegin(); itr != anim.MemberEnd(); ++itr) {
            HitboxInfo hitboxes;
            hitboxes.row = itr->value["row"].GetInt();
            assert(itr->value["hitbox"].IsArray());
            for (rapidjson::SizeType j = 0; j < itr->value["hitbox"].Size(); ++j) {
                sf::FloatRect newHitbox;

                assert(itr->value["hitbox"][j].IsObject());
                newHitbox.left = itr->value["hitbox"][j]["x"].GetInt();
                newHitbox.top = itr->value["hitbox"][j]["y"].GetInt();
                newHitbox.width = itr->value["hitbox"][j]["w"].GetInt();
                newHitbox.height = itr->value["hitbox"][j]["h"].GetInt();

                hitboxes.hitboxes.push_back(newHitbox);
            }

            entity->anim[itr->name.GetString()] = hitboxes;
        }
        return entity;
    }
}

std::string JsonAccessor::getStringWithDefault(const std::string& key, const std::string& defaultValue) {
    if (canTakeElementFrom(key)) {
        return getString(key);
    } else {
        return defaultValue;
        std::cerr << "Error: could not find " << key << " in " << pathToFile << " Using default value." << std::endl;
    }
}

bool JsonAccessor::load(const std::string& pathToFile) {
    if (!this->loaded) {
        this->pathToFile = pathToFile;

        createJsonIfNotExisting(pathToFile);

        pFile = fopen(pathToFile.c_str() , "r");
        rapidjson::FileStream is(pFile);
        if (values.ParseStream<0>(is).HasParseError()) {
            std::cerr << "Parse error when loading json" << std::endl;
            loaded = true; // the file is loaded, even with non-valid json
            return false;
        }
        loaded = true;
        return true;

    } else {
        std::cerr << "Already loaded" << std::endl;
        return false;
    }
}

bool JsonAccessor::canTakeElementFrom(const std::string& key) {
    if (pFile) {
        std::string contents;
        std::fseek(pFile, 0, SEEK_END);
        contents.resize(std::ftell(pFile));
        std::rewind(pFile);
        std::fread(&contents[0], 1, contents.size(), pFile);

        if (contents.find(key) != std::string::npos) {
            return true;
        }
    }
    std::cerr << "Error: could not get item from key \"" << key << "\"." << std::endl;
    return false;
}

bool JsonAccessor::close() {
    if (loaded) {
        fclose(pFile);
        loaded = false;
        return true;
    } else {
        std::cerr << "Nothing to close" << std::endl;
        return false;
    }
}

bool JsonAccessor::createJsonIfNotExisting(const std::string& file) {
    if (FILE * f = fopen(file.c_str(), "r")) {
        fclose(f);
        return true;
    } else {
        if (FILE * f = fopen(file.c_str(), "w")) {
            fputs("{}", f);
            fclose(f);
            return true;
        }
        else {
            std::cerr << "Could not create " << file << std::endl;
            return false;
        }
    }
    return false;
}
