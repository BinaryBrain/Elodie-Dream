#ifndef JSONSTRINGIFIER_H
#define JSONSTRINGIFIER_H

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filestream.h"
#include "rapidjson/stringbuffer.h"
#include "../env.h"

class JsonStringifier
{
public:
    JsonStringifier();
    virtual ~JsonStringifier();

    void add(std::string key, int i);
    void add(std::string key, double d);
    void add(std::string key, std::string s);
    void add(std::string key, std::vector<int> v);
    void add(std::string key, std::vector< std::vector<int> > v2d);
    void add(const std::string& key, const std::map<std::string, int>& m);
    void add(const std::string& key, const std::vector< std::map<std::string, int> >& maps);
    std::string getStringifiedDoc();
    bool reset();

private:
    rapidjson::Document doc;
};

#endif // JSONSTRINGIFIER_H
