#include "EtherCard.h"

static byte mymac[] = {0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A }; // MAC Address
static byte myip[] = {10, 161, 161, 60}; // IP адрес страницы
byte Ethernet::buffer[1200]; BufferFiller bfill;

int LedPins[] = { 8};
boolean PinStatus[] = {8};

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
  "<title>Управление Ардуино УНО</title>"
  "<h1 style='color:#0ea6f2'>Управление Ардуино</h1>"
  "<font size='3em'>"
  "<font style='display:none;'>RELE: <a href='?ArduinoPIN8=$F'>$F</a></font>"
  "RELE: <a href='?ArduinoPIN8=$F'>$F</a><br /><br />"
 
  "</font>"),

  http_OK,
  PinStatus[8] ? PSTR("off") : PSTR("on"),
  PinStatus[8] ? PSTR("<font color='green'>ON</font>") : PSTR("<font color='red'>OFF</font>"));
  ;
}

void setup() {
  Serial.begin(9600);

  if (ether.begin(sizeof Ethernet::buffer, mymac, 10) == 0);
  // подменяем динамический IP на постоянный
  ether.staticSetup(myip);
  // выводим на монитор порта новый статический IP 
  ether.printIp("MyIP: ", ether.myip);
  pinMode(LedPins[8], OUTPUT);
  PinStatus[8] = false;
  
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
        digitalWrite(LedPins[8], PinStatus[8]); 
      }
      // "16" = количество символов в строке "?ArduinoPIN1=on "

      else if (strncmp("?ArduinoPIN8=on ", data, 16) == 0) {
        PinStatus[8] = true;
        bfill.emit_p(http_Found);
      }

      // "17" = количество символов в строке "?ArduinoPIN1=off "

      else if (strncmp("?ArduinoPIN8=off ", data, 17) == 0) {
        PinStatus[8] = false;
        bfill.emit_p(http_Found);
      }
     
      else { bfill.emit_p(http_Unauthorized); }
    }
    ether.httpServerReply(bfill.position());
  }
}
