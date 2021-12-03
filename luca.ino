#include <LiquidCrystal.h>
#include <Wire.h>
#include <stdio.h>
#include <stdlib.h>

bool iniziato = false;
bool iniziato2 = false;
bool controllo = true;
int tempo = 3600; //durata partita
int Time_clock = 0;
int startMatchTime = 0, endMatchTime = 0;
int num = 0;
int player1 = 0, player2 = 0; 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); 
  
void setup() {
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
   //impostiamo il numero di colonne ed il numero di righe di lcd  
  lcd.clear();
  lcd.begin(16, 2);
}
 
void loop() {
  if(iniziato2 == true && controllo == true)
    tempo = 3600;
  if(iniziato == true){
    tempo--;
    delay(1000);
  }
  Time_clock = (millis() / 1000);
  delay(100);
  lcd.setCursor(0,1);
}
int old=-1;
void receiveEvent(int howMany){

  
while(Wire.available()){
  
    num = Wire.read();
    if(old!=num){

    switch(num){
      case 0:
      lcd.clear();
      lcd.print("Premi un pulsante");
      lcd.setCursor(0, 2);
      lcd.print("per iniziare");
      lcd.setCursor(0,1);
      break;
      case 1:
      lcd.clear();
      lcd.print("Scegli il numero");
      lcd.setCursor(0, 2);
      lcd.print("di giocatori (1/2)");
      lcd.setCursor(0,1);
      break;
      case 2:
      iniziato = true;
      if(player1>0){

      lcd.clear();
      lcd.print("Punteggio:");
      lcd.setCursor(0, 2);
      lcd.print(player1);
      lcd.print("     Timer:");
      lcd.print(tempo); //secondi
      lcd.setCursor(0,1);
      }else{
      lcd.clear();
      lcd.print("Tempo Iniziato!");
      lcd.setCursor(0, 2);
      lcd.print("Tocca al 1!");
      lcd.setCursor(0,1);
      }

      break;
      case 3:
      iniziato2 = true;
      if(player2>0){
      lcd.clear();
      lcd.print("Punteggio:");
      lcd.setCursor(0, 2);
      lcd.print(player2);
      lcd.print("     Timer:");
      lcd.print(tempo); //secondi
      lcd.setCursor(0,1);
      }else{
      lcd.clear();
      lcd.print("Tempo Iniziato!");
      lcd.setCursor(0, 2);
      lcd.print("Tocca al 2!");
      lcd.setCursor(0,1);
      }
      
      controllo = false;
      break;
      case 4:
      lcd.clear();
      lcd.print("Il player 1");
      lcd.setCursor(0, 2);
      lcd.print("ha segnato!");
      lcd.setCursor(0,1);
      player1++;
      break;
      case 5:
      lcd.clear();
      lcd.print("Il player 2");
      lcd.setCursor(0, 2);
      lcd.print("ha segnato!");
      lcd.setCursor(0,1);
      player2++;
      break;
      case 6:
      lcd.clear();
      lcd.print("Tempo Finito");
      lcd.setCursor(0, 2);
      lcd.print("Punttegio:");
       lcd.setCursor(11, 2);
       lcd.print(player1);
      lcd.setCursor(0,1);
      break;
      case 7:
      lcd.clear();
      lcd.print("Tempo finito");
      lcd.setCursor(0, 2);

      if(player1==player2)
      lcd.print("Pareggio");
      if(player1>player2)
      lcd.print("Player1 ha vinto");
      if(player1<player2)
      lcd.print("Player2 ha vinto");
     
      lcd.setCursor(0,1);
      break;
    }
      
    }
 old=num;
  }
delay(100);
}

