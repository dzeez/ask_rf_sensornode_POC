// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include "DHT.h"
#include <stdlib.h>

#define DHTPIN 3
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

RH_ASK driver;

void setup()
{
    pinMode(2, OUTPUT);
  digitalWrite(2,HIGH);
  pinMode(4, OUTPUT);
  digitalWrite(4,LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5,LOW);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
    Serial.begin(115200);	  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    else Serial.println("driver initialized");
    
    dht.begin();
}

void loop()
{
   // const char *msg = "hello";
   char buffer[10];
   char *msg = dtostrf(dht.readTemperature(true),5,2,buffer);

    driver.send((uint8_t *)msg, strlen(msg));
    Serial.print("sending ");
    Serial.println(msg);
    driver.waitPacketSent();
    delay(2000); //for dht
}
