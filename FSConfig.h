#ifndef FSCONFIG_H
#define FSCONFIG_H

#include <ESP8266WiFi.h>

class FSConfig {

public:
  
  FSConfig();
  FSConfig(Print &print);

  bool init();
  
  int getNome(char *buff);
  int getSSID(char *buff);
  int getPass(char *buff);
  int getAmbiente(char *buff);
  int getId(char *buff);
  int getCarga(char *buff, int number);


  void getConfig(char *buff);
  void setConfig(const char *config);
  void close();

  int getField(char *buff, int wanted); 
  void format(); 

private:

  Print *printer;
  
  char *filepath = "hs.conf";
  char buffer[256];

  bool error;
  
  bool validateMessage(char *message);
  int strlen(char *buffer);  
  bool updateConf();

};


#endif
