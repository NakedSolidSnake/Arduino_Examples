/*
 * Line Follower
 * Criadores: Bianca Moreira Matos Alves       RGM.: 132148-3
 *            Cristiano Silva de Souza         RGM.: 1629524-2
 *            Lia Leticia Alves Leopoldino     RGM.: 131645-1
 * Data: 21/05/2016
 * Descrição: Este programa consiste em controlar um Tanque
 * desenvolvido pelos criadores onde é possível controlá-lo
 * via comunicação bluetooth, assim como operar de forma autonoma
 * para o modo seguidor de linha.
 */

#include <Arduino.h>

 /* Definição de IO's Led's  e tecla */
#define LED_VD 7
#define LED_AM 6
#define LED_VM 5
#define BT     4

/* Definição de IO's Motores  */
#define M1_F 9
#define M1_R 12
#define M2_F 11
#define M2_R 10

#define TEMPO 25

/* Definições de Variaveis globais */
int RX;   //Variavel para recepção serial
bool standby = false;           /*
                                  Variavel para controlar o estado Ligado e Desligado
                                  standby = true -> esta no modo de espera
                                  standby = false -> modo de operação
                                */
bool line_or_control = false;   /*
                                   Variavel para mudar o modo de operação do Tanque
                                   line_or_control = false; -> modo controle remoto
                                   line_or_control = true; -> modo seguidor de linha
                                 */

bool stop_line = false;       // Variavel de controle para partir o seguidor de linha

/*
  Protocolo para controle
  Caracteres de recepção
  o - alterna estado standby modo controle
  m - alterna estado modo controle modo linha
  a - habilita seguidor de linha
  f - movimenta motores para frente
  r - movimenta motores para tras
  e - movimenta motor esquerdo
  d - movimenta motor direito

  Caracteres de transmissao
  d - atualiza imagem direita
  e - atualiza imagem esquerda
  f - atualiza imagem frente
  n - solicita estado standby
  s - solicita estado modo controle
*/


/* Configuraçãoes Iniciais */
void setup() {
  //Configura Leds

  //Configura Controle de Motores

  //Configura Botao

  //Configura Serial

  tk_state();
}

void loop() {
  //Alterna estado verificando se tecla foi pressionada somente se conectado
  if(!digitalRead(BT)){
    delay(10);
    while(!digitalRead(BT));
    delay(100);
    //Solicita conexão com SW mestre
    if(!standby){
        Serial.write('n');
    }

    else{
       Serial.write('s');
    }
  }

  if(Serial.available() > 0){
    RX = Serial.read();
  }

  //Modo ligado ou standby
  if(RX == 'O' || RX == 'o'){
      tk_state();
      RX = 0;
  }

  //Alterna modos de controle e seguidor de linha
  else if((RX == 'M' || RX == 'm') && (!standby)){
      tk_mode();
      RX = 0;
  }
  //Habilita seguidor de linha
  else if(RX == 'a'){
    stop_line = true;
  }

  //Modo Controle Remoto
  if(!standby && !line_or_control){
    remote_mode();
  }
  //Modo Seguidor de Linha
  else if(!standby && line_or_control){
    line_mode();
  }
  RX = 0;
}

void tk_state(void){
  //Estado ligado
  if(standby){
    standby = false;
    line_or_control = false;
    digitalWrite(LED_VD, HIGH);
    digitalWrite(LED_VM, LOW);
    digitalWrite(LED_AM, LOW);
  }
  // Estado desligado
  else{
    standby = true;
    digitalWrite(LED_VD, LOW);
    digitalWrite(LED_VM, HIGH);
    digitalWrite(LED_AM, LOW);
  }
}

void tk_mode(void){
  /* Seguidor de linha */
  if(line_or_control){
    line_or_control = false;
    digitalWrite(LED_VD, HIGH);
    digitalWrite(LED_AM, LOW);
  }
  /* modo controle remoto */
  else{
    line_or_control = true;
    digitalWrite(LED_VD, LOW);
    digitalWrite(LED_AM, HIGH);
  }
}

void remote_mode(void){
    // Envia comando motores para frente
    if(RX == 'F' || RX == 'f'){
      tk_frente();
    }
    //Envia comando motores para tras
    else if(RX == 'R' || RX == 'r'){
       tk_re();
    }
    //Envia comando motores para direita
    else if(RX == 'D' || RX == 'd'){
      tk_dir();
    }
    //Envia comando motores para esquerda
    else if(RX == 'E' || RX == 'e'){
      tk_esq();
    }

    int i;
    for(i = 9; i < 13; i++){
      digitalWrite(i, LOW);
    }
    RX = 0;
}

void line_mode(void){
  // Verifica se variavel stop_line esta ativa iniciar modo seguidor de linha
   if(stop_line){
    //Serial.println("Line mode");
   int s1 = analogRead(A0);
   int s2 = analogRead(A1);

   if((s1 < 200) && (s2 < 200)){
      Serial.write('f');
      tk_frente();
      tk_stop();
   }
   //Verifica se os sensores estao em superficie totalmente preta
   if((s1 > 200) && (s2 > 200)){
      stop_line = false;
      tk_stop();
   }
   //Verifica se o sensor esquerda esta em superficie preta
   if(s1 > 200){
      Serial.write('d');
      tk_dir();
      tk_stop();
   }
   //Verifica se o sensor direita esta em superficie preta
   if(s2 > 200){
      Serial.write('e');
      tk_esq();
      tk_stop();
   }
 }
}


}

//Função de temporização
void my_delay(){
  if(line_or_control)
    delay(TEMPO);
  else
    delay(TEMPO*6);
}

