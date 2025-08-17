#include <TM1638.h>
#include "DHT.h"     


#define DHTPIN 3                             // Пин к которому подключен датчик
#define DHTTYPE DHT22                          // Используемый датчик DHT 22 (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);                      // Инициализируем датчик
////////////////////////

////////////////////pin rele
#define PIN13 13

TM1638 module(8,9,10);
/* Подключение модуля: 
 *  8pin - DIO(data) 
 *  9pin - CLK(clock)
 *  10pin - STB(strobe)
 */
//module.clearDisplay();
//byte keys = module.getButtons();
void setup() {

  Serial.begin(9600);
  dht.begin();
  pinMode(PIN13, OUTPUT);
  //byte keys = module.getButtons();
  module.setupDisplay(true, 1);
  String str1 = "HIPrIhod"; 
  module.setDisplayToString(str1);
  delay(1000);
  module.clearDisplay();


  //int t = dht.readTemperature(); 
  //int h = dht.readHumidity();

  //byte keys = module.getButtons();
  //Serial.println(keys); //Пишем в монитор порта нажатие кнопок
  //module.setLEDs(((keys & 0xFF) << 8) | (keys & 0xFF));  //зажигаем светодиод в зависимости от кнопки
  //module.setDisplayToHexNumber(OCR1A,  0xFF);
  //module.setLEDs(0xFF);  //Включаем все светодиоды

}

