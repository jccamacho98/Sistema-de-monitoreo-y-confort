
#ifndef _Sensores_h_
#define _Sensores_h_
#define DHT11_PIN 27 
//variables para guardar las lecturas de los sensores
extern int temperatura=0;
extern int humedad=0;
extern int cantluz=0;

extern const int photocellPin = 15;
extern const int ledPin = 50;
extern int outputValue = 0;

void leerLuz(void);
void leerTemperatura();
#endif
