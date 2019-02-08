  int buttonStatus = 0;
  int prevButtonStatus = 0;
  bool relayStatus = false;
  String data="Red";
  
  int PiStatus = 0;
  int PiRead = 1;
  int Write = 2;
  int button = 6;
  int relay = 5;
  int test = 7;
  int power = 14;

void setup() {

   pinMode(PiStatus, INPUT);
  pinMode(PiRead,INPUT);
  pinMode(Write, OUTPUT);
  
  // put your setup code here, to run 
  pinMode(power, OUTPUT);
  pinMode(button, INPUT);
  pinMode(relay, OUTPUT);
  
  digitalWrite(power, HIGH);
  digitalWrite(relay, LOW);
   
  Serial.begin(9600);
  digitalWrite(Write, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  int buttonStatus = digitalRead(button);
  
  if(buttonStatus != prevButtonStatus){
     if( buttonStatus == HIGH){
        
        if(relayStatus){
          digitalWrite(relay, LOW);
          relayStatus = false;
          }
        else{
          digitalWrite(relay, HIGH);
          relayStatus = true;

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
          
        }
    }
    prevButtonStatus = buttonStatus;
}
