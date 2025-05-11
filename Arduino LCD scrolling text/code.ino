#include <LiquidCrystal.h>

LiquidCrystal lcd(8,9,4,5,6,7); // rs, en, d4, d5, d6, d7

const int botao1 = 13;
const int botao2 = 12;

// Representação do texto com caracteres especiais (ê = 130)
byte textoUP[] = {
  ' ', ' ', ' ', 'S', 161, 'm', 'b', 'o', 'l', 'o', ' ', 'd', 'e', ' ',' ',' '
};
byte textoDown[] = {
   ' ',' ',' ',' ',' ','A','m','p',130,'r','e','s',' ',' ',' ',' '
}; 
int tamanhoTextoUP = sizeof(textoUP);
int tamanhoTextoDown = sizeof(textoDown);
int indiceUP = 0;
int indiceDown = 0;
bool direita = true;

void setup() {
  pinMode(botao1, INPUT);
  pinMode(botao2, INPUT);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  int btn1 = digitalRead(botao1);
  int btn2 = digitalRead(botao2);

  if (btn1 == LOW && btn2 == HIGH) {
    direita = true;
  } else if (btn1 == LOW && btn2 == LOW) {
    direita = false;
  } else {
    return;
  }

  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++) {
    int posUP = (indiceUP + i) % tamanhoTextoUP;
    byte caractereUP = textoUP[posUP];

    if (caractereUP < 128) {
      lcd.print((char)caractereUP);
    } 
    else {
      lcd.write(caractereUP);
    }
  }
  lcd.setCursor(0,1);
  for (int i = 0; i < 16; i++) {
    int posDown = (indiceDown + i) % tamanhoTextoDown;
    byte caractereDown = textoDown[posDown];

    if (caractereDown < 128) {
      lcd.print((char)caractereDown);
    } 
    else {
      lcd.write(caractereDown);
    }
  }
  

  if (direita) {
    indiceUP++;
    indiceDown++;
    if (indiceUP >= tamanhoTextoUP) {
      indiceUP = 0;
    }
    if(indiceDown >= tamanhoTextoDown){
    	indiceDown = 0;
    }
  } 
  else 
  {
    indiceUP = (indiceUP==0) ? tamanhoTextoUP-1 : indiceUP-1;
    indiceDown = (indiceDown==0) ? tamanhoTextoDown-1 : indiceDown-1;
  }

  delay(300); // ← só aqui!
}

