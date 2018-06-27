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

// FirebaseRoom_ESP8266 is a sample that demo using multiple sensors
// and actuactor with the FirebaseArduino library.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <stdlib.h>



// Set these to run example.
#define FIREBASE_HOST "apple-tracker-e4b63.firebaseio.com"
#define FIREBASE_AUTH "token_or_secret"
#define WIFI_SSID "deepdive"
#define WIFI_PASSWORD "2427BC6248"

int led_pin = 13;
int button_pin = 14;
int wifi_pin = 4;
void setup() {
  
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(wifi_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  digitalWrite(led_pin, LOW);

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
  digitalWrite(wifi_pin, HIGH);
}

int poid = 0;

void loop() {
  int switchButton = digitalRead(button_pin);

  if(switchButton == HIGH) {
    poid = (rand() % 1000);
    Firebase.begin(FIREBASE_HOST);
    Firebase.setInt("stock/quantite", poid);
    if(Firebase.success()) {
      Serial.println("FireBase updated");
      digitalWrite(led_pin, HIGH);
      delay(2000);
    }
    //digitalWrite(led_pin, HIGH);
  } else{
    digitalWrite(led_pin, LOW);
  }
}
