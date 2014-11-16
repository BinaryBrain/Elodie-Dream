#include "JsonStringifier.h"


JsonStringifier::JsonStringifier()
{
    reset();
}

JsonStringifier::~JsonStringifier()
{

}

void JsonStringifier::add(std::string key, int i)
{
    doc.AddMember(key.c_str(), i, doc.GetAllocator());
}

void JsonStringifier::add(std::string key, double d)
{
    doc.AddMember(key.c_str(), d, doc.GetAllocator());
}

void JsonStringifier::add(std::string key, std::string s)
{
    doc.AddMember(key.c_str(), s.c_str(), doc.GetAllocator());
}

void JsonStringifier::add(std::string key, std::vector<int> v)
{
    rapidjson::Value arr;
    arr.SetArray();

    for (size_t i = 0; i < v.size(); ++i)
    {
        arr.PushBack(v[i], doc.GetAllocator());
    }
    doc.AddMember(key.c_str(), arr, doc.GetAllocator());
}

void JsonStringifier::add(std::string key, std::vector< std::vector<int> > v2d)
{
    rapidjson::Value arr;
    rapidjson::Value arr2;

    arr.SetArray();

    for (size_t i = 0; i < v2d.size(); ++i)
    {
        arr2.SetArray();

        for (size_t j = 0; j < v2d[i].size(); ++j)
        {
            arr2.PushBack(v2d[i][j], doc.GetAllocator());
        }
        arr.PushBack(arr2, doc.GetAllocator());
    }
    doc.AddMember(key.c_str(), arr, doc.GetAllocator());
}

void JsonStringifier::add(const std::string& key, const std::map<std::string, int>& m)
{
    rapidjson::Value v;
    v.SetObject();
    doc.AddMember(key.c_str(), v, doc.GetAllocator());
    rapidjson::Value& o = doc[key.c_str()];

    for (auto it = m.begin(); it != m.end(); ++it)
    {
        v.SetInt(it->second);
        o.AddMember((it->first).c_str(), v, doc.GetAllocator());
    }
}

void JsonStringifier::add(const std::string& key, const std::vector< std::map<std::string, int> >& maps)
{
    rapidjson::Value v;
    v.SetArray();
    doc.AddMember(key.c_str(), v, doc.GetAllocator());
    rapidjson::Value& a = doc[key.c_str()];

    rapidjson::Value mapData;
    for (size_t i = 0; i < maps.size(); ++i)
    {
        mapData.SetObject();
        for (auto it = maps[i].begin(); it != maps[i].end(); ++it)
        {
            v.SetInt(it->second);
            mapData.AddMember((it->first).c_str(), v, doc.GetAllocator());
        }
        a.PushBack(mapData, doc.GetAllocator());
    }
}

std::string JsonStringifier::getStringifiedDoc()
{
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    doc.Accept(writer);

    return strbuf.GetString();
}

bool JsonStringifier::reset()
{
    doc.SetObject();
    const char buff[] = "{}";
    if (doc.Parse<0>(buff).HasParseError())
    {
        std::cerr << "Parse error when initializing document in JsonStringifier" << std::endl;
        return false;
    }
    return true;
}
