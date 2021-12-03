#include <Wire.h>

#define one_player 8
#define two_player 7
#define tilt 10
#define buzzer 9

int Time_clock = 0;
int startMatchTime = 0, endMatchTime = 0;
int check_tilt = 0;
int bottone = 0, bottone2 = 0;
//long durata = 0, cm = 0;
int one_state = 0, two_state = 0; //per rilevare se bottone one e two    sono premuti o rilasciati
int which_player = 0; //se = 0 --> nessun giocatore selezionato|
int match_status = 0; /* se = 0 --> premi un bottone per iniziare
                         se = 1 --> scegli un numero di giocatori
                         se = 2 --> match in esecuzione con 1 player
                         se = 3 --> match in esecuzione con 2 player
                         se = 4 --> punto player 1
                         se = 5 --> punto player 2
                         se = 6 --> match conluso e presentazione punteggio con un solo player
                         se = 7 --> match conluso e presentazione punteggio con due player*/

int player1Punti = 0, player2Punti = 0;
int button_check() {

    int b = 0;
    one_state = digitalRead(one_player);
    if (one_state == HIGH) {

        b = 1;
    }

    two_state = digitalRead(two_player);
    if (two_state == HIGH) {
        // bottone = 2;

        b = 2;
    }
    // Serial.println(b);

    return b;
}

/*int distanza (){
          digitalWrite(trigPin, HIGH);
        delayMicroseconds(1);
        digitalWrite(trigPin, LOW);

        durata = pulseIn(EchoPin, HIGH);
        cm = (durata / 58.31);
        return cm;
}*/


void send_opcode(int op) {

    Wire.beginTransmission(4);
    Wire.write(op);
    Wire.endTransmission();
}

void setup() {

    Wire.begin(4);
    Serial.begin(9600);
    pinMode(one_player, INPUT);
    pinMode(two_player, INPUT);
    pinMode(tilt, INPUT);
    digitalWrite(tilt, HIGH);
    pinMode(buzzer, OUTPUT);
}

void loop() {

    Time_clock = (millis() / 1000);
    Serial.println(Time_clock);
    //Serial.println(match_status);
    
    switch (match_status) {

        case 0: {
            send_opcode(0);
            int r = button_check();
            switch (r) {
                case 1:
                case 2:
                    match_status++;
                    delay(1000);
            }
            break;
        }

        case 1: {
            send_opcode(1);
            int r = button_check();
            switch (r) {
                case 1: {
                    which_player = 1;
                    match_status++;
                    delay(1000);
                    break;
                }

                case 2: {
                    which_player = 2;
                    match_status++;
                    delay(1000);
                    break;
                }
            }
            break;
        }

        case 2: {
            if (startMatchTime == 0) {

                startMatchTime = Time_clock;
                endMatchTime = Time_clock + 3600;
            }

            send_opcode(2);
            int val = digitalRead(tilt);
            if (val == HIGH) {
                send_opcode(4);
                tone(buzzer, 80, 1000);
                delay(2000);
            }

            if (Time_clock >= endMatchTime) {
                if (which_player == 2) {

                    match_status++;
                    startMatchTime = 0;
                } else {

                    send_opcode(6);
                    match_status = 6;
                }
            }
            break;
        }

        case 3: {
            if (startMatchTime == 0) {

                startMatchTime = Time_clock;
                endMatchTime = Time_clock + 3600 3;
            }

            send_opcode(3);
            int val = digitalRead(tilt);

            if (val == HIGH) {

                send_opcode(5);
                tone(buzzer, 80, 1000);
                delay(2000);
            }
            if (Time_clock >= endMatchTime) {

                send_opcode(7);
                match_status = 7;
            }
            break;
        }            
    }
}