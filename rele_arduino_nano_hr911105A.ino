
#include "EtherCard.h"

static byte mymac[] = {0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A }; // MAC Address
static byte myip[] = {192, 168, 1, 55 }; // IP адрес страницы
static byte gwip[] = { 192,168,1,1 };


byte Ethernet::buffer[1100]; BufferFiller bfill;

//int LedPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
boolean PinStatus[] = {4};

const char http_OK[] PROGMEM =
  "HTTP/1.0 200 OK\r\n"
  "Content-Type: text/html\r\n"
  "Pragma: no-cache\r\n\r\n";

const char http_Found[] PROGMEM =
  "HTTP/1.0 302 Found\r\n"
  "Location: /\r\n\r\n";

const char http_Unauthorized[] PROGMEM =
  "HTTP/1.0 401 Unauthorized\r\n"
  "Content-Type: text/html\r\n\r\n"
  "<h1>401 Unauthorized</h1>";

// оформление Web страницы
void homePage() {
  bfill.emit_p(PSTR("$F"
  "<meta http-equiv='Content-Type' content='text/html; charset=utf-8'>"
  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
  "<title>++++BAZA_KARTENON_RELE++++</title>"
  "<h1 style='color:#0ea6f2'>++++BAZA_KARTENON_RELE++++</h1>"
  "<font size='3em'>"
 
  "Rele_status==: <a href='?ArduinoPIN4=$F'>$F</a><br /><br />"
  "</font>"),

  http_OK,
  PinStatus[4] ? PSTR("off") : PSTR("on"),
  PinStatus[4] ? PSTR("<font color='green'>ON</font>") : PSTR("<font color='red'>OFF</font>"));
}

void setup() {
  Serial.begin(9600);

  if (ether.begin(sizeof Ethernet::buffer, mymac, 10) == 0);
  //if (!ether.dhcpSetup());
  // выводим на монитор порта IP, который присвоил роутер для Ардуино
  //ether.printIp("DHCP IP: ", ether.myip);
  // подменяем динамический IP на постоянный
  ether.staticSetup(myip, gwip);
  // выводим на монитор порта новый статический IP 
  ether.printIp("Static IP: ", ether.myip);

  pinMode(4, OUTPUT);//rele_pin
  digitalWrite(4, LOW);
  
  

  //for (int i = 2; i <= 4; i++) {
   // pinMode(LedPins[i], OUTPUT);
   // PinStatus[i] = false;
  
}

void loop() {
  delay(1);
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);

  if (pos) {
    bfill = ether.tcpOffset();
    char *data = (char *) Ethernet::buffer + pos;
    if (strncmp("GET /", data, 5) != 0) {
      bfill.emit_p(http_Unauthorized);
    }
    else {

      data += 5;
      if (data[0] == ' ') {
        homePage(); // если обнаружены изменения на станице, запускаем функцию
      }

      // "16" = количество символов в строке "?ArduinoPIN4=on "

      else if (strncmp("?ArduinoPIN4=on ", data, 16) == 0) {
        digitalWrite(4, LOW);
        PinStatus[4]=true;
        bfill.emit_p(http_Found);
      }
   

      // "17" = количество символов в строке "?ArduinoPIN4=off "

      else if (strncmp("?ArduinoPIN4=off ", data, 17) == 0) {
        digitalWrite(4, HIGH);
        PinStatus[4]=false;
        bfill.emit_p(http_Found);
      }
     
      else { bfill.emit_p(http_Unauthorized); }
    }
    ether.httpServerReply(bfill.position());
  }
}
