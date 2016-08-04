#ifndef HSTOKER_H
#define HSTOKER_H

#include "HSConst.h"

class HSToker {

public:

    HSToker();
    HSToker(char *message);

    bool isValid(void);
    char getType();
    int getField(char *buff, int wanted);

private:

    char buffer[MAX_MSG_LEN];
    int strlen(char *buffer);
    bool validateMessage(char *message);

    bool valid;
    char type;
};

#endif
