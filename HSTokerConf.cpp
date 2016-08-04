#include "HSTokerConf.h"
#include <stdlib.h>

int HSTokerConf::getTitle(char *buffer) {
    return getField(buffer, 1);
}

int HSTokerConf::getSSID(char *buffer) {
    return getField(buffer, 2);
}

int HSTokerConf::getPass(char *buffer) {
    return getField(buffer, 3);
}

int HSTokerConf::getAmbiente(char *buffer) {
  return getField(buffer, 4);
}

int HSTokerConf::getId(char *buffer) {

  return getField(buffer, 5);
}

    

int HSTokerConf::getCarga(char *buffer, int index) {

    int pos;

    if (index == 1)  
        pos = 6;
    else if (index == 2)
        pos = 7;
    else
      return -1;
      
    return getField(buffer, pos);
}


