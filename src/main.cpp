#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

#define SSID       "SSID"
#define PASSWORD   "PASSWORD"
#include "credentials.h"

// If something setup is wrong
void trap()
{
    Serial.println("Error\n");
    while(1);
}


// Setup connection settings
WiFiClient debug;
WiFiClient data;
static const IPAddress Debug_IP { 192, 168, 0, 13 };    //IP adress of your proxy Lorrys terminal
static const uint16_t Debug_port = 12345;               //Proxy debug port
static const uint16_t Data_port = 12346;                //Proxy data port


void setup() {
    Serial.begin(115200);

    // Connect to WiFi
    WiFi.begin(SSID, PASSWORD);
    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED) { 
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());


    // Connect to Lorris proxy
    Serial.println("Connecting to Lorris proxy\n");
    if (!debug.connect(Debug_IP, Debug_port)) {
        Serial.println("Can not connect to the debug server");
        trap();
    }
    if (!data.connect(Debug_IP, Data_port)) {
        debug.println("Can not connect to the data server");
        trap();
    }

    delay(3000);


    debug.println("Connected succesly to DEBUG\n");
    data.println("Connected succesly to DATA\n");
    Serial.println("Connected succesly to DEBUG and DATA\n");
}


void loop() {
    int runtime = millis()/1000;

    Serial.println(String("Running for: " + String(runtime) + " seconds"));
    debug.println(String("Running for: " + String(runtime) + " seconds"));

    data.println(String("WiFi strength: " + String(WiFi.RSSI()) ));    
    
    delay(1000);

}