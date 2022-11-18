#include "Sensores.h"
#include <DFRobot_DHT11.h>
#include "humbrales.h"

DFRobot_DHT11 DHT;
//////////// Sensor de luz////////////
void leerLuz(void) {
  cantluz = analogRead(photocellPin);
  Serial.print("Sensor de luz:");
  Serial.println(cantluz);
  encenderLampara();  
  delay(1000);
}
////////////////////////////////////
void leerTemperatura() {

  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  temperatura = DHT.temperature;
  Serial.print(" hum:");
  Serial.println(DHT.humidity);
  humedad = DHT.humidity;

  loopHumbrales();
}