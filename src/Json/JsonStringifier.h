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

    void setInt(std::string key, int i);
    void setString(std::string key, std::string s);
    void setIntVector(std::string key, std::vector<int> v);
    void setInt2DVector(std::string key, std::vector<std::vector<int> > v);
    std::string getStringifiedDoc();

private:
    rapidjson::Document values;
};

#endif // JSONSTRINGIFIER_H
