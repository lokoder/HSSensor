#ifndef HSTOKERCONF_H
#define HSTOKERCONF_H

#include "HSToker.h"

class HSTokerConf : public HSToker {

public:

    HSTokerConf(char *message) : HSToker(message) {}


    int getTitle(char *buffer);
    int getSSID(char *buffer);
    int getPass(char *buffer);
    int getAmbiente(char *buffer);
    int getId(char *id);
    int getCarga(char *buffer, int index);

private:

};


#endif
