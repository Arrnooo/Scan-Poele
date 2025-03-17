#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>  // Pour uint8_t, uint16_t, etc.

//#define DEBUG

// ===== Paramètres WiFi =====
#include "secrets.h"
/*
Créer un fichier secrets.h dans le dossier include avec les informations suivantes

#ifndef SECRETS_H
#define SECRETS_H

// Informations WiFi
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PWD"

#endif

*/

// ===== Paramètres MQTT =====
extern const char *mqtt_server;
extern const int mqtt_port;

// ===== Délais =====
const uint8_t delayPublish = 200;

// ===== Définition des pins =====
#define ENABLE_RX       D8
#define RX_PIN          D5
#define TX_PIN          D6

//Identifier et modifier si besoin les adresses ROM et RAM du poêle
// ===== Paramètres du poêle =====
#define ReadRAM         0x00
#define ReadROM         0x20

// ===== Définition du mode série logiciel =====
#define SERIAL_MODE SWSERIAL_8N2

#endif