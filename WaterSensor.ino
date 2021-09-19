// counter je brojac sekundi
int counter = 0;
// a je najmanji broj koji senzor ocitava kada ima vode
int analogReadLevel = 200;
int nemaVodeLED = 0;
// fNemaVodeLED se koristi kada nema vode, za oznacavanje da li su LED diode upaljene ili ugasene
int fNemaVodeLED = 0;
//nivoVode je nivo vode
int nivoVode = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);  
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT); 
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);

  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW); 
  digitalWrite(7,LOW);    
}

//////////////////////////////////
// Mijenja status LED Dioda kada nema vode
// Input: (int fNemaVodeLED) Status LED Dioda
// Output: (int) Status LED Dioda
//////////////////////////////////
int nemaVode(int fNemaVodeLED) {
  if(fNemaVodeLED == 0){
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    fNemaVodeLED = 1;
    return fNemaVodeLED;
   }
   else if(fNemaVodeLED == 1){
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    fNemaVodeLED = 0;
    return fNemaVodeLED;
   }
}

//////////////////////////////////
// Ocitava analogne portove za nivo vode
// Output: (int) nivo vode
//////////////////////////////////
int provjeraVode(){
  digitalWrite(7, HIGH);
  if(analogRead(1)>analogReadLevel){
          nemaVodeLED = 0;
          digitalWrite(7, LOW);
          Serial.println("Detektovano 1");
          return 6;
          }
   else if(analogRead(2)>analogReadLevel){
         nemaVodeLED = 0;
         digitalWrite(7, LOW);
         Serial.println("Detektovano 2");
         return 5;
          }
   else if(analogRead(3)>analogReadLevel){
          nemaVodeLED = 0;
          digitalWrite(7, LOW);
          Serial.println("Detektovano 3");
          return 4;
          }
   else if(analogRead(4)>analogReadLevel){
          nemaVodeLED = 0;
          digitalWrite(7, LOW);
          Serial.println("Detektovano 4");
          return 3;
          }
   else if(analogRead(5)>analogReadLevel){
          nemaVodeLED = 0;
          digitalWrite(7, LOW);
          Serial.println("Detektovano 5");
          return 2;
          }
   else{
         digitalWrite(7, LOW);  
         return 1;
          }
}

//////////////////////////////////
// Kontrolise sta se desava na razlicitim nivoima ocitanja vode
// Input (int nivoVode) nivo vode
//////////////////////////////////
void vodaLED(int nivoVode){

  switch (nivoVode){
      case 1:
        if(counter==60){
           fNemaVodeLED = 0;
           counter = 0;
           nemaVode(fNemaVodeLED);
           nemaVodeLED = 1;
        }
        break;

      case 2:
        digitalWrite(2,HIGH);
        digitalWrite(3,LOW);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        counter = 0; 
        break;

      case 3:
        digitalWrite(2,HIGH);
        digitalWrite(3,HIGH);
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        counter = 0; 
        break;

      case 4:
        digitalWrite(2,HIGH);
        digitalWrite(3,HIGH);
        digitalWrite(4,HIGH);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        counter = 0; 
        break;

      case 5:
        digitalWrite(2,HIGH);
        digitalWrite(3,HIGH);
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(6,LOW);
        counter = 0;
        break;

      case 6:
        digitalWrite(2,HIGH);
        digitalWrite(3,HIGH);
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH); 
        counter = 0; 
        break;
    }

}

void loop() {
  
  if(counter % 30 == 0){
    nivoVode = provjeraVode();
    vodaLED(nivoVode);
  }
  
  if(nemaVodeLED == 1){
     fNemaVodeLED = nemaVode(fNemaVodeLED);
  }

  Serial.println("/////////////////////////////////////");
  Serial.println(counter);
  Serial.println(fNemaVodeLED);
  
  counter++; 
  delay(1000);
}
