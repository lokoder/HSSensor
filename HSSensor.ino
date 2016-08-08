#include "EEConfig.h"
#include "HSTokerConf.h"
#include "HSTokerCmd.h"
#include "HSBoard.h"
#include "FSConfig.h"
#include <ESP8266WiFi.h>


void setup() {

  Serial.begin(115200);
  Serial.printf("[INFO] - ESP-03 inicializado\n");
  
  FSConfig fs;
  HSBoard board(Serial);
  char ssid[32], pass[32];
  int len;
  
  if (fs.init())
    Serial.println("FS Inicializado..");
  else
    Serial.println("Problemas com fs.init()");

    //fs.format();
    
  
  len = fs.getSSID(ssid);
  if (!len) {
    Serial.printf("[INFO] - No SSID. Ativando modo AP..\n");
    board.initAP("rede hackstyle");    
  }

  len = fs.getPass(pass);
  if (!len) {
    Serial.printf("[INFO] - No Pass. A rede %s é aberta?\n", ssid);
  }
  
  board.initSTA(ssid, pass);
  
}

void loop() {}
