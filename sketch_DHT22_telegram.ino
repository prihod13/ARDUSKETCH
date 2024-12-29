

#ifdef ESP32 
#include "WiFi.h" 
#else 
#include "ESP8266WiFi.h" 
#endif 

#include "WiFiClientSecure.h" 
#include "UniversalTelegramBot.h" 
#include "ArduinoJson.h" 
//#include "Adafruit_BME280.h" 
#include "Adafruit_Sensor.h" 
#include "DHT.h"

#define DHTPIN 5  
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE); 
// Укажите свои данные сети
const char* ssid = "Mik_prihod2g";
const char* password = "xxxxxxxxxxx";
//5118735295
// Используйте @myidbot, чтобы получить ID пользователя или группы
// Помните, что бот сможет вам писать только после нажатия
// вами кнопки /start
#define CHAT_ID "xxxxxxxxxx"
#define CHAT_ID_2 "xxxxxxxxx"
// Запустите бот Telegram
#define BOTtoken "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  // укажите токен бота

#ifdef ESP8266
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Каждую секунду проверяет новые сообщения
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

// BME280 подключаем к ESP32 I2C (GPIO 21 = SDA, GPIO 22 = SCL)
// BME280 подключаем к ESP8266 I2C (GPIO 4 = SDA, GPIO 5 = SCL)
//Adafruit_BME280 bme;         

// Запрос показаний датчика BME280 и запись их в переменную типа String
String getReadings()
{
  float temperature, humidity;
  


  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
 

  String message = "Температура Червятник : " + String(temperature) + " ºC \n";
  message += "Влажность: " + String (humidity) + " % \n";

  return message;
}

// Задаем действия при получении новых сообщений
void handleNewMessages(int numNewMessages) 
{
    Serial.println("handleNewMessages");
    Serial.println(String(numNewMessages));

    for (int i = 0; i < numNewMessages; i++) 
    { 
        // Идентификатор чата запроса 
        String chat_id = String(bot.messages[i].chat_id); 
        //if (chat_id != CHAT_ID ||chat_id != CHAT_ID_2) 
        //{ 
        //    bot.sendMessage(chat_id, "Unauthorized user", ""); 
        //    continue; 
        //} 

        // Выводим полученное сообщение 
        String text = bot.messages[i].text; 
        Serial.println(text); 
        String from_name = bot.messages[i].from_name; 

        if (text == "/start") 
        { 
            String welcome = "Welcome, " + from_name + ".\n"; 
            welcome += "Use the following command to get current readings.\n\n";
            welcome += "/temp \n"; 

            bot.sendMessage(chat_id, welcome, ""); 
        } 

        if (text == "/temp") 
        { 
           String readings = getReadings(); bot.sendMessage(chat_id, readings, ""); 
        } 
    } 
} 

void setup() 
{ 
    Serial.begin(115200);
    dht.begin();

    #ifdef ESP8266 
    configTime(0, 0, "pool.ntp.org"); // Получаем всемирное координированное время (UTC) через NTP
    client.setTrustAnchors(&cert); // Получаем сертификат api.telegram.org 
    #endif 


    // Запускаем датчик
    delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }


    //dht.begin();
    //if (!dht.begin(true)) 
    //float f = dht.readTemperature(true);
    //float f = dht.readTemperature(true);
    //if (dht.begin())
    //{ 
    // Serial.println("Невозможно обнаружить датчик, проверьте соединение!"); 
    //  while (true); // Останавливаем программу
    //} 

    // Подключаемся к Wi-Fi 
    WiFi.mode(WIFI_STA); 
    WiFi.begin(ssid, password);

    #ifdef ESP32 
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Добавляем корневой сертификат для api.telegram.org 
    #endif

    while (WiFi.status() != WL_CONNECTED) 
    { 
        delay(1000); 
        Serial.println("Подключение WiFi.."); 
    } 

    // Выводим IP ESP32
    Serial.println(WiFi.localIP()); 
} 

void loop() 
{ 
    if (millis() > lastTimeBotRan + botRequestDelay)
    {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        while(numNewMessages) 
        {
            Serial.println("got response");
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
        
        lastTimeBotRan = millis();
    }
}
