#ifndef LANGUAGEHANDLER_H
#define LANGUAGEHANDLER_H

#include "../env.h"
#include "../Json/JsonAccessor.h"

class LanguageHandler {
public:
    static LanguageHandler* getInstance();
    JsonAccessor* getAccessor();

private:
    LanguageHandler();
    virtual ~LanguageHandler();

    static LanguageHandler* lhInstance;
    LanguageHandler& operator= (LanguageHandler const&);

    JsonAccessor* accessor;
};

#endif // LANGUAGEHANDLER_H
