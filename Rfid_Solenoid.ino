#include <RFID.h>
#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9
#define Relay 8

RFID rfid(SS_PIN,RST_PIN);

int serNum[5];
int cards[][5] = {
  {69,110,204,101,130}
};

bool access = false;

void setup(){

    Serial.begin(9600);
    SPI.begin();
    rfid.init();

    pinMode(Relay, OUTPUT);

    digitalWrite(Relay, LOW);
   
}

void loop(){
    
    if(rfid.isCard()){
    
        if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");
            
            for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }
        }
       if(access){
          Serial.println("Welcome!");
          digitalWrite(Relay, HIGH);
          delay(10000);
          digitalWrite(Relay, LOW);
           
      } else {
           Serial.println("Not allowed!"); 
            }        
    }
    rfid.halt();
}


