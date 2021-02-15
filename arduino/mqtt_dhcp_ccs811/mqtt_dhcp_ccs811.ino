#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <CCS811.h>

// WiFi configuration
#define WLAN_SSID       "PUT_YOUR_WLAN_SSID_HERE"
#define WLAN_PASS       "PUT_YOUR_WLAN_PASS_HERE"

// MQTT configuration
#define MQTT_SERVER      "PUT_YOUR_MQTT_SERVER_HERE"
#define MQTT_SERVERPORT  1883
#define MQTT_USERNAME    ""
#define MQTT_KEY         ""
#define MQTT_FEED_CO2   "iescelia/aula22/co2"
#define MQTT_FEED_TVOC  "iescelia/aula22/tvoc"

// WiFi connection
WiFiClient client;

// MQTT connection
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_USERNAME, MQTT_KEY);

// Feed to publish CO2
Adafruit_MQTT_Publish co2Feed = Adafruit_MQTT_Publish(&mqtt, MQTT_FEED_CO2);

// Feed to publish TVOC
Adafruit_MQTT_Publish tvocFeed = Adafruit_MQTT_Publish(&mqtt, MQTT_FEED_TVOC);

CCS811 sensor;

//----------------------------------------------

void connectWiFi();
void connectMQTT();
void initSensor();

//----------------------------------------------

void setup() {
  Serial.begin(115200);
  Serial.println("CO2 IES Celia");
  connectWiFi();
  connectMQTT();
  initSensor();
}

//----------------------------------------------

void loop() {
  // Wait a few seconds between measurements.
  delay(1000);

  if(sensor.checkDataReady() == false){
    Serial.println("Data is not ready!");
    return;
  }

  float co2 = sensor.getCO2PPM();
  float tvoc = sensor.getTVOCPPB();

  Serial.print("CO2: ");
  Serial.print(co2);
  Serial.print(" ppm\t");
  Serial.print("TVOC: ");
  Serial.print(tvoc);
  Serial.println(" ppb");
 
  co2Feed.publish(co2);
  tvocFeed.publish(tvoc);

  //sensor.writeBaseLine(0x847B);
  //delay cannot be less than measurement cycle
  //delay(1000);  
}

//----------------------------------------------

void initSensor() {
  // Wait for the chip to be initialized completely
  while(sensor.begin() != 0){
    Serial.println("Failed to init chip, please check if the chip connection is fine");
    delay(1000);
  }
 
  // eClosed      Idle (Measurements are disabled in this mode)
  // eCycle_1s    Constant power mode, IAQ measurement every second
  // eCycle_10s   Pulse heating mode IAQ measurement every 10 seconds
  // eCycle_60s   Low power pulse heating mode IAQ measurement every 60 seconds
  // eCycle_250ms Constant power mode, sensor measurement every 250ms
  sensor.setMeasCycle(sensor.eCycle_250ms);
}

//----------------------------------------------

void connectWiFi() {
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//----------------------------------------------

void connectMQTT() {
  if (mqtt.connected())
    return;

  Serial.print("Connecting to MQTT... ");
  while (mqtt.connect() != 0) {
       Serial.println("Error. Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);
  }
}
