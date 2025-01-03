#include <Arduino.h>



void rgb_init(){
    pinMode(12,OUTPUT);
    pinMode(27,OUTPUT);
    pinMode(32,OUTPUT);
    pinMode(33,OUTPUT);




}





void no(){
    digitalWrite(12,0); 
    digitalWrite(27,1);
    digitalWrite(33,1);
    digitalWrite(32,1);
}


void red(){
    digitalWrite(12,1); 
    digitalWrite(27,0);
    digitalWrite(33,1);
    digitalWrite(32,1);
}
void greed(){
    digitalWrite(12,1); 
    digitalWrite(27,1);
    digitalWrite(33,0);
    digitalWrite(32,1);
}


void greed2(){
    digitalWrite(12,0); 
    digitalWrite(27,0);
    digitalWrite(33,1);
    digitalWrite(32,0);
}

void blue(){
    digitalWrite(12,1); 
    digitalWrite(27,1);
    digitalWrite(33,1);
    digitalWrite(32,0);
}

void blue2(){
    digitalWrite(12,0); 
    digitalWrite(27,0);
    digitalWrite(33,0);
    digitalWrite(32,1);
}