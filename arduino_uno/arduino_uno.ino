#include <AddicoreRFID.h>
#include <SPI.h>
#include <string.h>
#define MAX_LEN 16

AddicoreRFID myRFID; // creamos el objeto AddicoreRFID para controlar el modulo RFID

//////////////////////////////////////////////////////
//CONFIGURAMOS LOS PINES DEL RFID
//////////////////////////////////////////////////////
const int chipSelectPin = 10;
const int resetPin = 5;

void setup() {
  Serial.begin(9600);                       //Iniciamos la comunicacion Serial
  //while(!Serial){}
  //Serial.println("Serial Inicializado");
  SPI.begin();                              //Iniciamos la libreria SPI
  pinMode(chipSelectPin,OUTPUT);            //Configuramos el pin 2 como salida para activar el modulo RFID
  digitalWrite(chipSelectPin,LOW);          //Activamos el modulo RFID
  pinMode(resetPin,OUTPUT);                 //Configuramos el pin 9 como salida para resetear el modulo RFID
  digitalWrite(resetPin,HIGH);          
  myRFID.AddicoreRFID_Init();

}

void loop() {
  unsigned char status;
  unsigned char str[MAX_LEN];
  String code_id = "";
  str[1] = 0x4400;
  status = myRFID.AddicoreRFID_Request(PICC_REQIDL,str);


  
  //PROCEDEMOS A LEER EL CODIGO DE LA TARJETA 
  status = myRFID.AddicoreRFID_Anticoll(str);
  if (status == MI_OK){
    //Serial.println("El numero de la tarjeta es: ");
    for (int i = 0; i < 4; i++){
      
      //Serial.print(str[i]);
      code_id += String(str[i]);
      if(i==3){
          Serial.println(code_id); 
          myRFID.AddicoreRFID_Halt();
          delay(500);
          
        }
        
        
    }
    //Serial.println(); 
    
  }
  //Serial.println();
  


}


