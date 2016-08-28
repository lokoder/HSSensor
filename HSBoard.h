#ifndef HSBOARD_H
#define HSBOARD_H

#include <ESP8266WiFi.h>
#include "HSTokerCmd.h"
#include "HSTokerConf.h"
#include "FSConfig.h"

class HSBoard {

public:

  HSBoard(Print &print);
  
  void initAP(char *ssid);
  void initSTA(char *ssid, char *pass);

  void setPin12(int active);
  void setPin14(int active);
  int getPin12();
  int getPin14();

private:

  void initServer(void);
  void manageClientReq(WiFiClient *client, String req);
  void executeCommand(HSTokerCmd *cmd);
  void sendEEConf(WiFiClient *client);
  void setEEConf(const char *req);  

  String ipToString(IPAddress ip);  
  Print *printer;

  int pin12, pin14;
  
};

#endif
