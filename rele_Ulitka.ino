#include "DHT.h"                               // Подключаем библиотеку DHT 
#include <TM1637Display.h>

//#define int set = 0;
////////////////////pin rele
#define PIN12 12
//////////////////keybord
#define PAD1 2 //Buttons pins
#define PAD2 3
#define PAD3 4
#define PAD4 5
//Boolean variable to store pad state

bool PAD1_State, PAD2_State, PAD3_State, PAD4_State; 
///////////////
#define CLK 8
#define DIO 9
TM1637Display display = TM1637Display(CLK, DIO);
// an array that sets individual segments per digit to display the word "dOnE"
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,         // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, // O
  SEG_C | SEG_E | SEG_G,                         // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G          // E
};

// degree celsius symbol
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Degree symbol
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};


//////////////////

#define DHTPIN 7                              // Пин к которому подключен датчик
#define DHTTYPE DHT22                          // Используемый датчик DHT 22 (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);                      // Инициализируем датчик
////////////////////////

void setup() 
{
  Serial.begin(9600);                          // Задаем скорость передачи данных
  //Serial.println("DHT22 TEST!");               // Выводим текст
  dht.begin();
  ///////////////dusplay
  display.clear();
  display.setBrightness(7);
  /////////////////////////key
  pinMode(PAD1,INPUT);    //Set pin modes
  pinMode(PAD2,INPUT);
  pinMode(PAD3,INPUT);
  pinMode(PAD4,INPUT);
  pinMode(PIN12, OUTPUT);
  


}

void loop() 
{
  delay(1000);
  Serial.print("ITER\n");

  PAD1_State = digitalRead(PAD1); 
  PAD2_State = digitalRead(PAD2);
  PAD3_State = digitalRead(PAD3);
  PAD4_State = digitalRead(PAD4);
  while (PAD1_State) {
    Serial.print("27*c \n");            
    int t = dht.readTemperature(); 
    int h = dht.readHumidity(); 
    display.showNumberDec(t, false, 2, 0);
    display.setSegments(celsius, 2, 2);
    delay(2000);
    display.showNumberDec(h);
    delay(2000);
    Serial.print(t);   
    digitalWrite(PIN12,HIGH); 

    if (t >= 27 ) digitalWrite(PIN12,LOW); 
    
  
  }
  while (PAD2_State) {
    Serial.print("28*c \n");            
    int t = dht.readTemperature(); 
    int h = dht.readHumidity(); 
    display.showNumberDec(t, false, 2, 0);
    display.setSegments(celsius, 2, 2);
    delay(2000);
    display.showNumberDec(h);
    delay(2000);
    Serial.print(t);   
    digitalWrite(PIN12,HIGH); 

    if (t >= 28) digitalWrite(PIN12,LOW); ;
  
  }
}





/*
void loop() 
{
  Serial.print("ITER\n");
  PAD1_State = digitalRead(PAD1); 
  PAD2_State = digitalRead(PAD2);
  PAD3_State = digitalRead(PAD3);
  PAD4_State = digitalRead(PAD4);

  if(PAD1_State == HIGH){
  Serial.print("26*c \n");
  delay(2000);                                  // Задежка в 2 с
  int h = dht.readHumidity();                 // Считывание влажности в процентах
  int t = dht.readTemperature();              // Считывание температуры в градусах цельсия
  //float hic = dht.computeHeatIndex(t, h, false);// Расчет типла по целсию
  //Serial.print("Humidity: ");                   // Выводим текст
  //Serial.print(h);                              // Отображаем влажность
  //Serial.print(" %\t");                         // Выводим текст
  //Serial.print("Temperature: ");                // Выводим текст
  //Serial.print(t);                              // Отображаем температуру
  //Serial.println(" *C "); 
  ///////////////////////////////////
  display.showNumberDec(t, false, 2, 0);
  display.setSegments(celsius, 2, 2);
  delay(2000);
  display.showNumberDec(h);
  //display.setSegments(h, 2, 2);
  delay(2000);
  display.clear();
  if (t >= 26 ){
    display.showNumberDec(26, false, 2, 0);
    display.setSegments(celsius, 2, 2);
    delay(1000);
    digitalWrite(PIN12,HIGH); 
  } else {
   digitalWrite(PIN12,LOW); 
  }
        
  }
   

   
  
  if(PAD2_State == HIGH){
   Serial.print("28*c \n");
  delay(2000);                                  // Задежка в 2 с
  int h = dht.readHumidity();                 // Считывание влажности в процентах
  int t = dht.readTemperature();              // Считывание температуры в градусах цельсия
  //float hic = dht.computeHeatIndex(t, h, false);// Расчет типла по целсию
  //Serial.print("Humidity: ");                   // Выводим текст
  //Serial.print(h);                              // Отображаем влажность
  //Serial.print(" %\t");                         // Выводим текст
  //Serial.print("Temperature: ");                // Выводим текст
  //Serial.print(t);                              // Отображаем температуру
  //Serial.println(" *C "); 
  ///////////////////////////////////
  display.showNumberDec(t, false, 2, 0);
  display.setSegments(celsius, 2, 2);
  delay(2000);
  display.showNumberDec(h);
  //display.setSegments(h, 2, 2);
  delay(2000);
  display.clear();
  if (t >= 28 ){
    display.showNumberDec(28, false, 2, 0);
    display.setSegments(celsius, 2, 2);
    delay(1000);
    digitalWrite(PIN12,HIGH); 
  } else {
  digitalWrite(PIN12,LOW); 
  }
  }
  //digitalWrite(PIN12,LOW);  
  delay(1000); 



   
}


  delay(2000);                                  // Задежка в 2 с
  float h = dht.readHumidity();                 // Считывание влажности в процентах
  float t = dht.readTemperature();              // Считывание температуры в градусах цельсия
  //float hic = dht.computeHeatIndex(t, h, false);// Расчет типла по целсию
  Serial.print("Humidity: ");                   // Выводим текст
  Serial.print(h);                              // Отображаем влажность
  Serial.print(" %\t");                         // Выводим текст
  Serial.print("Temperature: ");                // Выводим текст
  Serial.print(t);                              // Отображаем температуру
  Serial.println(" *C "); 
  ///////////////////////////////////


  // displayed 23°C

  display.showNumberDec(t, false, 2, 0);
  display.setSegments(celsius, 2, 2);
  delay(2000);
  
 
  display.showNumberDec(h);
  //display.setSegments(h, 2, 2);
 
 
  delay(2000);
  display.clear();
*/



                    
