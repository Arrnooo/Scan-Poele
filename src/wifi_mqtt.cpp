#include "mqtt_topics.h"
#include "wifi_mqtt.h"
#include "config.h"
#include "poele.h"

WiFiClient espPoele;
PubSubClient client(espPoele);

void setup_wifi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#ifdef DEBUG
  Serial.print("Connexion au WiFi...");
#endif
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
  }
#ifdef DEBUG
  Serial.println(" Connecté au WiFi");
#endif
}

void reconnect()
{
  while (!client.connected())
  {
    if (client.connect("espPoele"))
    {
      delay(100);
#ifdef DEBUG
      Serial.println("Connecté au MQTT");
#endif
    }
  }
}

void setup_mqtt()
{
  client.setCallback(callback);
  client.setServer(mqtt_server, mqtt_port);
  reconnect();
  client.subscribe(in_topic);
}

void check_wifi_connection()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    setup_wifi();
  }
}

void handle_mqtt()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}

void callback(char *topic, byte *payload, unsigned int length)
{
#ifdef DEBUG
  Serial.print("Message reçu [");
  Serial.print(topic);
  Serial.print("] ");
  for (uint8_t i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
#endif
  switch ((char)payload[1])  {
  case 1:
    loc = 0x00;
    break;
  case 2:
    loc = 0x20;
    break;
  }
}
