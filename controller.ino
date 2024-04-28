#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

#define led 13;

String numData, strData;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Data diterima dari python: ");
  Serial.println(topic);

  String receivedMessage = "";
  for (int i = 0; i < length; i++) {
    receivedMessage += (char)message[i];
  }
  Serial.print("Pesan: ");
  Serial.println(receivedMessage);

  if (strcmp(topic, "/kalil/str") == 0) {
    strData = "String data : " receivedMessage ;
  } else if (strcmp(topic, "/kalil/num") == 0) {
    numData = "Numeric data : " receivedMessage;
  }

  delay(1000);
  digitalWrite(led, HIGH);
  Serial.println(strData);
  Serial.println(numData);
  delay(1000);
  digitalWrite(led, LOW);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Mencoba koneksi ke MQTT ...");
    if (client.connect("ESP32-Client")) {
      Serial.println("Koneksi ke MQTT Ssukses : ");
      client.subscribe("/kalil/num");
      client.subscribe("/kalil/str");
    } else {
      Serial.print("Koneksi ke MQTT gagal : ");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Mencoba koneksi Wi-fi...");
  }
  Serial.println("Koneksi Wi-fi berhasil");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  if (client.connect("ESP32-Client")) {
    Serial.println("Koneksi ke MQTT berhasil");
    client.subscribe("/kalil/num");
    client.subscribe("/kalil/str");
  } else {
    Serial.print("Koneksi ke MQTT gagal : ");
    Serial.println(client.state());
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
