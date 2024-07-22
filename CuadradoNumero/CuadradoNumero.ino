/*

Cuadrado de un número

Practicas CAN con módulo MCP2515  https://github.com/moytech

Este programa recibe un número random y muestra su cuadrado. Se muestra en el Serial monitor.
Se recibe por el protocolo CAN bus con ayuda del módulo MCP2515 y otro 
módulo MCP2515 envía el número random.

Autor: Moytech
github: https://github.com/moytech
Programa: Cuadrado de un número
Fecha: Julio 2024

*/

#include <SPI.h>
#include <mcp2515.h>

#define CS 10
int numeroRan;

struct can_frame datareceive;
MCP2515 mcp2515(CS);                                          

void setup() 
{
  Serial.begin(9600);                                         //iniciar serial monitor
  Serial.println("Conexión CAN bus");                         //imprimir en serial monitor
  SPI.begin();                                                //Iniciar SPI
  mcp2515.reset();                                            //reset MCP2515
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);                  //configuración CAN bus
  mcp2515.setNormalMode();                                    //modo normal
}

void loop() 
{
  if(mcp2515.readMessage(&datareceive)== MCP2515::ERROR_OK)
  {
    numeroRan= datareceive.data[0];                           //byte [0]
    Serial.print("El número random es: ");                    //imprimir en serial monitor
    Serial.println(numeroRan);                                //imprimir en serial monitor
    Serial.print("El cuadrado del número random es: ");       //imprimir en serial monitor
    Serial.println(numeroRan* numeroRan);                     //cuadrado
  }
}
