#include "configurarESP32.h"

void leerTerm(String cadena);
int opcion = 0;

bool dataflag = 0;
void setupConfigurarESP32() {
  Serial.begin(115200);         // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("CarlosEsp32");  //set bluetooth name of your device
  Serial.println("Monitor iniciado");
  pinMode(13, OUTPUT);
}
//////////////////////////////
void loopConfigurarESP32() {
  Dabble.processInput();  //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  if (Terminal.available() != 0) {
    while (Terminal.available() != 0) {
      leerTerminal = Terminal.readString();
    }
  }

  if (leerTerminal.compareTo("menu") == 0) {
    menu();
    leerTerminal = "";
  }
}
///////////////////////////////////////7
void menu() {
  String opc = "";
  String Humed = "";
  String tem = "";
  String luz = "";

  Terminal.print("         menu  \n1-Ingresar al sistema\n2-Configurar Umbral_low\n3-Configurar Umbral_high\n4-Configurar Umbral Luz ");
  ///////////////////////////////////77
  Dabble.processInput();
  do {
    while (Terminal.available() != 0) {
      opc = Terminal.readString();
    }
    Serial.print(opc);
    Dabble.processInput();
  } while (Terminal.available() == 0);
  opc = Terminal.readString();
  //////////////////////////////////////////

  int opcion = opc.toInt();
  if (opc.length() != 0) {
    switch (opcion) {
      case 1:  //ingresar al sistema
        Terminal.print("Ingrese contraseña:");

        /////////////////////////////////////
        Dabble.processInput();
        do {
          while (Terminal.available() != 0) {
            obtener_contrasena = Terminal.readString();
          }
          // Serial.print(opc);
          Dabble.processInput();
        } while (Terminal.available() == 0);
        obtener_contrasena = Terminal.readString();
        break;
        ////////////////////////////////////////////////////////////////////////////////////////
      case 2:  //Umbral_low
        Terminal.print("Ingrese el Umbral_low de Temperatura:");
        ////////////////////////////////
        Dabble.processInput();
        do {
          while (Terminal.available() != 0) {
            Humed = Terminal.readString();
          }
          Dabble.processInput();
        } while (Terminal.available() == 0);
        Humed = Terminal.readString();
        //////////////////////////////
        umbral_low = Humed.toInt();
        Terminal.print("El valor de Umbral_low cambio a :");
        Terminal.println(umbral_low);
        break;
        //////////////////////////////////////////////////////////////////////////////////////
      case 3:  //Umbral high
        Terminal.print("Ingrese el Umbral_high de temperatura:");
        /////////////////////////////////////////////////////
        Dabble.processInput();
        do {
          while (Terminal.available() != 0) {
            tem = Terminal.readString();
          }
          Dabble.processInput();
          ;
        } while (Terminal.available() == 0);
        tem = Terminal.readString();
        //////////////////////////////////////////////////////7
        umbral_high = tem.toInt();
        Terminal.print("El valor de Umbral_high cambio a :");
        Terminal.println(umbral_high);
        break;
        /////////////////////////////////////////////////////////////////////////////////////
      case 4:  //Umbral Luz
        Terminal.print("Ingrese el Umbral de luz(0-4095):");
        ///////////////////////////////////////////7
        Dabble.processInput();
        do {
          while (Terminal.available() != 0) {
            luz = Terminal.readString();
          }
          Dabble.processInput();
        } while (Terminal.available() == 0);
        luz = Terminal.readString();
        ///////////////////////////////////////////
        if (luz.toInt() >= 0 || luz.toInt() <= 4095) {
          umbralLuz = luz.toInt();
          Terminal.print("El valor de Umbral de luz cambio a :");
          Terminal.println(umbralLuz);
        } else {
          Terminal.print("El valor no es valido");
        }
        break;
      default:
        Terminal.print("Opcion no valida");
        break;
    }
  }
}
//////////////////////////Funcion para leer los datos enviados por el usuario desde el celular///////////////////////
void leerTerm(String cadena) {
  Dabble.processInput();
  do {
    while (Terminal.available() != 0) {
      cadena = Terminal.readString();
    }
    Dabble.processInput();
  } while (Terminal.available() == 0);
  cadena = Terminal.readString();
}