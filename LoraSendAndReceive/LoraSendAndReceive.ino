
#include <MKRWAN.h>

LoRaModem modem;

#include "arduino_secrets.h"

String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;
_lora_class z = CLASS_A;

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

void setup()
{

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

  Serial.begin(115200);
  while (!Serial);

  if (!modem.begin(US915))
  {
    Serial.println("Failed to start module");
    while (1) {}
  };

  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  bool cl = modem.configureClass(z);
  if (cl == 1)
  {
    Serial.print("Your device is using class: ");
    Serial.println("CLASS A");
  }

  Serial.println("Your device is trying to connect to network - -  ");

  int connected = modem.joinOTAA(appEui, appKey);

  if (!connected)
  {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    //while (1) {}

    Serial.println("Do you want to retry? (Y/N)");

    while (!Serial.available());
    String check = Serial.readStringUntil('\n');

    if (check == "Y")
      int connected = modem.joinOTAA(appEui, appKey);

    return;
  }

  // Set poll interval to 60 secs.
  modem.minPollInterval(60);
  // NOTE: independently by this setting the modem will
  // not allow to send more than one message every 2 minutes,
  // this is enforced by firmware and can not be changed.
}

void WriteOut(int val) {
  switch (val) {
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

void ClearOut() {
  digitalWrite(firstBit, LOW);
  digitalWrite(secondBit, LOW);
  return;
}

void loop()
{
  Serial.println();
  Serial.println("Enter a message to send to network");
  Serial.println("(make sure that end-of-line 'NL' is enabled)");

  while (!Serial.available());
  String msg = Serial.readStringUntil('\n');

  Serial.println();
  Serial.print("Sending: " + msg + " - ");
  for (unsigned int i = 0; i < msg.length(); i++)
  {
    Serial.print(msg[i] >> 4, HEX);
    Serial.print(msg[i] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();

  int err;
  modem.beginPacket();
  modem.print(msg);
  err = modem.endPacket(true);
  if (err > 0)
  {
    Serial.println("Message sent correctly!");
  }
  else
  {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
  delay(1000);
  if (!modem.available())
  {
    Serial.println("No downlink message received at this time.");
    return;
  }
  //char rcv[64];
  int i = 0;
  while (modem.available())
  {
    incomingByte = (char)modem.read();
  }
  Serial.print("Received: ");
  //  for (unsigned int j = 0; j < i; j++)
  //  {
  //      Serial.print(incomingByte);
  //  }

  Serial.print(incomingByte);

  //Serial.print(" - ");

  //  for (unsigned int j = 0; j < i; j++)
  //  {
  //    Serial.print(rcv[j] >> 4, HEX);
  //    Serial.print(rcv[j] & 0xF, HEX);
  //    Serial.print(" ");
  //  }
  val = (int) (incomingByte - '0');


  digitalWrite(relay, HIGH);

  while (digitalRead(DisplayStatus) == LOW) {
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
  Serial.println();
}
