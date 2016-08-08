#include "FSConfig.h"
#include "HSConst.h"
#include <FS.h>


FSConfig::FSConfig() {
}

bool FSConfig::init() {
  
  bool ret = SPIFFS.begin();
  if (!ret) {    
    return false;
  }

  File arq = SPIFFS.open(filepath, "a+"); //se nao existir, cria...
  if (!arq) {
    return false;
  }
  
  
  String conf = arq.readStringUntil('\n');
  conf.toCharArray(buffer, 255);
  
  arq.close();
   
  return true; 
}

int FSConfig::getNome(char *buff) {

  return getField(buff, 2);
}


int FSConfig::getSSID(char *buff) {

  return getField(buff, 3);
}


int FSConfig::getPass(char *buff) {

  return getField(buff, 4);
}


int FSConfig::getAmbiente(char *buff) {

  return getField(buff, 5);
}


int FSConfig::getId(char *buff) {

  return getField(buff, 6);
}


int FSConfig::getCarga(char *buff, int number) {

  if (number == 1)
    return getField(buff, 7);
  else if (number == 2)
    return getField(buff, 8);
}


void FSConfig::close() {

 // SPIFFS.end();
}


void FSConfig::getConfig(char *buff) {

  File f = SPIFFS.open(filepath, "r");
  String conf = f.readStringUntil('\n');

  for (int i=0; i<255; i++)
    buff[i] = '\0';
    
  conf.toCharArray(buff, 255);
  f.close(); 
}

void FSConfig::setConfig(const char *config) {

  File f = SPIFFS.open(filepath, "w");
  f.print(config);
  f.close();

  init();
}



int FSConfig::getField(char *buff, int wanted) {
    
    char *pbuff = buffer, ch;
    int bcount;

    if ( (wanted < 1) || (wanted >8) )
        return 0;

    for (int c=1; c<=MAX_FIELDS; c++) { //iterar sobre os 7 campos de dados

        for (int i=0; i<MAX_FIELD_LEN; i++) //zerar o user-buffer
            buff[i] = '\0';

        bcount = 0;

        for (int i=0; i<MAX_FIELD_LEN; i++) { //maximo de 32 casas por campo

            ch = *pbuff++;

            if ( (ch == ':') && (i==0) ) { //ja comecou com ':'
                if (c == wanted)
                    return 0;

                break;

            } else if ( (ch == ':') && (i>0) ) { //terminamos
            
                if (c == wanted)
                    return bcount;
                else
                    break;

            } else {
             
                buff[bcount++] = ch;
            }

        }
    }

    return 0;
}




/* retorna o tamanho da string, excluindo o caractere '\0' */
int FSConfig::strlen(char *buffer) {

    int count=0;
    char *p = buffer;

    while ( (*p != '\0') && (*p < MAX_MSG_LEN) ) {
        count++;
        p++;
    }

    return count;
}




bool FSConfig::validateMessage(char *message) {

    int msglen = this->strlen(message);
    int colon_count=0;

    if (msglen > MAX_MSG_LEN) {
        return false;
    }

    for (int i=0; i<msglen; i++)
        if (message[i] == ':')
            colon_count++;

    if (colon_count != 8)
        return false;

    return true;
}


void FSConfig::format() {

  SPIFFS.format();
}

