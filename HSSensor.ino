#include "EEConfig.h"
#include "HSTokerConf.h"
#include "HSTokerCmd.h"
#include "HSBoard.h"
#include "FSConfig.h"
#include <ESP8266WiFi.h>


void setup() {

  Serial.begin(115200);
  Serial.printf("[INFO] - ESP-03 inicializado\n");


  /*FSConfig fs(Serial);
  if (fs.init()) {
    Serial.println("FS Inicializado..");
  } else {
    Serial.println("Problemas com fs.init()");
  }

  char buff[255] = {0};

  //char *conf = "setinfo:rack:ap36:ap36erick:1,Sala:1:led,12:led,14:";
  //fs.setConfig(conf);  
  fs.getConfig(buff);

  //Serial.println(buff);

 fs.close();*/




  
  FSConfig fs;
  HSBoard board(Serial);
  char ssid[32], pass[32];
  int len;
  
  if (fs.init())
    Serial.println("FS Inicializado..");
  else
    Serial.println("Problemas com fs.init()");

  len = fs.getSSID(ssid);
  if (!len) {
    fs.close();
    Serial.printf("[INFO] - No SSID. Ativando modo AP..\n");
    board.initAP("rede hackstyle");    
  }

  len = fs.getPass(pass);
  if (!len) {
    Serial.printf("[INFO] - No Pass. A rede %s é aberta?\n", ssid);
  }

  fs.close();
  
  board.initSTA(ssid, pass);
  
}

void loop() {}
