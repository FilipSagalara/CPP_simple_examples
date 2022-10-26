/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <dht11.h>
#include <BH1750.h>




dht11 DHT11;
#define DHT11PIN 2    //przypisanie pinu 2 Arduino jako odczyt z sensora
#define MOISTURE_PIN 15
#define ESP_OUT 4 //Zmienic pin!!

// Replace the next variables with your SSID/Password combination
const char* ssid = "Playstation 5";
const char* password = "XRHSHJPH";

// Add your MQTT Broker IP address, example:
const char* mqtt_server = "192.168.68.114";
String id = "Node1";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


//const int D4 = 4;

//Light sensor
BH1750 light_sensor(0x23);

float lux  = 0.0;

//DHT sensor 

float temperature = 0.0;
float humidity = 0.0;

char temp_string[10]= "Undefined";
char humidity_string[10]= "Undefined";


void moisture_read(){

  int moisture = analogRead(MOISTURE_PIN);
  Serial.println("Moisture at level");
  Serial.println(moisture);
  delay(2000);
}





void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void read_dht(float &temp, float &humidity ){
  Serial.println("Reading from DHT sensor");
  int chk = DHT11.read(DHT11PIN);         //sprawdzenie stanu sensora, a następnie wyświetlenie komunikatu na monitorze szeregowym
  Serial.print("Stan sensora: ");
  switch (chk)
  {
    case DHTLIB_OK: 
    Serial.print("OKt"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.println("Błąd sumy kontrolnej"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.println("Koniec czasu oczekiwania - brak odpowiedzi"); 
    break;
    default: 
    Serial.println("Nieznany błąd"); 
    break;
  }
  Serial.print("Wilgotnosc (%): ");              //wyświetlenie wartości wilgotności
  Serial.print((float)DHT11.humidity, 2);
  Serial.print("tt");
  Serial.print("Temperatura (C): ");           //wyświetlenie temperatury
  Serial.println((float)DHT11.temperature, 2);
  Serial.println("Koniec odczytu dht");
  temp = (float)DHT11.temperature;
  humidity = (float)DHT11.humidity;
}



void callback(char* topic, byte* message, unsigned int length) {
  
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  // Feel free to add more if statements to control more GPIOs with MQTT
  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(D4, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(D4, LOW);
    }
    else if(messageTemp =="dht11") {
      Serial.println("dht read.....");
      read_dht(temperature,humidity);
      dtostrf(temperature, 6, 2, temp_string);
      client.publish("esp32/dht",temp_string);
        
    }
    else if(messageTemp == "moisture") {
      moisture_read();


    }
    else if(messageTemp == "moisture_TEST") {
      int random_moisture = random(0,100);
      char moisture_test[5] = "none";
      itoa(random_moisture, moisture_test, 10);

      Serial.print("Publishing TEST moisture");
      Serial.println(moisture_test);
      client.publish("esp32/moisture_TEST",moisture_test);
      

      
    }
    else if(messageTemp == "light_TEST") {
      //int random_moisture = random(0,100);
      //char moisture_test[5] = "none";
      //itoa(random_moisture, moisture_test, 10);
      lux = light_sensor.readLightLevel();

      Serial.print("Publishing TEST light");
      Serial.println(lux);
      char lux_str[10] = {"0"};
      itoa(lux, lux_str, 10);
      delay(500);
      client.publish("esp32/light_TEST",lux_str);
      

      
    }
    else if(messageTemp == "dht_TEST") {
      int random_moisture = random(0,100);
      char moisture_test[5] = "none";
      itoa(random_moisture, moisture_test, 10);

      Serial.print("Publishing TEST dht");
      Serial.println(moisture_test);
      client.publish("esp32/dht_TEST",moisture_test);
      

      
    }
    else if(messageTemp == "temp_TEST") {
      int random_moisture = random(0,100);
      char moisture_test[5] = "none";
      itoa(random_moisture, moisture_test, 10);

      Serial.print("Publishing TEST temp");
      Serial.println(moisture_test);
      client.publish("esp32/temp_TEST",moisture_test);
      

      
    }
    else if(messageTemp == "pump_TEST") {
      int random_moisture = random(0,100);
      char moisture_test[5] = "none";
      itoa(random_moisture, moisture_test, 10);

      Serial.print("Publishing TEST pump");
      Serial.println(moisture_test);
      client.publish("esp32/moisture_TEST",moisture_test);
      

      
    }
    
  }
}


void setup() {
  Serial.begin(115200);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  //Initializing sensors
  light_sensor.begin();

  if (light_sensor.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Advanced begin"));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }





  pinMode(D4, OUTPUT);
  pinMode(MOISTURE_PIN, INPUT);
}



void reconnect() {
  // Loop until we're reconnected

String clientId = "ESP8266Client - MyClient";
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqtt_server)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");  
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
