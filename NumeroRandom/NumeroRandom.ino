/*

Número random

Practicas CAN con módulo MCP2515  https://github.com/moytech

Este programa envía un número random del 1 al 20. Se muestra en el Serial monitor.
Se envía por el protocolo CAN bus con ayuda del módulo MCP2515 y otro 
módulo MCP2515 recibe el número para mostrar su cuadrado.

Autor: Moytech
github: https://github.com/moytech
Programa: Número random
Fecha: Julio 2024

*/

#include <SPI.h>
#include <mcp2515.h>

#define CS 10
int numRandom;

struct can_frame datasend;
MCP2515 mcp2515(CS);                                        

void setup() 
{
  Serial.begin(9600);                                       //iniciar serial monitor
  Serial.println("Conexión CAN bus");                       //imprimir en serial monitor
  SPI.begin();                                              //iniciar SPI
  mcp2515.reset();                                          //reset MCP2515
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);                //configuración CAN bus
  mcp2515.setNormalMode();                                  //modo normal
}

void loop() 
{
  numRandom=random(1,21);                                   //número random
  datasend.can_id= 0x11;                                    //CAN id
  datasend.can_dlc= 4;                                      //4 bytes
  datasend.data[0]= numRandom;                              //número random en el byte [0];
  datasend.data[1]= 0x00;                                   //byte [1]
  datasend.data[2]= 0x00;                                   //byte [2]
  datasend.data[3]= 0x00;                                   //byte [3]
  mcp2515.sendMessage(&datasend);                           //enviar datos

  Serial.println("Número Random enviado: ");                //imprimir en serial monitor
  Serial.println(datasend.data[0]);                         //imprimir en serial monitor
  delay(5000);                                              //esperar 5 seg.

}
