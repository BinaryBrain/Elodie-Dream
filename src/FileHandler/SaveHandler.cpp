#include <iostream>
#include <fstream>
#include <string>
#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output
#include <cstdio>

#include "SaveHandler.h"

SaveHandler::SaveHandler(std::string path) {
    this->path = path;
}

void SaveHandler::save() {
    /*ofstream stream(path.c_str());

    if(stream) stream << "This is a save file." << endl;
    else cout << "An unexpected error occured. Is the file available ?" << endl;*/

}

SaveHandler::~SaveHandler() {}
