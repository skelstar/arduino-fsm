#include <Arduino.h>
#include <elapsedMillis.h>

void setup()
{
  Serial.begin(115200);
  Serial.printf("\n\nReady\n");
}

elapsedMillis sincePing;

void loop()
{
  if (sincePing > 2000)
  {
    sincePing = 0;
    Serial.printf("ping\n");
  }
}