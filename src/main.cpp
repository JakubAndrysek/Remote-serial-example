/**
 * Project:     BasicOTA for VSCode-PlatformIO
 * Doc:         https://github.com/JakubAndrysek/Remote-serial-example/blob/master/README.md
 * Proj URL:    https://github.com/JakubAndrysek/Remote-serial-example
 * Author:      Kuba Andrýsek
 * Created:     2020-5-15
 * Website:     https://kubaandrysek.cz
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

WiFiClient debug;
WiFiClient data;

// Setup connection
#define SSID       "WiFi_SSID"
#define PASSWORD   "WiFi_PASSWORD"
static const IPAddress Debug_IP { 192, 168, 0, 13 };    //IP adress of your PC with Lorris
static const uint16_t Debug_port = 12345;               //Proxy debug port
static const uint16_t Data_port = 12346;                //Proxy data port

// If something setup is wrong
void trap()
{
    Serial.println("Error\n");
    while(1);
}

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