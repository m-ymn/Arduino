#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial s(5,6);
 
  int da1 = 0;
  int da2 = 0;
  int da3 = 0 ;
  int btn_st = 0 ;
  int btn_st2 = 0 ;
  int pre_btn_st = 0 ;
  int pre_btn_st2 = 0;
 
void setup() {
  s.begin(9600);
  Serial.begin(9600) ;
  pinMode(2,INPUT);
  pinMode(3,INPUT) ;
  pinMode(8,OUTPUT); 
  pinMode(9,OUTPUT) ; 
}
 
void loop() {
 StaticJsonBuffer<1000> jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
  root["data1"] = da1;
  root["data2"] = da2;
  root["data3"] = da3;
  if(s.available()>0)
  {
   root.printTo(s);
  }
   btn_st = digitalRead(2) ;
   btn_st2 = digitalRead(3) ;

   if (btn_st != pre_btn_st || btn_st2 != pre_btn_st2)
   {
    if (btn_st == HIGH && btn_st2 == LOW){
        digitalWrite(8,HIGH) ; //motor pin 1
        digitalWrite(9,LOW) ;   //motor pin2   //c. clockwise
        da1 += 1 ;
    }
    else if (btn_st == LOW && btn_st2 == HIGH){
       digitalWrite(9,HIGH) ;
       digitalWrite(8,LOW) ;    //clockwise
       da2 += 1 ;
    }
    else if (btn_st == LOW && btn_st2 == LOW){
        digitalWrite(8,HIGH);  // motor stoped
        digitalWrite(9,HIGH) ;  // motor stoped
       da3 += 1 ;
    }
      delay(50) ;
    }

    
      pre_btn_st = btn_st ;
      pre_btn_st2 = btn_st2 ;
      Serial.print("Count1 = ");
      Serial.println(da1);
      Serial.print("count2 = ");
      Serial.println(da2);
      Serial.print("count3 = ");
      Serial.println(da3);
      Serial.println("-------------------------");
      
    delay(3000);
}
