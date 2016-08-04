#ifndef HSBOARD_H
#define HSBOARD_H

#include <ESP8266WiFi.h>
#include "HSTokerCmd.h"
#include "HSTokerConf.h"

class HSBoard {

public:

  HSBoard(Print &print);
  
  void initAP(char *ssid);
  void initSTA(char *ssid, char *pass);

private:

  void initServer(void);
  void manageClientReq(WiFiClient *client, String req);
  void executeCommand(HSTokerCmd *cmd);
  void sendEEConf(WiFiClient *client);
  void setEEConf(HSTokerConf *conf);  

  String ipToString(IPAddress ip);  
  Print *printer;
};

#endif
