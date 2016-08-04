#include "HSBoard.h"
#include "EEConfig.h"

HSBoard::HSBoard(Print &print) {

  printer = &print;
}


void HSBoard::initSTA(char *ssid, char *pass) {

  printer->printf("[INFO] - Conectando em %s com a senha %s\n", ssid, pass);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    printer->print(".");
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

      printer->print("recebido getinfo: ");
      printer->println(req.c_str());
      sendEEConf(client);      
      printer->println("getinfo enviado para o commander");

    } else if (hs.getType() == 's') { //setinfo

      printer->print("recebido setinfo: ");
      printer->println(req.c_str());
      HSTokerConf conf((char*)req.c_str());
      setEEConf(&conf);
      printer->println("setinfo salvo na EEPROM");
      sendEEConf(client);
      printer->println("getinfo enviado para o commander");

      ESP.restart();
      
    } else if (hs.getType() == 'c') { //cmdexec
      
      HSTokerCmd cmd((char*)req.c_str());
      executeCommand(&cmd);
      client->print("cmdexec executado ok!\n");      
    
    } else if (hs.getType() == 'z') {

      //printer->println("getinfo enviado para o commander");
      EEConfig ee;
      ee.zerofill();
      
      printer->println("EEPROM zerada!");
      
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

    EEConfig p;
    char buff[32];

    p.getId(buff);
    int id = atoi(buff);
    if (id < 1) { //virgem

      client->print("getinfo:-1:-2:-3:-4,-5:-1:-2,-3:-3,-4:\n");
      return;
    }

  String msg = "getinfo:";
  
  //  client->print("getinfo:");

    p.getTitle(buff);
    msg+=buff;
    msg+=":";
    //client->print(buff);
    //client->print(":");

    p.getSSID(buff);     
    msg+=buff;
    msg+=":";
    //client->print(buff);
    //client->print(":");

    p.getPass(buff);
    msg+=buff;
    msg+=":";
    //client->print(buff);
    //client->print(":");

    p.getAmbiente(buff);
    msg+=buff;
    msg+=":";
    //client->print(buff);
    //client->print(":");

    p.getId(buff);
    msg+=buff;
    msg+=":";
    //client->print(buff);
    //client->print(":");

    p.getCarga(buff, 1);
    msg+=buff;
    msg+=":";
    //client->print(buff);
    //client->print(":");

    p.getCarga(buff, 2);
    msg+=buff;
    msg+=":";
    msg+="\n";
    //client->print(buff);
    //client->print(":\n");    

    client->print(msg);

}


void HSBoard::setEEConf(HSTokerConf *conf) {  

    EEConfig ee;

    char buff[32];
    if (conf->getTitle(buff)) 
      ee.setTitle(buff);
    

    if (conf->getSSID(buff)) 
      ee.setSSID(buff);   

    if (conf->getPass(buff)) 
      ee.setPass(buff);

    if (conf->getAmbiente(buff))
      ee.setAmbiente(buff);

    if (conf->getId(buff)) 
      ee.setId(buff);

    if (conf->getCarga(buff, 1)) 
      ee.setCarga(buff, 1);
    
    if (conf->getCarga(buff, 2)) 
      ee.setCarga(buff, 2);    
}



