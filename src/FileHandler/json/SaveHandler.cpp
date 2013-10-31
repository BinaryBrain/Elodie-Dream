#include <iostream>
#include <fstream>
#include <string>

#include "SaveHandler.h"

using namespace std;

SaveHandler::SaveHandler(string path): m_path(path) {}

void SaveHandler::save() {
    ofstream stream(m_path.c_str());

    if(stream) stream << "This is a save file." << endl;
    else cout << "An unexpected error occured. Is the file available ?" << endl;
}

SaveHandler::~SaveHandler() {}
