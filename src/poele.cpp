#include "mqtt_topics.h"
#include "config.h" // Inclure en premier pour avoir les définitions
#include "poele.h"
#include "wifi_mqtt.h" // Pour accéder à 'client'
#include <Arduino.h>

// Initialisation de la communication série vers le poêle
SoftwareSerial StoveSerial(RX_PIN, TX_PIN); // Utilise les pins définis dans config.h

char stoveRxData[2];
uint8_t loc = 0;
uint8_t locCheksum = 0;

void setup_poele()
{
  StoveSerial.begin(1200, SERIAL_MODE, RX_PIN, TX_PIN, false, 256);
  pinMode(ENABLE_RX, OUTPUT);
  digitalWrite(ENABLE_RX, LOW);
#ifdef DEBUG
  Serial.println("Poêle initialisé");
#endif
}

void checkStoveReply()
{
  digitalWrite(ENABLE_RX, HIGH);
  delay(80);
  uint8_t rxCount = 0;
  stoveRxData[0] = 0x00;
  stoveRxData[1] = 0x00;
  while (StoveSerial.available())
  {
    stoveRxData[rxCount] = StoveSerial.read();
    rxCount++;
  }
  digitalWrite(ENABLE_RX, LOW);
  if (rxCount == 2)
  {    
#ifdef DEBUG
    Serial.printf("Param=%01x value=%01x ", param, val);
#endif
    char dynamic_topic[50]; // Assurez-vous que la taille est suffisante pour contenir le topic
    snprintf(dynamic_topic, sizeof(dynamic_topic), "%s/%d", in_topic, loc);
    char message[2] = {stoveRxData[1], '\0'}; // Convertit le char en une chaîne de caractères
    client.publish(dynamic_topic, message, false);
  }
}

void getState(uint8_t loc, uint8_t param)
{
  locCheksum = loc;
  StoveSerial.write(loc);
  delay(1);
  StoveSerial.write(param);
  checkStoveReply();
  locCheksum = 0;
}