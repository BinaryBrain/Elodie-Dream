#include "JsonAccessor.h"

using std::cerr;
using std::endl;

JsonAccessor::JsonAccessor()
{
    //ctor
}

JsonAccessor::~JsonAccessor()
{
    //dtor
}
string JsonAccessor::getString(string key)
{
    if(!loaded)
    {
        cerr << "Not loaded yet" << endl;
        return "";
    }
    else
    {
        return values[Utils::toCharArray(key)].GetString();
    }
}
int JsonAccessor::getInt(string key)
{
    if(!loaded)
    {
        cerr << "Not loaded yet" << endl;
        return 0;
    }
    else
    {
        return values[Utils::toCharArray(key)].GetInt();
    }
}
bool JsonAccessor::load(string file)
{
    if(!loaded)
    {
        FILE * pFile = fopen (Utils::toCharArray(file) , "r");
        rapidjson::FileStream is(pFile);
        if(values.ParseStream<0>(is).HasParseError())
        {
            cerr << "Parse Error" << endl;
        }
        loaded = true;
        return true;
    }
    else
    {
        cerr << "Already loaded" << endl;
        return false;
    }
}
