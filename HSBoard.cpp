#include "HSBoard.h"
#include "EEConfig.h"
#include "FSConfig.h"

HSBoard::HSBoard(Print &print) {

  printer = &print;
}


void HSBoard::initSTA(char *ssid, char *pass) {

RECON:

  printer->printf("[INFO] - Conectando em %s com a senha %s\n", ssid, pass);
  
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  int counter = 0;
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    printer->print(".");
    counter++;

    if (counter >= 100)
      break;    
  }

  if (WiFi.status() != WL_CONNECTED) {
    goto RECON;
  }
  
  printer->println("");
  String ip = WiFi.localIP().toString();
  printer->printf("[INFO] - Conectado em WiFi %s com IP %s\n", ssid, ip.c_str());

  initServer();
}


void HSBoard::initAP(char *ssid) {

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  String ip = WiFi.softAPIP().toString();
  printer->printf("[INFO] - Servidor modo AP em %s:8000\n", ip.c_str());

  initServer();
}



void HSBoard::executeCommand(HSTokerCmd *cmd) {

  pinMode(cmd->getPin(), OUTPUT);
  digitalWrite(cmd->getPin(), cmd->getValue());  
}


String HSBoard::ipToString(IPAddress ip) {
  
  String s="";
  for (int i=0; i<4; i++)
    s += i  ? "." + String(ip[i]) : String(ip[i]);
    
  return s;
}  


void HSBoard::manageClientReq(WiFiClient *client, String req) {

    HSToker hs((char*)req.c_str());
    if (!hs.isValid()) {
      printer->printf("[ERRO] - Requisicao invalida: %s\n", req.c_str());
      client->stop();
      return;
    }

    printer->printf("[INFO] - Requisicao recebida: %s\n", req.c_str());
    
    if (hs.getType() == 'g') { //getinfo

      printer->print("recebido getinfo. enviando getinfo para o commander...");      
      sendEEConf(client);   
      printer->println("getinfo enviado para o commander!");

    } else if (hs.getType() == 's') { //setinfo

      printer->print("recebido setinfo. salvando no fs...");
      setEEConf(req.c_str());
      printer->println("setinfo salvo na EEPROM");
      sendEEConf(client);
      printer->println("getinfo enviado para o commander; reiniciando esp-03, bye!");

      ESP.restart();
      
    } else if (hs.getType() == 'c') { //cmdexec
      
      HSTokerCmd cmd((char*)req.c_str());
      executeCommand(&cmd);
      client->print("cmdexec executado ok!\n");      
    
    } else if (hs.getType() == 'z') {

      printer->println("Recebido comando para formatar o FS");
      FSConfig fs;
      fs.init();
      fs.format();
      client->print("FileSystem do sensor formatado com sucesso!");
      printer->println("FileSystem formatado! Reiniciando ESP03.... bye!");
           
      ESP.restart();      
    }
      
}


void HSBoard::initServer(void) {

  WiFiServer srv(8000);
  srv.begin();

  //printer->printf("Entrou em initServer\n");
  
  while (true) {

    //printer->printf(".");
 
    WiFiClient client = srv.available();
    if (!client) {
      //printer->printf("not available\n");
      continue;
    }

    printer->printf("[INFO] - Novo cliente conectado\n");
    while (!client.available()) {
      delay(1);
    }
    
    String req = client.readStringUntil('\n');
    manageClientReq(&client, req);
    client.stop();
  }
  
}



void HSBoard::sendEEConf(WiFiClient *client) {

    FSConfig fs;
    char buff[255];

    fs.init();
    fs.getId(buff);

    int id = atoi(buff);
    if (id < 1) { //virgem
      client->print("getinfo:-1:-2:-3:-4,-5:-1:-2,-3:-3,-4:\n");      
      return;
    }

    fs.getConfig(buff);
    buff[0] = 'g';
    printer->printf("getinfo recuperado de fs: %s\n", buff);    
    
    client->printf("%s\n", buff);
}


void HSBoard::setEEConf(const char *req) {  

  FSConfig fs;

  fs.init();
  fs.setConfig(req);

  printer->printf("getinfo salvo em fs: %s\n", req);
}



