#include "JsonAccessor.h"

using std::cerr;
using std::endl;

JsonAccessor::JsonAccessor() {
    //ctor
}

JsonAccessor::~JsonAccessor() {
    if(loaded)
        fclose(pFile);
    delete pFile;
}

rapidjson::Value& JsonAccessor::getAskedObject(string key) {
    using namespace std;
    string delimiter = " ";
    replace(key.begin(), key.end(), '.', ' ');
    istringstream iss(key);
    vector<std::string> tokens;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter<vector<string> >(tokens));
    rapidjson::Value* obj = &values;
    for (size_t i = 0; i < tokens.size(); ++i) {
        obj = &(*obj)[tokens[i].c_str()];
    }
    return *obj;
}

string JsonAccessor::getString(string key) {
    if(!loaded) {
        cerr << "Not loaded yet" << endl;
        return "";
    } else {
        const rapidjson::Value& a = getAskedObject(key);
        return a.GetString();
    }
}

int JsonAccessor::getInt(string key) {
    if(!this->loaded) {
        cerr << "Not loaded yet" << endl;
        return 0;
    } else {
        const rapidjson::Value& a = getAskedObject(key);
        return a.GetInt();
    }
}

double JsonAccessor::getDouble(string key) {
    if(!this->loaded) {
        cerr << "Not loaded yet" << endl;
        return 0;
    } else {
        const rapidjson::Value& a = getAskedObject(key);
        return a.GetDouble();
    }
}

std::vector<int>* JsonAccessor::getIntVector(string key) {
    if(!this->loaded) {
        cerr << "Not loaded yet" << endl;
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

std::vector< std::vector<int>* >* JsonAccessor::getInt2DVector(string key) {
    if(!this->loaded) {
        cerr << "Not loaded yet" << endl;
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
    if(!this->loaded) {
        cerr << "Not loaded yet" << endl;
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

bool JsonAccessor::load(string file) {
    if(!this->loaded) {
        pathToFile = file;

        createJsonIfNotExisting(file);

        pFile = fopen(file.c_str() , "r");
        rapidjson::FileStream is(pFile);
        if(values.ParseStream<0>(is).HasParseError()) {
            cerr << "Parse error when loading json" << endl;
            loaded = true; // the file is loaded, even with non-valid json
            return false;
        }
        loaded = true;
        return true;

    } else {
        cerr << "Already loaded" << endl;
        return false;
    }
}

bool JsonAccessor::canTakeElementFrom(std::string key) {
    if(pFile) {
        std::string contents;
        std::fseek(pFile, 0, SEEK_END);
        contents.resize(std::ftell(pFile));
        std::rewind(pFile);
        std::fread(&contents[0], 1, contents.size(), pFile);

        if (contents.find(key) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool JsonAccessor::close() {
    if(loaded) {
        fclose(pFile);
        return true;
    } else {
        cerr << "Nothing to close" << endl;
        return false;
    }
}

bool JsonAccessor::createJsonIfNotExisting(std::string file) {
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
            cerr << "Could not create " << file << endl;
            return false;
        }
    }
    return false;
}
