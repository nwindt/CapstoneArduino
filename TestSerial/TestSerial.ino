String data="Red";
int PiStatus = 0;
int PiRead = 1;
int Write = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(PiStatus, INPUT);
  pinMode(PiRead,INPUT);
  pinMode(Write, OUTPUT);
  
  Serial.begin(9600);
  digitalWrite(Write, HIGH);


}

  void loop() {
  // put your main code here, to run repeatedly:
  
  while(digitalRead(PiStatus) == LOW){
   //Do nothing
    }
  
  while(digitalRead(PiRead) == LOW){
    //Do nothing
    }
  Serial.println(data);//data that is being Sent

  digitalWrite(Write, HIGH);
  delay(200);

  while(digitalRead(PiRead) == HIGH){
    //Do nothing
    }
  
}
