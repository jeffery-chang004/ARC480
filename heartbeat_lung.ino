//ARC480 A2: You/Me/We/It
//commit history can be found here https://github.com/jeffery-chang004/ARC480/tree/main
int signal;
bool read = false;
int highest;
//constant variables
const int LED = 3;
const int BUZZER = 6;
//motor bridge side A (inputs 1 and 2)
const int enA = 9;
const int in1 = 8;
const int in2 = 7;
//motor driver side B (inputs 3 and 4)
const int enB = 11;
const int in3 = 12;
const int in4 = 13;

//variables to track LED and fan direction
int beats;
bool fanBlow = false;
bool canAdd = true;
bool fanSwitch = true;

void setup()
{
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop()
{
  //read heartbeat from A0
  signal = analogRead(A0);
  //only turn on fans if human presence detected
  if (signal == 0) {
    read = true;
  }if (signal > 800 && read == true) {
    read = false;
  }

  //debug print statement
  Serial.println("Signal: " + String(signal) + " reading: " + String(read) + " beats: " + String(beats) + " blow: " + String(fanBlow));

  //if someone is here
  if (read) {
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    if (signal > 500) {
      digitalWrite(LED, HIGH);
      digitalWrite(BUZZER, HIGH);
      if (canAdd) {
        beats++;
        canAdd = false;
      }
    }//turn off signal if hand not detected
    else if (signal < 500) {
      digitalWrite(LED, LOW);
      digitalWrite(BUZZER, LOW);
      canAdd = true;
    }
    //change directions of fan depending on fan blow variable
    if (fanBlow) {
      digitalWrite(in1, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in4, HIGH);
    }else if (!fanBlow) {
      digitalWrite(in1, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in2, HIGH);
      digitalWrite(in4, LOW);
    }
  }
  
  if (read == false) {
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    beats = 0;
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);
  }
  //change this number to change how many heartbeats it takes to reverse the direction of fan
  //fanSwitch variable ensures fan does not rapidly change if lingering on a heartbeat
  if (beats % 3 == 0 && fanSwitch) {
    fanBlow = !fanBlow;
    fanSwitch = false;
  }if (beats % 3 != 0) {
    fanSwitch = true;
  }

  delay(10);
}

