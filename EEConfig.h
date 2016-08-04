#include <ESP8266WiFi.h>

class EEConfig {

public:

  EEConfig();
  EEConfig(Print &print);
  
  int getTitle(char *buff);
  void setTitle(char *title);

  int getSSID(char *buff);
  void setSSID(char *ssid);

  int getPass(char *buff);
  void setPass(char *pass);

  int getAmbiente(char *buff);
  void setAmbiente(char *ambiente);

  int getId(char *buff);
  void setId(char *id);
  
  int getCarga(char *buff, int number);
  void setCarga(char *carga, int number);
  
  void zerofill();

private:

  Print *printer;
  int read(int offset_ini, int offset_end, char *buff);
  
  const int title_ini = 0;
  const int title_end = 31;
  
  const int ssid_ini = 32;
  const int ssid_end = 63;
  
  const int pass_ini = 64;
  const int pass_end = 95;
  
  const int ambiente_ini = 96;
  const int ambiente_end = 127;
  
  const int id_ini = 128;
  const int id_end = 159;
  
  const int car1_ini = 160;
  const int car1_end = 191;
  
  const int car2_ini = 192;
  const int car2_end = 223;
  
};

