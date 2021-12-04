#include <LiquidCrystal.h>
#include <Wire.h>
#include <stdio.h>
#include <stdlib.h>

bool iniziato = false;
bool iniziato2 = false;
bool controllo = true;
int tempo = 30; //durata partita
int tempo2 = tempo; 
int Time_clock = 0, start, end;
int startMatchTime = 0, endMatchTime = 0;
int num = 0;
int player1 = 0, player2 = 0; 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); 
int  Time_clock;
bool firstTimePlayer1 =true;
bool firstTimePlayer2 =true;


void setup() {
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  lcd.clear();
  lcd.begin(16, 2);
}
 


void loop() {
    
    TimeClock = (millis() / 1000);

}

int old=-1;
void receiveEvent(int howMany){

int tmp=-2;
  int currentime=30;
while(Wire.available()){

    currenttime= end-Time_clock;

    num = Wire.read();
      if(iniziato2 == true){
      lcd.setCursor(0, 2);
      lcd.print("     Timer:");
      lcd.print(currentime); //secondi player 1
      lcd.setCursor(0,1);
      }
  
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
      lcd.print("Giocatori (1/2)");
      lcd.setCursor(0,1);
      break;
      case 2:
  if(firstTimePlayer1){

      firstTimePlayer1=!firstTimePlayer1;
      start= Time_clock;
      end= Time_clock+ tempo;

  }
      iniziato = true;
      if(player1>0){

      lcd.clear();
      lcd.print("Punteggio:");
      lcd.setCursor(0, 2);
      lcd.print(player1);
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
          if(firstTimePlayer2){

      firstTimePlayer2=!firstTimePlayer2;
      start= Time_clock;
      end= Time_clock+ tempo;

  }
      iniziato2 = true;
      if(player2>0){
      lcd.clear();
      lcd.print("Punteggio:");
      lcd.setCursor(0, 2);
      lcd.print(player2);
      lcd.setCursor(0,1);
      }else{
      lcd.clear();
      lcd.print("Tempo Iniziato!");
      lcd.setCursor(0, 2);
      lcd.print("Tocca al 2!");
      lcd.setCursor(0,1);
      }
        
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
      lcd.print("Punteggio:");
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

