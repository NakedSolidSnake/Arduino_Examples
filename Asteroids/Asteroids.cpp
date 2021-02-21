#include <Arduino.h>
#include <LiquidCrystal.h>

#define LCD_RS_PIN	8
#define LCD_EN_PIN	9
#define LCD_D4_PIN	10
#define LCD_D5_PIN	11
#define LCD_D6_PIN	12
#define LCD_D7_PIN	13

#define LCD_SIZE	16

static LiquidCrystal lcd(LCD_RS_PIN,
		LCD_EN_PIN,
		LCD_D4_PIN,
		LCD_D5_PIN,
		LCD_D6_PIN,
		LCD_D7_PIN);

int vel = 100;
int pxnave;
int pynave;
int pxaste;
int pyaste;
int pxenergia;
int pyenergia;
int pxtiro;
int pytiro;

bool game, vtiro, vpilha;
int pontos;
double venergia;
int vtela = 0;

byte nave[8] = {
		B11000,
		B01100,
		B01110,
		B01111,
		B01110,
		B01100,
		B11000
};

byte asteroide[8] = {
		B00000,
		B00100,
		B01110,
		B10111,
		B11101,
		B01110,
		B00100,
		B00000
};

byte explosao[8] = {
		B10001,
		B10101,
		B01010,
		B10100,
		B00101,
		B01010,
		B10101,
		B10001
};

byte energia[8] = {
		B01110,
		B11011,
		B10001,
		B10101,
		B10101,
		B10101,
		B10001,
		B11111
};

byte tiro[8] = {
		B00000,
		B00000,
		B00000,
		B00111,
		B00111,
		B00000,
		B00000,
		B00000
};

void desenhaNave(int px, int py);
void desenhaAsteroide(int px, int py);
void desenhaEnergia(int px, int py);
void desenhaTiro(int px, int py);
void desenhaExplosaoNave(int px, int py);
void desenhaExplosaoAsteroide(int px, int py);
void painel(int px);
void reset();
void tela(int cond);

const int btcima = 2;
const int btbaixo = 3;
const int bttiro = 4;

void setup() {
	pxnave = 0;
	pynave = 0;
	pyaste = 0;
	pxenergia = 0;
	pyenergia = 0;
	pytiro = 0;

	vtela = 0;

	pxtiro = -1;
	pxaste = 12;

	venergia = 100;
	lcd.createChar(1, nave);
	lcd.createChar(2, asteroide);
	lcd.createChar(3, explosao);
	lcd.createChar(4, energia);
	lcd.createChar(5, tiro);

	lcd.begin(16, 2);
	lcd.clear();

	game = true;
	vtiro = vpilha = false;

	pinMode(btcima, INPUT);
	pinMode(btbaixo, INPUT);
	pinMode(bttiro, INPUT);

}

void loop() {
	if(game){
		venergia -= 0.25;
		if(venergia <= 0){
			game = 0;
			desenhaExplosaoNave(pxnave, pynave);
			vtela = 2;
		}
		lcd.clear();
		painel(13);

		if(digitalRead(btcima) == 1){
			pynave = 0;
		}

		if(digitalRead(btbaixo) == 1){
			pynave = 1;
		}

		if(digitalRead(bttiro) == 1){
			pxtiro = 1;
			vtiro = true;
			pytiro = pynave;
		}

		pxaste -= 1;
		desenhaNave(pxnave, pynave);
		desenhaAsteroide(pxaste, pyaste);
		if(vtiro){
			desenhaTiro(pxtiro, pytiro);
			pxtiro += 1;
		}

		if(pxaste < 0){
			pxaste = 12;
			pyaste = (random(0, 2));
		}

		if(pxtiro > 16){
			vtiro  = false;
			pxtiro -= 1;
		}

		//colisão do tiro com o asteroide
		if(((pxtiro == pxaste + 1) && (pytiro == pyaste)) ||
			((pxtiro == pxaste) && (pytiro == pyaste))){
			vtiro =  false;
			pxtiro = -1;
			desenhaAsteroide(pxaste, pyaste);
			pyaste = random(0, 2);
			pxaste = 12;
			pontos += 2;

			if(pontos > 100){
				game = 0;
				vtela = 1;
			}
		}

		//colisão da nave com o asteroide
		if((pxnave == pxaste) && (pynave == pyaste)){
			game = 0;
			desenhaExplosaoNave(pxnave, pynave);
			vtela = 2;
		}

		if(!vpilha){
			if(random(0, 60) > 58){
				pxenergia = 12;
				vpilha = true;
				pyenergia = random(0 , 2);
			}
		}else{
			pxenergia -= 1;
			desenhaEnergia(pxenergia, pyenergia);
			if(((pxnave == pxenergia + 1) && (pynave == pyenergia)) ||
						((pxnave == pxenergia) && (pynave == pyenergia))){
				vpilha = false;
				pxenergia = -1;
				venergia = 100;
			}
		}

		delay(vel);

	}else{
		tela(vtela);
		if(digitalRead(bttiro) == 1){
			reset();
		}

	}
}

void desenhaNave(int px, int py){
	lcd.setCursor(px, py);
	lcd.write(1);
}

void desenhaAsteroide(int px, int py){
	lcd.setCursor(px, py);
	lcd.write(2);
}

void desenhaEnergia(int px, int py){
	lcd.setCursor(px, py);
	lcd.write(4);
}

void desenhaTiro(int px, int py){
	lcd.setCursor(px, py);
	lcd.write(5);
}

void desenhaExplosaoNave(int px, int py){
	lcd.clear();
	lcd.setCursor(px, py);
	lcd.write(3);
	delay(1000);
	lcd.clear();
}


void desenhaExplosaoAsteroide(int px, int py){
	lcd.setCursor(px, py);
	lcd.write(3);
	delay(1000);
	lcd.clear();
}

void reset(){
	pontos = 0;
	venergia = 100;
	game = true;
	vtela = 0;
}

void painel(int px){
	lcd.setCursor(px, 0);
	lcd.print(pontos);
	lcd.setCursor(px, 1);
	lcd.print(venergia);
}

void tela(int cond){
	if(cond < 1){
		lcd.setCursor(2, 0);
		lcd.print("Asteroides");
		lcd.setCursor(0, 1);
		lcd.print("Pressione Tiro");

	}else{
		String txt ={ cond > 0 ? "GANHOU" : "PERDEU" };
		lcd.setCursor(9, 0);
		lcd.print("pts:");
		lcd.setCursor(13, 0);
		lcd.print(pontos);

		lcd.setCursor(1, 0);
		lcd.print(txt);
		lcd.setCursor(0, 1);
		lcd.print("Pressione Tiro");
	}
}

//void ganhou(){
//	lcd.setCursor(9, 0);
//	lcd.print("pts:");
//	lcd.setCursor(13, 0);
//	lcd.print(pontos);
//
//	lcd.setCursor(1, 0);
//	lcd.print("GANHOU");
//	lcd.setCursor(0, 1);
//	lcd.print("Pressione Tiro");
//}
//
