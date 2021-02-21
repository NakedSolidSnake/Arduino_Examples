/*
  Sweep

  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Arduino.h>
#include <Servo.h>
#include <string.h>

typedef struct list
{
	int comandos[10];
	int qtde_com;
};

int pos = 0;
Servo servo_9;
int flag = 0;
unsigned long current = 0;
unsigned long time = 0;

list l;

void executa_lista(){
	for(int i = 0 ; i < l.qtde_com; i++){
      	Serial.print("comando: ");
      	Serial.println(l.comandos[i]);
		servo_9.write(l.comandos[i]);
      	delay(1000);
	}
}

void mostra_lista(void){
 	for(int i = 0 ; i < l.qtde_com; i++){
      	Serial.print("comando: ");
      	Serial.println(l.comandos[i]);
	}
}

void limpa_lista(void){
  l.qtde_com = 0;
}

void setup()
{
  servo_9.attach(9);
  Serial.begin(9600);

}

void loop()
{
  if(Serial.available() > 0)
  {
   	String s = Serial.readString();

   	if(strcmp("play", s.c_str()) == 0){
      Serial.println("Executando lista");
   		executa_lista();
   	}

    else if(strcmp("grava", s.c_str()) == 0){
      Serial.println("Grava...");
   	  if(l.qtde_com > 10){

   	   }else{
   		  l.comandos[l.qtde_com] = pos;
   		  l.qtde_com++;
   		  Serial.println(pos);
   	   }
   	}

    else if(strcmp("mostra", s.c_str()) == 0){
      Serial.println("Mostra");
   	  mostra_lista();
   	}

    else if(strcmp("limpa", s.c_str()) == 0){
      Serial.println("Limpa");
   	  limpa_lista();
   	}

    else if(strcmp("reset", s.c_str()) == 0){
      Serial.println("Reset");
   	  servo_9.write(92);
   	}

    else{
		pos = atoi(s.c_str());
    	if(pos > 0 || pos < 181){
    		servo_9.write(pos);
        	delay(15);
    	}
    }
  }

  current = millis();
  if((time + 1000) < current){
	  time = millis();
	  Serial.println(servo_9.read());
  }
}
