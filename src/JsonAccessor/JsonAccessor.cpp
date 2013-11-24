#include "JsonAccessor.h"

using std::cerr;
using std::endl;

JsonAccessor::JsonAccessor() {
    //ctor
}

JsonAccessor::~JsonAccessor() {
    delete pFile;
}

rapidjson::Value& JsonAccessor::getAskedObject(string key) {
    string delimiter = ".";
    size_t pos = 0;
    std::string subKey;
    rapidjson::Value obj;
    bool init = false;
    if (key.find(delimiter) == string::npos)
        return values[key.c_str()];

    while ((pos = key.find(delimiter)) != string::npos) {
        subKey = key.substr(0, pos);
        key.erase(0, pos + delimiter.length());
        if (!init) {
            assert(values[subKey.c_str()].IsObject());
            obj = values[subKey.c_str()];
            init = true;
        } else {
            assert(obj[subKey.c_str()].IsObject());
            obj = obj[subKey.c_str()];
        }
    }

    //Very bad in terms of performance
    loaded = false;
    load(pathToFile);

    return obj[key.c_str()];
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

bool JsonAccessor::load(string file) {
    if(!this->loaded) {
        pathToFile = file;
        pFile = fopen (file.c_str() , "r");
        rapidjson::FileStream is(pFile);
        if(values.ParseStream<0>(is).HasParseError()) {
            cerr << "Parse Error" << endl;
        }
        loaded = true;
        return true;
    } else {
        cerr << "Already loaded" << endl;
        return false;
    }
}
