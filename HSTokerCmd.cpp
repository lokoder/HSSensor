#include "HSTokerCmd.h"
#include <stdlib.h>

int HSTokerCmd::getPin(void) {
    
    char buff[32]={0};

    if (getField(buff, 1))
        return atoi(buff);
}


int HSTokerCmd::getValue(void) {

    char buff[32]={0};

    if (getField(buff, 2))
        return atoi(buff);
}


