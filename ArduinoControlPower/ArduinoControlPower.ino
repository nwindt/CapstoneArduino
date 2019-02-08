  int buttonStatus = 0;
  int prevButtonStatus = 0;
  bool relayStatus = false;
  char incomingByte;
  int val;

  int DisplayStatus = 3;
  int WriteStatus = 2;
  int firstBit = 1;
  int secondBit = 0;

  int DisplayOn = 4;
  int button = 6;
  int relay = 5;
  int power = 14;

void setup() {
  // put your setup code here, to run 
  pinMode(power, OUTPUT);
  pinMode(button, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(DisplayOn, OUTPUT);

  pinMode(DisplayStatus, INPUT);
  pinMode(WriteStatus, OUTPUT);
  pinMode(firstBit, OUTPUT);
  pinMode(secondBit, OUTPUT);

  digitalWrite(WriteStatus, LOW);
  digitalWrite(firstBit, LOW);
  digitalWrite(secondBit, LOW);
  
  digitalWrite(power, HIGH);
  digitalWrite(relay, LOW);
  digitalWrite(DisplayOn, LOW);
  Serial.begin(9600);
}

void WriteOut(int val){
    switch(val){     
      case 0:
          digitalWrite(firstBit, LOW);
          digitalWrite(secondBit, LOW);
          break;
      case 1:
          digitalWrite(firstBit, HIGH);
          digitalWrite(secondBit, LOW);
          break;
      case 2:
          digitalWrite(firstBit, LOW);
          digitalWrite(secondBit, HIGH);
          break;
      case 3:
          digitalWrite(firstBit, HIGH);
          digitalWrite(secondBit, HIGH);
          break;
       default:
          Serial.println("Not an option");
     }

     return;
 }
 
void ClearOut(){
    digitalWrite(firstBit, LOW);
    digitalWrite(secondBit, LOW);
    return;
  }

void loop() {
  // put your main code here, to run repeatedly:

  
  if (Serial.available() > 0){

    incomingByte = Serial.read();
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);
    val = (int) (incomingByte - '0');

    
    digitalWrite(relay, HIGH);
  
    while(digitalRead(DisplayStatus) == LOW){
     //Do nothing
      }
    digitalWrite(DisplayOn, HIGH);  
    WriteOut(val);
    digitalWrite(WriteStatus, HIGH);
    
    delay(25000);

    ClearOut();
    digitalWrite(DisplayOn, LOW); 
    digitalWrite(WriteStatus, LOW);
    digitalWrite(relay, LOW);
  }
        
}
