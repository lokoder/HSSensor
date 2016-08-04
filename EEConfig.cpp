#include "EEConfig.h"
#include <EEPROM.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

EEConfig::EEConfig() {
}


int EEConfig::read(int offset_ini, int offset_end, char *buff) {

  EEPROM.begin(512);
  
  int count = 0;

  for (int i=0; i<32; i++)
    buff[i] = '\0';
  
  for (int i=offset_ini; i<=offset_end; i++) {

    int n = EEPROM.read(i);
    if ( (n>=32) && (n<=126) ) {
      buff[count]= (char)n;
      count++;
    }    
  } 
  return count;
}


int EEConfig::getTitle(char *buff) {

  return read(title_ini, title_end, buff);
}


void EEConfig::setTitle(char *title) {

  EEPROM.begin(512);
  //zera o espaco
  /*for (int i=title_ini; i<=title_end; i++)
    EEPROM.write(i, '\0');

  EEPROM.commit();*/
    
  int title_len = strlen(title);
  for (int i = title_ini, j=0; (i<=title_end) && (j<title_len); i++, j++) {
    EEPROM.write(i, title[j]);
  }
  EEPROM.commit();
}


int EEConfig::getSSID(char *buff) {

  return read(ssid_ini, ssid_end, buff);
}

void EEConfig::setSSID(char *ssid) {

  EEPROM.begin(512);
  /*for (int i=ssid_ini; i<=ssid_end; i++)
    EEPROM.write(i, '\0');

  EEPROM.commit();*/
  
  int ssid_len = strlen(ssid);
  for (int i = ssid_ini, j=0; (i<=ssid_end) && (j<ssid_len); i++, j++) {
    EEPROM.write(i, ssid[j]);
  }
  EEPROM.commit();  
}

int EEConfig::getPass(char *buff) {

  return read(pass_ini, pass_end, buff);
}

void EEConfig::setPass(char *pass) {

  EEPROM.begin(512);
  /*for (int i=pass_ini; i<=pass_end; i++)
    EEPROM.write(i, '\0');

  EEPROM.commit();*/

  int pass_len = strlen(pass);
  for (int i = pass_ini, j=0; (i<=pass_end) && (j<pass_len); i++, j++) {
    EEPROM.write(i, pass[j]);
  }
  EEPROM.commit();    
}



int EEConfig::getAmbiente(char *buff) {

    return read(ambiente_ini, ambiente_end, buff);
}

void EEConfig::setAmbiente(char *ambiente) {

  EEPROM.begin(512);
  /*for (int i=ambiente_ini; i<=ambiente_end; i++)
    EEPROM.write(i, '\0');

  EEPROM.commit();*/

  int ambiente_len = strlen(ambiente);
  for (int i = ambiente_ini, j=0; (i<=ambiente_end) && (j<ambiente_len); i++, j++) {
    EEPROM.write(i, ambiente[j]);
  }
  EEPROM.commit();    
  
}

int EEConfig::getId(char *buff) {

  return read(id_ini, id_end, buff);
}

void EEConfig::setId(char *id) {

  EEPROM.begin(512);
/*  for (int i=id_ini; i<=id_end; i++)
    EEPROM.write(i, '\0');

  EEPROM.commit();*/

  int id_len = strlen(id);
  for (int i = id_ini, j=0; (i<=id_end) && (j<id_len); i++, j++) {
    EEPROM.write(i, id[j]);
  }
  EEPROM.commit();    
  
}


int EEConfig::getCarga(char *buff, int number) {

  int ini_offset, end_offset;
  int count = 0;
  
  if (number == 1) {
    ini_offset = 160;
    end_offset = 191;
    
  } else if (number == 2) {
    ini_offset = 192;
    end_offset = 223;    
  } else  {
    return 0;
  }

  return read(ini_offset, end_offset, buff);
}



void EEConfig::setCarga(char *carga, int number) {

  EEPROM.begin(512);
  
  int ini_offset, end_offset;
  
  if (number == 1) {
    ini_offset = 160;
    end_offset = 191;
    
  } else if (number == 2) {
    ini_offset = 192;
    end_offset = 223;    
  }

  /*for (int i=ini_offset; i<=end_offset; i++) {
    EEPROM.write(i, '\0');
  }
  EEPROM.commit();*/

  int carga_len = strlen(carga);
  for (int i = ini_offset, j=0; (i<=end_offset) && (j<carga_len); i++, j++) {
    EEPROM.write(i, carga[j]);
  }
  
  EEPROM.commit();      
    
}


void EEConfig::zerofill() {

  EEPROM.begin(512);
  
  for (int i = 0 ; i < 256 ; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

