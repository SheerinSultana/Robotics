//LDR -  #10
//LED -  #3

int LDRPin = 10;
int led = 3;
void setup() { 
pinMode(led, OUTPUT);
pinMode(LDRPin,INPUT); }
void loop()
{
if (digitalRead(LDRPin)==HIGH)
{digitalWrite(led,HIGH);}
else{digitalWrite(led,LOW);}
}
