#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>

#include "SaveHandler.h"

using namespace std;

SaveHandler::SaveHandler(string path): m_path(path) {}

void SaveHandler::save() {
    /*ofstream stream(m_path.c_str());

    if(stream) stream << "This is a save file." << endl;
    else cout << "An unexpected error occured. Is the file available ?" << endl;*/

    Json::Value event;
    Json::Value vec(Json::arrayValue);
    vec.append(Json::Value(1));
    vec.append(Json::Value(2));
    vec.append(Json::Value(3));

    event["competitors"]["home"]["name"] = "Liverpool";
    event["competitors"]["away"]["code"] = 89223;
    event["competitors"]["away"]["name"] = "Aston Villa";
    event["competitors"]["away"]["code"]=vec;

    cout << event << endl;
}

SaveHandler::~SaveHandler() {}
