#include "EEConfig.h"
#include "HSTokerConf.h"
#include "HSTokerCmd.h"
#include "HSBoard.h"
#include <ESP8266WiFi.h>


void setup() {

  Serial.begin(115200);

  EEConfig econf;
  //econf.zerofill();
  
  HSBoard board(Serial);
  char ssid[32], pass[32];
  int len;

  Serial.printf("[INFO] - ESP-03 inicializado\n");
  
  len = econf.getSSID(ssid);
  if (!len) {
    Serial.printf("[INFO] - No SSID. Ativando modo AP..\n");
    board.initAP("rede hackstyle");    
  }

  len = econf.getPass(pass);
  if (!len) {
    Serial.printf("[INFO] - No Pass. A rede %s é aberta?\n", ssid);
  }
  
  board.initSTA(ssid, pass);
  
}

void loop() {}