void loop() {
  byte keys = module.getButtons();
  Serial.println(keys);//Пишем в монитор порта нажатие кнопок
  module.setLEDs(((keys & 0xFF) << 8) | (keys & 0xFF)); //зажигаем светодиод в зависимости от кнопки
  delay(2000); 
  int t = dht.readTemperature(); 
  int h = dht.readHumidity();
  String str = String(t) + "*C.";
  String str2 = String(h) + "H";
  module.setDisplayToString(str+str2);
  delay(2000); 
  
  while(keys == 1){
    module.clearDisplay();
    Serial.println(keys);//Пишем в монитор порта нажатие кнопок
    module.setLEDs(((keys & 0xFF) << 8) | (keys & 0xFF)); //зажигаем светодиод в зависимости от кнопки
    String regim = "SET_22*C";
    module.setDisplayToString(regim);
    delay(2000); 
    int t = dht.readTemperature(); 
    int h = dht.readHumidity();
    String str = String(t) + "*C.";
    String str2 = String(h) + "H";
    module.setDisplayToString(str+str2);
    Serial.print("Humidity: ");                   // Выводим текст
    Serial.print(h);                              // Отображаем влажность
    Serial.print(" %\t");                         // Выводим текст
    Serial.print("Temperature: ");                // Выводим текст
    Serial.print(t);                              // Отображаем температуру
    Serial.println(" *C "); 
    //digitalWrite(PIN13,HIGH); 
    delay(4000); 
    if (t <= 22){
      digitalWrite(PIN13,LOW);
    } else digitalWrite(PIN13,HIGH);

  }
  while(keys == 2){
    module.clearDisplay();
    Serial.println(keys);//Пишем в монитор порта нажатие кнопок
    module.setLEDs(((keys & 0xFF) << 8) | (keys & 0xFF)); //зажигаем светодиод в зависимости от кнопки
    String regim = "SET_23*C";
    module.setDisplayToString(regim);
    delay(2000); 
    int t = dht.readTemperature(); 
    int h = dht.readHumidity();
    String str = String(t) + "*C.";
    String str2 = String(h) + "H";
    module.setDisplayToString(str+str2);
    Serial.print("Humidity: ");                   // Выводим текст
    Serial.print(h);                              // Отображаем влажность
    Serial.print(" %\t");                         // Выводим текст
    Serial.print("Temperature: ");                // Выводим текст
    Serial.print(t);                              // Отображаем температуру
    Serial.println(" *C "); 
    //digitalWrite(PIN13,HIGH); 
    delay(4000); 
    if (t <= 23){
      digitalWrite(PIN13,LOW);
    } else digitalWrite(PIN13,HIGH);

  }
  while(keys == 4){
    module.clearDisplay();
    Serial.println(keys);//Пишем в монитор порта нажатие кнопок
    module.setLEDs(((keys & 0xFF) << 8) | (keys & 0xFF)); //зажигаем светодиод в зависимости от кнопки
    String regim = "SET_24*C";
    module.setDisplayToString(regim);
    delay(2000); 
    int t = dht.readTemperature(); 
    int h = dht.readHumidity();
    String str = String(t) + "*C.";
    String str2 = String(h) + "H";
    module.setDisplayToString(str+str2);
    Serial.print("Humidity: ");                   // Выводим текст
    Serial.print(h);                              // Отображаем влажность
    Serial.print(" %\t");                         // Выводим текст
    Serial.print("Temperature: ");                // Выводим текст
    Serial.print(t);                              // Отображаем температуру
    Serial.println(" *C "); 
    //digitalWrite(PIN13,HIGH); 
    delay(4000); 
    if (t <= 24){
      digitalWrite(PIN13,LOW);
    } else digitalWrite(PIN13,HIGH);

  }
  while(keys == 8){
    module.clearDisplay();
    Serial.println(keys);//Пишем в монитор порта нажатие кнопок
    module.setLEDs(((keys & 0xFF) << 8) | (keys & 0xFF)); //зажигаем светодиод в зависимости от кнопки
    String regim = "SET_25*C";
    module.setDisplayToString(regim);
    delay(2000); 
    int t = dht.readTemperature(); 
    int h = dht.readHumidity();
    String str = String(t) + "*C.";
    String str2 = String(h) + "H";
    module.setDisplayToString(str+str2);
    Serial.print("Humidity: ");                   // Выводим текст
    Serial.print(h);                              // Отображаем влажность
    Serial.print(" %\t");                         // Выводим текст
    Serial.print("Temperature: ");                // Выводим текст
    Serial.print(t);                              // Отображаем температуру
    Serial.println(" *C "); 
    //digitalWrite(PIN13,HIGH); 
    delay(4000); 
    if (t <= 25){
      digitalWrite(PIN13,LOW);
    } else digitalWrite(PIN13,HIGH);

  }
  while(keys == 16){
    module.clearDisplay();
    Serial.println(keys);//Пишем в монитор порта нажатие кнопок
    module.setLEDs(((keys & 0xFF) << 8) | (keys & 0xFF)); //зажигаем светодиод в зависимости от кнопки
    String regim = "SET_26*C";
    module.setDisplayToString(regim);
    delay(2000); 
    int t = dht.readTemperature(); 
    int h = dht.readHumidity();
    String str = String(t) + "*C.";
    String str2 = String(h) + "H";
    module.setDisplayToString(str+str2);
    Serial.print("Humidity: ");                   // Выводим текст
    Serial.print(h);                              // Отображаем влажность
    Serial.print(" %\t");                         // Выводим текст
    Serial.print("Temperature: ");                // Выводим текст
    Serial.print(t);                              // Отображаем температуру
    Serial.println(" *C "); 
    //digitalWrite(PIN13,HIGH); 
    delay(4000); 
    if (t <= 26){
      digitalWrite(PIN13,LOW);
    } else digitalWrite(PIN13,HIGH);

  }
  while(keys == 32){
    module.clearDisplay();
    Serial.println(keys);//Пишем в монитор порта нажатие кнопок
    module.setLEDs(((keys & 0xFF) << 8) | (keys & 0xFF)); //зажигаем светодиод в зависимости от кнопки
    String regim = "SET_27*C";
    module.setDisplayToString(regim);
    delay(2000); 
    int t = dht.readTemperature(); 
    int h = dht.readHumidity();
    String str = String(t) + "*C.";
    String str2 = String(h) + "H";
    module.setDisplayToString(str+str2);
    Serial.print("Humidity: ");                   // Выводим текст
    Serial.print(h);                              // Отображаем влажность
    Serial.print(" %\t");                         // Выводим текст
    Serial.print("Temperature: ");                // Выводим текст
    Serial.print(t);                              // Отображаем температуру
    Serial.println(" *C "); 
    //digitalWrite(PIN13,HIGH); 
    delay(4000); 
    if (t <= 27){
      digitalWrite(PIN13,LOW);
    } else digitalWrite(PIN13,HIGH);

  }
  while(keys == 64){
    module.clearDisplay();
    Serial.println(keys);//Пишем в монитор порта нажатие кнопок
    module.setLEDs(((keys & 0xFF) << 8) | (keys & 0xFF)); //зажигаем светодиод в зависимости от кнопки
    String regim = "SET_28*C";
    module.setDisplayToString(regim);
    delay(2000); 
    
    int t = dht.readTemperature(); 
    int h = dht.readHumidity();
    String str = String(t) + "*C.";
    String str2 = String(h) + "H";
    module.setDisplayToString(str+str2);
    Serial.print("Humidity: ");                   // Выводим текст
    Serial.print(h);                              // Отображаем влажность
    Serial.print(" %\t");                         // Выводим текст
    Serial.print("Temperature: ");                // Выводим текст
    Serial.print(t);                              // Отображаем температуру
    Serial.println(" *C "); 
    //digitalWrite(PIN13,HIGH); 
    delay(4000); 
    
    if (t <= 28){
      digitalWrite(PIN13,LOW);
    } else digitalWrite(PIN13,HIGH);

  }
  

}
