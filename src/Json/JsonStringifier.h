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

    void setInt(int i, std::string key);
    void setString(std::string s, std::string key);
    void setIntVector(std::vector<int> v, std::string key);
    void setInt2DVector(std::vector<std::vector<int> > v, std::string key);
    rapidjson::Document* getDocument();

private:
    rapidjson::Document values;
};

#endif // JSONSTRINGIFIER_H
