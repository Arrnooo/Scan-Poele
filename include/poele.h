#ifndef POELE_H
#define POELE_H

#include <SoftwareSerial.h>

// Déclaration de l'objet pour la communication série avec le poêle
extern SoftwareSerial StoveSerial;

extern uint8_t loc;
extern uint8_t locCheksum;

// Fonctions de gestion du poêle
void setup_poele();
void checkStoveReply();
void getState(uint8_t loc, uint8_t param);

#endif