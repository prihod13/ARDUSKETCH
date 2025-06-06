#include <CustomStepper.h>  

int irsensor= 2;                    // Вывод OUT на модуле подключен к выходу 7 Arduino
int sensorvalue;                    // Переменная для хранения показаний датчика 
 

CustomStepper stepper(8, 9, 10, 11);  // Указываем пины, к которым подключен драйвер шагового двигателя
boolean rotate1 = false;              // Переменная для смены режимов
boolean rotatedeg = false;            // Переменная для смены режимов
boolean crotate = false;              // Переменная для смены режимов                 




void setup()                
{
 Serial.begin(9600);                // Задаем скорость передачи данных
 pinMode(irsensor,INPUT); 
 stepper.setRPM(12);                 // Устанавливаем количество оборотов в минуту
 stepper.setSPR(4075.7728395);       // Устанавливаем колочество шагов на полный оборот. Максимальное значение 4075.7728395
 if (stepper.isDone() &&  rotate1 == false)  
  {
    stepper.setDirection(CCW);        // Устанавливает направление вращения (по часовой)
    stepper.rotate(2);                // Устанавливает вращение на заданное количество оборотов
    rotate1 = true;
  }
  if (stepper.isDone() && rotate1 == true && rotatedeg == false)
  {
    stepper.setDirection(CW);         // Устанавливает направление вращения (против часовой)
    stepper.rotateDegrees(90);        // Поворачивает вал на заданное кол-во градусов
    rotatedeg = true;
  }
  if (stepper.isDone() && rotatedeg == true && crotate == false)
  {
    stepper.setDirection(CCW);        // Устанавливает направление вращения (по часовой)
    stepper.rotate();                 // Будет вращать пока не получит команду о смене направления или STOP
    crotate = true;
  }

}

void loop()
{
 
 sensorvalue=digitalRead(irsensor); // Считываем показания в переменной sensorvalue.
 Serial.print("Sensor ==");         // Выводим текст
 Serial.println(sensorvalue);       // Выводим текст
 if (sensorvalue==1)
 {
  Serial.println(" No obstacle");   // Выводим текст
  delay (1000);
 }
 else{
   stepper.run(); 
 }

}



