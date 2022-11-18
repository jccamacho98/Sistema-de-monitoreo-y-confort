#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <DabbleESP32.h>


void configuracionEsp32();
void loopConfigurarESP32();
void setupConfigurarESP32();
//variables globales 
#ifndef _configurarESP32_h_
#define _configurarESP32_h_

extern String pass;
extern String Serialdata = "";
extern String contrasena = "123";
extern String obtener_contrasena = "";
extern String leerTerminal="";
///////////Umbrales////////////
//valores por defecto///
extern int umbral_low=20; 
extern int umbral_high=25;
extern int umbralLuz=2000;
#endif