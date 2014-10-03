#ifndef JSONSTRINGIFIER_H
#define JSONSTRINGIFIER_H

#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output<w>
#include "rapidjson/stringbuffer.h"
#include "../env.h"

class JsonStringifier {
public:
    JsonStringifier();
    virtual ~JsonStringifier();

    void add(std::string key, int i);
    void add(std::string key, std::string s);
    void add(std::string key, std::vector<int> v);
    std::string getStringifiedDoc();

private:
    rapidjson::Document values;
};

#endif // JSONSTRINGIFIER_H
