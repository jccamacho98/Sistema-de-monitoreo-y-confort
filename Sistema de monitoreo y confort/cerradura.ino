#include <Keypad.h>
#include <LiquidCrystal.h>
#include "AsyncTaskLib.h"
#include <Average.h>
#include "configurarESP32.h"
#include "Sensores.h"
#include "humbrales.h"

AsyncTask asyncTaskTemperatura(5000, true, leerTemperatura);
//////////////////////// Fotorreistencia //////////////////
AsyncTask asyncTaskFotorresistencia(1000, true, leerLuz);

#define ledAmarillo 12
#define ledVerde 13
#define ledRojo 14

void opciones();
int num_intentos = 0;    //numero de intetos del usuario
bool resultado = false;  //estado de la comparacion de las cadenas contraseña ingresada y contraseña

String opcionesConfort = "";  //variable para leer las opciones dentro del sistema de monitoreo
bool salirConfort = false;    //variable para salir del sitema de confort

void setup() {
  ////configuramos
  setupConfigurarESP32();
  setupHumrales();
  //////////////////////////
  Serial.begin(115200);

  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  digitalWrite(ledAmarillo, HIGH);
  digitalWrite(ledRojo, HIGH);
  digitalWrite(ledVerde, HIGH);
  delay(3000);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde, LOW);
  /////////tareas asincronas /////////////////
  asyncTaskTemperatura.Start();       //leer temperatura
  asyncTaskFotorresistencia.Start();  //sensor de luz
}
//////////////////////        funciones      ////////////////////////////7
void pedir_clave();
void validar_clave();
//////////////////////////////////        void loop    /////////////////////////////
void loop() {
  if (resultado == false) {
    loopConfigurarESP32();
    if (num_intentos < 3 && obtener_contrasena.length() > 0)
      validar_clave();
    if (num_intentos == 3) {
      digitalWrite(ledRojo, HIGH);

      Terminal.print("Bloqueado");
      num_intentos = 0;
      delay(10000);
      digitalWrite(ledRojo, LOW);
    }
  } else {

    Terminal.print("Clave valida");
    delay(3000);

    Terminal.print("Sistema Desbloqueado");
    digitalWrite(ledVerde, HIGH);
    delay(3000);
    while (salirConfort == false) {
      opciones();
      asyncTaskTemperatura.Update();
      asyncTaskFotorresistencia.Update();
    }
    //Reiniciamos las variables
    salirConfort = false;
    obtener_contrasena = "";
    num_intentos = 0;
    digitalWrite(ledVerde, LOW);
  }
}
////////////////////////////////////////////////////////////
void validar_clave() {

  int comparacion = contrasena.compareTo(obtener_contrasena);
  if (comparacion == 0)
    resultado = true;
  else {
    digitalWrite(ledAmarillo, HIGH);
    if (num_intentos < 2)
      Terminal.print("Intente de nuevo");
    num_intentos++;
    resultado = false;
    delay(3000);
    digitalWrite(ledAmarillo, LOW);
  }
  obtener_contrasena = "";
  Serial.println(num_intentos);
}
///funcion para realizar acciones cuando el sistema esta desbloqueado (salir del sistema , consultar variables)
void opciones() {
  Dabble.processInput();
  if (Terminal.available() != 0) {
    while (Terminal.available() != 0) {
      opcionesConfort = Terminal.readString();
    }
  }

  if (opcionesConfort.compareTo("salir") == 0){
    salirConfort = true;
    resultado = false;
    digitalWrite(18, LOW);
    digitalWrite(19, LOW);
    digitalWrite(21, LOW);
    digitalWrite(25, LOW);
    opcionesConfort = "";
    Terminal.print("Saliendo del sistema,Bye");
  } else if (opcionesConfort.compareTo("temperatura") == 0) {
    Terminal.print("La temperatura en grados celcius es");
    Terminal.print(temperatura);
    opcionesConfort = "";
  } else if (opcionesConfort.compareTo("humedad") == 0) {
    Terminal.print("La humedad en % es");
    Terminal.print(humedad);
    opcionesConfort = "";
  }
}