#include <Arduino.h>
#include "wifi_mqtt.h"
#include "poele.h"
#include "ota.h"
#include "config.h"

void setup()
{
#ifdef DEBUG
  Serial.begin(115200);
#endif
  setup_wifi();
  setup_mqtt();
  setup_poele();
  setup_ota();
}

void loop()
{
  check_wifi_connection();
  handle_mqtt();
  handle_ota();
  getState(loc, emp);
  if (emp >= 255)
  {
    emp = 0;
  }
  else
  {
    emp++;
  }
  //delay(delayPublish);
}