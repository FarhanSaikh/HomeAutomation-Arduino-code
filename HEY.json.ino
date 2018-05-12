

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
 
#include <SimpleDHT.h>

// Set these to run example.
#define FIREBASE_HOST "homeautomation-72a40.firebaseio.com"
#define FIREBASE_AUTH "Y7PZn8qZQ1mqqjY3dcBuEAQzAqqfU8wUzO6*****"
#define WIFI_SSID "ssidname"
#define WIFI_PASSWORD "password"

int pinDHT11 = 2;
SimpleDHT11 dht11;
void setup() {
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);



  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("LED_STATUS", 0);
  Firebase.set("AC STATUS", 0);
  

}

void loop() {
// get value
digitalWrite(D2, Firebase.getInt("AC STATUS"));
digitalWrite(D1, Firebase.getInt("LED_STATUS"));
sendtemp();

}
 void sendtemp()
{
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
    Firebase.set("Temperature",((int) temperature));
    Firebase.set("Humidity", ((int)humidity));
    

  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
  
  }




