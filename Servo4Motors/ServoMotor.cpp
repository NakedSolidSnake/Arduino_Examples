#include <Arduino.h>
#include <Servo.h>
#include <string.h>
#include <stdio.h>


#define SERVO_SHOULDER		9
#define SERVO_ELBOW			6
#define SERVO_BASE			5
#define SERVO_CLAW			3

typedef void (*Exec)(String &);

typedef struct motors
{
	int m1_pos;
	int m2_pos;
	int m3_pos;
	int m4_pos;
}motors_t;

typedef struct list
{
	motors_t m[10];
	int qtde_com;
};

typedef struct table
{
	const char *command;
	int nChars;
	Exec exec;
};

int pos = 0;
Servo servo_9;
Servo servo_6;
Servo servo_5;
Servo servo_3;

int flag = 0;
unsigned long current = 0;
unsigned long time = 0;

list l;

void executa_lista(String &arg);
void mostra_lista(String &arg);
void limpa_lista(String &arg);
void posicaoInicial(String &arg);
void set_Posicao(String &arg);
void le_Posicao(String &arg);
void grava_Posicao(String &arg);

static table t[] = {
		{.command = "play"  , .nChars = 4, .exec = executa_lista },
		{.command = "grava" , .nChars = 5, .exec = grava_Posicao },
		{.command = "estado", .nChars = 6, .exec = le_Posicao    },
		{.command = "mostra", .nChars = 6, .exec = mostra_lista  },
		{.command = "limpa" , .nChars = 5, .exec = limpa_lista   },
		{.command = "reset" , .nChars = 5, .exec = posicaoInicial},
		{.command = "servo" , .nChars = 5, .exec = set_Posicao   }
};

static int table_len = sizeof(t)/sizeof(t[0]);



void setup()
{
	servo_9.attach(9);
	servo_6.attach(6);
	servo_5.attach(5);
	servo_3.attach(3);
	Serial.begin(9600);
}

void loop()
{
	if(Serial.available() > 0)
	{
		String s = Serial.readString();

		for(int i = 0; i < table_len; i++){
			if(strncmp(t[i].command, s.c_str(),t[i].nChars) == 0){
				t[i].exec(s);
				break;
			}
		}
	}
}

void executa_lista(String &arg){
	Serial.println("Executando comandos...");
	for(int i = 0 ; i < l.qtde_com; i++){
		servo_9.write(l.m[i].m1_pos);
		servo_6.write(l.m[i].m2_pos);
		servo_5.write(l.m[i].m3_pos);
		servo_3.write(l.m[i].m4_pos);
		delay(1000);
	}
}

void mostra_lista(String &arg){
	Serial.println("Mostrando Lista...");
	for(int i = 0 ; i < l.qtde_com; i++){
		Serial.print("Servo 1: "); Serial.println(l.m[i].m1_pos);
		Serial.print("Servo 2: "); Serial.println(l.m[i].m2_pos);
		Serial.print("Servo 3: "); Serial.println(l.m[i].m3_pos);
		Serial.print("Servo 4: "); Serial.println(l.m[i].m4_pos);
	}
}

void limpa_lista(String &arg){
	Serial.println("Limpando lista...");
	l.qtde_com = 0;
}

void grava_Posicao(String &arg){
	Serial.println("Gravando...");
	if(l.qtde_com > 10){

	}else{
		l.m[l.qtde_com].m1_pos = servo_9.read();
		l.m[l.qtde_com].m2_pos = servo_6.read();
		l.m[l.qtde_com].m3_pos = servo_5.read();
		l.m[l.qtde_com].m4_pos = servo_3.read();
		l.qtde_com++;
	}
}

void le_Posicao(String &arg){
	Serial.print("servo:1:"); Serial.print(servo_9.read());Serial.print("\n");
	Serial.print("servo:2:"); Serial.print(servo_6.read());Serial.print("\n");
	Serial.print("servo:3:"); Serial.print(servo_5.read());Serial.print("\n");
	Serial.print("servo:4:"); Serial.print(servo_3.read());Serial.print("\n");
}

void posicaoInicial(String &arg){
	Serial.println("Posição Inicial...");
	servo_9.write(0);
	servo_6.write(0);
	servo_5.write(0);
	servo_3.write(0);
}

void set_Posicao(String &arg){
	String s = arg;

	char delim[] = ":";
	char str[s.length() + 1];
	s.toCharArray(str, s.length() + 1, 0);
	String string[5];

	char *ptr = strtok(str, delim);
	int i = 0;
	while(ptr != NULL)
	{
		string[i++] = ptr;
		ptr = strtok(NULL, delim);
	}

	int servo = atoi(string[1].c_str());
	int value = atoi(string[2].c_str());
	if((value >= 0 || value <= 180) && (servo >= 1 || servo <= 4))
	{
		Servo *s = nullptr;
		switch(servo){
		case 1:
			s = &servo_9;
			break;
		case 2:
			s = &servo_6;
			break;
		case 3:
			s = &servo_5;
			break;
		case 4:
			s = &servo_3;
			break;

		default:
			break;
		}

		int temp = s->read();
		if(temp > value){ //diminui
			for(int i = temp ; i >= value; i--){
				s->write(i);
				delay(10);
			}
		}else{ //aumenta
			for(int i = temp; i <= value; i++ ){
				s->write(i);
				delay(10);
			}
		}
	}
}
