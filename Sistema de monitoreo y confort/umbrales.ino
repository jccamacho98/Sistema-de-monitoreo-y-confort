#include "humbrales.h"

void setupHumrales() {

  pinMode(ledUmbralHigh, OUTPUT);
  pinMode(ledUmbralow, OUTPUT);
  pinMode(ledTemIdeal, OUTPUT);
  pinMode(lampara, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

//funcion para relizar acciones al cruzar ciertos humbreles de temperatura
void loopHumbrales() {

  if (temperatura > umbral_high) {

    digitalWrite(ledUmbralHigh, HIGH);  //led rojo
    digitalWrite(ledUmbralow, LOW);
    digitalWrite(ledTemIdeal, LOW);


  } else if (temperatura < umbral_low) {
    digitalWrite(ledUmbralow, HIGH);  // led azul
    digitalWrite(ledUmbralHigh, LOW);
    digitalWrite(ledTemIdeal, LOW);
   
  } else {
    digitalWrite(ledUmbralow, LOW);
    digitalWrite(ledUmbralHigh, LOW);
    digitalWrite(ledTemIdeal, HIGH);  //led verde
    
  }
}
///////////////////////////////////////
void encenderLampara() {
  if (cantluz >= umbralLuz) {
    digitalWrite(lampara, HIGH);
  } else {
    digitalWrite(lampara, LOW);
  }
}
///////////////////////////////////////