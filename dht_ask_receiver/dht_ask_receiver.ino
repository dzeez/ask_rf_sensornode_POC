// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver(2000,6,3,2);

void setup()
{
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  //pinMode(5, INPUT);
    Serial.begin(115200);	// Debugging only
    if (!driver.init())
         Serial.println("init failed");
    else Serial.println("driver initialized");
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
	int i;//=3;

        digitalWrite(13, true); // Flash a light to show received good message
        // Message with a good checksum received, dump it.
        Serial.print("Got: ");
//        Serial.println((char*)buf);
        for (i = 0; i < buflen; i++)
        {
            Serial.print(char(buf[i]));
            //Serial.print(" ");
        }
        Serial.println("");
        digitalWrite(13, false);
    }
}
