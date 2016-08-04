#ifndef HSTOKERCMD_H
#define HSTOKERCMD_H

#include "HSToker.h"

class HSTokerCmd : public HSToker {

public:

    HSTokerCmd(char *message) : HSToker(message) {}

    int getPin(void);
    int getValue(void);

private:

};


#endif
