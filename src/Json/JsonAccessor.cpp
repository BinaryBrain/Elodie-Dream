#include "JsonAccessor.h"

JsonAccessor::JsonAccessor() {

}

JsonAccessor::~JsonAccessor() {
    if (buffer) {
        delete buffer;
    }
}

rapidjson::Value& JsonAccessor::getAskedObject(std::string key) {
    std::string delimiter = " ";
    std::replace(key.begin(), key.end(), '.', ' ');
    std::istringstream iss(key);
    std::vector<std::string> tokens;
    std::copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter<std::vector<std::string> >(tokens));
    rapidjson::Value* obj = &doc;
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        obj = &(*obj)[tokens[i].c_str()];
    }
    return *obj;
}

std::string JsonAccessor::getString(const std::string& key) {
    const rapidjson::Value& a = getAskedObject(key);
    return a.GetString();
}

int JsonAccessor::getInt(const std::string& key) {
    const rapidjson::Value& a = getAskedObject(key);
    return a.GetInt();
}

double JsonAccessor::getDouble(const std::string& key) {
    const rapidjson::Value& a = getAskedObject(key);
    return a.GetDouble();
}

std::vector<int>* JsonAccessor::getIntVector(const std::string& key) {
    std::vector<int>* vec = new std::vector<int>();
    const rapidjson::Value& a = getAskedObject(key);
    assert(a.IsArray());
    for (rapidjson::SizeType i = 0; i < a.Size(); i++) {
        vec->push_back(a[i].GetInt());
    }

    return vec;
}

std::vector< std::vector<int>* >* JsonAccessor::getInt2DVector(const std::string& key) {
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

EntityInfo* JsonAccessor::getEntityInfo() {
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

std::string JsonAccessor::getStringWithDefault(const std::string& key, const std::string& defaultValue) {
    if (canTakeElementFrom(key)) {
        return getString(key);
    } else {
        std::cerr << "Error: could not find \"" << key << "\". Using default value." << std::endl;
        return defaultValue;
    }
}

int JsonAccessor::getIntWithDefault(const std::string& key, int defaultValue) {
    if (canTakeElementFrom(key)) {
        return getInt(key);
    } else {
        std::cerr << "Error: could not find \"" << key << "\". Using default value." << std::endl;
        return defaultValue;
    }
}

bool JsonAccessor::loadJsonFrom(const std::string& pathToFile) {
    this->pathToFile = pathToFile;

    FileHandler::createFileIfNotExisting(pathToFile);
    std::string json = FileHandler::getContent(pathToFile);
    return setJson(json);
}

bool JsonAccessor::setJson(const std::string& json) {
    reset();
    buffer = new char [json.size() + 1];
    memcpy(buffer, json.c_str(), json.size() + 1);
    if (doc.ParseInsitu<0>(buffer).HasParseError()) {
        std::cout << "Error: could not parse json:\n" << std::endl;
        reset();
        return false;
    }
    return true;
}

bool JsonAccessor::canTakeElementFrom(const std::string& key) {
    return doc.HasMember(key.c_str());
}

std::string JsonAccessor::getCurrentJson() {
    rapidjson::StringBuffer jsonOutput;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonWriter(jsonOutput);
    doc.Accept(jsonWriter);
    return jsonOutput.GetString();
}

void JsonAccessor::reset() {
    doc.SetObject();
    if (buffer) {
        delete buffer;
        buffer = NULL;
    }
}
