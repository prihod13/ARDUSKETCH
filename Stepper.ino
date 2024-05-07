/* Name: Stepper control  
   Description: Arduino ATmega 328P + TB6600 Driver + Stepper Motor 23HS5628
   Author:      TDA

       Arduino pinout diagram:
          _______________
         |      USB      |
         |           AREF|
         |            GND|
         |             13| 
         |RESET        12| 
         |3V3         #11|
         |5V          #10|
         |GND          #9|
         |VIN           8| 
         |               |
         |              7| 
         |             #6|
         |A0           #5| ENA
         |A1            4| DIR
         |A2           #3| STEP
         |A3            2| 
         |A4         TX 1|
         |A5         RX 0|
         |_______________|               
*/
#include <TM1638.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//переменые шаговика
#define STEP   3
#define DIR    4
#define ENA    5 
// переменые энкодера 
//#define CLK 11                        // Указываем к какому выводу CLK энкодер подключен к Arduino
//#define DT 10                         // Указываем к какому выводу DT энкодер подключен к Arduino
//#define SW 12                     // Указываем к какому выводу SW энкодер подключен к Arduino
/* Подключение модуля: 
 *  8pin - DIO(data) 
 *  9pin - CLK(clock)
 *  7pin - STB(strobe)
 */

TM1638 module(8,9,7);


//int counter = 5000;
//int counterSH=50000;
//int counter = 0;                    // Создаем переменную counter
//int currentStateCLK;                  // Создаем переменную currentStateCLK
//int lastStateCLK;                     // Создаем переменную lastStateCLK
//String currentDir ="";                // Создаем 
//unsigned long lastButtonPress = 0;    // Создаем переменную lastBut



 
void setup() 
  {
    //пишем символы на дисплее и точки между 8мя знаками
    digitalWrite(ENA, HIGH);  // Разрешение управления двигателями
    Serial.begin(9600);
   
    /*
    pinMode(CLK, INPUT);                // Указываем вывод CLK как вход
    pinMode(DT, INPUT);                 // Указываем вывод DT как вход
    pinMode(SW, INPUT_PULLUP);          // Указываем вывод SW как вход и включаем подтягивающий резистор
    Serial.begin(9600);                 // Создаем последовательную связь 
    lastStateCLK = digitalRead(CLK);    // Считываем значение с CLK
    /*
     * 
     */
    int us =2000;
    int a = 400;
    module.setupDisplay (true, 1);
    //module.setDisplayToDecNumber (a,true);
    String str1 = "HIPrIhod"; 
    String str2 = "E L 0400";
    module.setDisplayToString(str1);
    delay(us);
    
    module.setDisplayToString(str2);  
    // опрееделения шаговика //////////////////////////////////////////////////////////////////////
   
    
    pinMode(STEP, OUTPUT);   // Инициализация входов/выходов  
    pinMode(DIR,  OUTPUT);
    pinMode(ENA,  OUTPUT);
    digitalWrite(DIR, HIGH); // Направление вращения 
       

    cli();                                                                        // Глобальный запрет прерываний
    TCCR1A=(0<<COM1A1)|(0<<COM1B1)|(0<<COM1A0)|(0<<COM1B0)|(0<<WGM11)|(0<<WGM10); // Настройка таймера/счетчика 1: нормальный режим работы порта, OC1A/OC1B отключены; ATmega328/P DATASHEET стр.170-172
    TCCR1B=(0<<WGM13)|(1<<WGM12)|(0<<CS12)|(0<<CS11)|(1<<CS10);                   // Режим работы таймера/счетчика - CTC (очистить таймер при достижении значения в регистре сравнения OCR1A)
    OCR1A = 6000 ;                                                                 // Значение в регистре OCR1A определяет частоту входа в прерывание таймера и устанавливает скрость вращения двигателей
    TIMSK1 = 0b00000010;                                                          // Разрешение прерываний от таймера/счетчика
    sei();                                                                        // Глобальное разрешение прерываний
  }

void loop()
  /*{
    currentStateCLK = digitalRead(CLK); // Считываем значение с CLK
  // Проверяем изменилось ли состояние CLK
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
    if (digitalRead(DT) != currentStateCLK) {
      OCR1A =  OCR1A - counter ;

      currentDir ="Скорость ниже ";
    } else {
      
      OCR1A =  OCR1A + counter ;
      
      currentDir ="Скорость выше";
    }
    Serial.print("Вывод: ");
    Serial.print(currentDir);
    Serial.print(" | На: ");
    Serial.println(OCR1A);
  }

  lastStateCLK = currentStateCLK;         // Сохраняем последнее состояние CLK
  /*
   * 
   */
  //tmp1638
  {
    
  //module.clearDisplay(); // clear display
  byte keys = module.getButtons();
  //Serial.println(keys); //Пишем в монитор порта нажатие кнопок
  //module.setLEDs(((keys & 0xFF) << 8) | (keys & 0xFF));  //зажигаем светодиод в зависимости от кнопки
  //module.setDisplayToHexNumber(OCR1A,  0xFF);
  //module.setLEDs(0xFF);  //Включаем все светодиоды
  //speed+++
  //int speed =  1000;
  // keys pool
  //if (keys==true) module.clearDisplay();
  
  if (keys == 1){
    String str_dirl = "  L ";
    module.setDisplayToString(str_dirl);
    digitalWrite(DIR, HIGH);
  }
  if (keys == 2){
    String str_dirr = "  P ";
    module.setDisplayToString(str_dirr);
    digitalWrite(DIR, LOW);
  }
  
  if (keys == 4){
    String str_ena = "E   ";
    module.setDisplayToString(str_ena);
    digitalWrite(ENA, HIGH);
    module.setLEDs(0xFF);
  } 
  if (keys == 8){
    String str_ens = "A   ";
    module.setDisplayToString(str_ens);
    digitalWrite(ENA, LOW);
    module.setLEDs(((keys & 0xFF) << 8) | (keys = 5));
  } 
 
   
  // keys speed
  if (keys == 128){
    OCR1A = 55000;
    int a = 5500;
    module.setDisplayToDecNumber (a,false);
  }
  if (keys == 64){
    OCR1A = 40000;
    int a = 4000;
    module.setDisplayToDecNumber (a,false);    
  }   
  if (keys == 32){
    OCR1A = 25000;
    int a = 2500;
    module.setDisplayToDecNumber (a,false);
  }
  if (keys == 16){
    OCR1A = 3000;
    int a = 300;
    module.setDisplayToDecNumber (a,false);   
  }

  
    

  
  
  
  //module.clearDisplay();
  //String str2 = "L E 0400";
  //module.setDisplayToString(str1);
  
  
  
  
  }


ISR(TIMER1_COMPA_vect)                             // Вектор прерывания от таймера/счетчика 1
  {                    
    if (PORTD & 0b00001000) {PORTD &= 0b11110111;} // STEP HIGH
    else                    {PORTD |= 0b00001000;} // STEP LOW
  }
