int signal;
bool read = false;
bool timed = false;
int currentMillis;
int timeDiff;
int highest;

const int LED = 3;
const int BUZZER = 6;

const int enA = 9;
const int in1 = 8;
const int in2 = 7;

const int enB = 11;
const int in3 = 12;
const int in4 = 13;

const int speed = 60;
int time;
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
  time = millis()/1000 - timeDiff;
  signal = analogRead(A0);
  if (signal == 0) {
    read = true;
    //timeDiff = millis()/1000;
  }if (signal > 800 && read == true) {
    read = false;
  }

  Serial.println("Signal: " + String(signal) + " reading: " + String(read) + " beats: " + String(beats) + " blow: " + String(fanBlow));
  //Serial.println(String(time));
  //Serial.println("Tme Diff: " + String(timeDiff));
  
  // if (read == true && time < 3) {
  //   highest = 0;
  //   if (signal > highest) {
  //     highest = signal;
  //   }
  // }

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
    }else if (signal < 500) {
      digitalWrite(LED, LOW);
      digitalWrite(BUZZER, LOW);
      canAdd = true;
    }
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
  if (beats % 5 == 0 && fanSwitch) {
    fanBlow = !fanBlow;
    fanSwitch = false;
  }if (beats % 5 != 0) {
    fanSwitch = true;
  }

  //digitalWrite(3, HIGH);
  delay(10);
}
