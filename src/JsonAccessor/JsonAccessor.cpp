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
        return values[key.c_str()].GetString();
    }
}
int JsonAccessor::getInt(string key)
{
    if(!this->loaded)
    {
        cerr << "Not loaded yet" << endl;
        return 0;
    }
    else
    {
        return values[key.c_str()].GetInt();
    }
}
bool JsonAccessor::load(string file)
{
    if(!this->loaded)
    {
        FILE * pFile = fopen (file.c_str() , "r");
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
