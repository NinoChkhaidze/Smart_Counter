
#include <SoftwareSerial.h> 
SoftwareSerial ChemiSeriali(3, 4); // RX, TX bluetooth module

#include <TroykaCurrent.h>
ACS712 UnivCounter(A0); // current sensor
float I = 0;
int Brzaneba = 0;
bool X1 = 0, X2 = 0, X3 = 0, X4 = 0;
#define relay1 12
#define relay2 11
#define relay3 10
#define relay4 9
double kvh = 0;
int U = 220;

void setup()
{
  pinMode(relay1, OUTPUT);  
  pinMode(relay2, OUTPUT);  
  pinMode(relay3, OUTPUT);  
  pinMode(relay4, OUTPUT);  
  
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
  digitalWrite(relay4,HIGH);
  
  Serial.begin(9600);
  ChemiSeriali.begin(9600);
}

void loop()
{

  if  (ChemiSeriali.available() > 0) {
    // signal is sent from the app to arduino          
      Brzaneba=ChemiSeriali.read();
      if (Brzaneba==0){resetF();}   
      if (Brzaneba==9){setF();}     
     
     if (Brzaneba==1){digitalWrite(relay1,LOW); } 
     if (Brzaneba==2){digitalWrite(relay1,HIGH);} 
     
     if (Brzaneba==3){digitalWrite(relay2,LOW); } 
     if (Brzaneba==4){digitalWrite(relay2,HIGH);} 
     
     if (Brzaneba==5){digitalWrite(relay3,LOW); } 
     if (Brzaneba==6){digitalWrite(relay3,HIGH);} 
     
     if (Brzaneba==7){digitalWrite(relay4,LOW); } 
     if (Brzaneba==8){digitalWrite(relay4,HIGH);} 
  }
  
  if (Serial.available() > 0) {
     char monac = Serial.read();
     if (monac=='0'){resetF();}   
     if (monac=='9'){setF();}     
     
     if (monac=='1'){digitalWrite(relay1,LOW); } 
     if (monac=='2'){digitalWrite(relay1,HIGH);} 
     
     if (monac=='3'){digitalWrite(relay2,LOW); } 
     if (monac=='4'){digitalWrite(relay2,HIGH);} 
     
     if (monac=='5'){digitalWrite(relay3,LOW); } 
     if (monac=='6'){digitalWrite(relay3,HIGH);} 
     
     if (monac=='7'){digitalWrite(relay4,LOW); } 
     if (monac=='8'){digitalWrite(relay4,HIGH);} 
  } 
      
   I = 3 * UnivCounter.readCurrentAC(); // calculating the electric current 
   if (I < 0) I = 0;
   
   String str= "I="; 
   str += I;
   str += "A";
   
   double P = I * U; // calculating power
   kvh += P; 
   
   double bill = 0; // calculating electrcity bill 
   if (kvh > 0 && kvh <= 101) bill = kvh * 0.18041;
   else if (kvh > 101 && kvh <= 301) bill = kvh * 0.22053;
   else bill = kvh * 0.26537;

   str += int(bill);
   str += "S";

   str += kvh;
   str += "K";
   while(str.length() < 25) str+=';';
   
   Serial.println(str);
   ChemiSeriali.print(str); // sending information from arduino to the app using bluetooth module
   delay(1000);
}

void resetF(){
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
  digitalWrite(relay4,HIGH);
}

void setF(){
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
  digitalWrite(relay3,LOW);
  digitalWrite(relay4,LOW);
}
