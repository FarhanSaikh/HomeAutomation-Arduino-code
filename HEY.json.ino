//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
 
#include <SimpleDHT.h>

// Set these to run example.
#define FIREBASE_HOST "homeautomation-72a40.firebaseio.com"
#define FIREBASE_AUTH "Y7PZn8qZQ1mqqjY3dcBuEAQzAqqfU8wUzO6onkoY"
#define WIFI_SSID "farhan"
#define WIFI_PASSWORD "farhan12345"

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




