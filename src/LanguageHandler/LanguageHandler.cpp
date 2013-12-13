#include "LanguageHandler.h"

// Initialisation of the singleton to NULL
LanguageHandler* LanguageHandler::lhInstance = NULL;

LanguageHandler::LanguageHandler() {
    //ctor
}

LanguageHandler::~LanguageHandler() {
    //dtor
}

// Gets the instance of the LangugaeHandler
LanguageHandler* LanguageHandler::getInstance() {
    if(!lhInstance) lhInstance = new LanguageHandler();
    return lhInstance;
}

JsonAccessor* LanguageHandler::getAccessor() {
    return accessor;
}
