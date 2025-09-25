// C++ code
//

int signal;
bool read = false;
bool timed = false;
int currentMillis;
int timeDiff;
int highest;
const int enA = 9;
const int in1 = 8;
const int in2 = 7;
const int speed = 60;
int time;

void setup()
{
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

}

void loop()
{
  time = millis()/1000 - timeDiff;
  signal = analogRead(A0);
  if (signal == 0) {
    read = true;
    timeDiff = millis()/1000;
  }if (signal > 800 && read == true) {
    read = false;
  }

  //Serial.println("hi");
  //Serial.println(signal);
  Serial.println(String(signal));
  //Serial.println(String(time));
  //Serial.println("Tme Diff: " + String(timeDiff));
  
  if (read == true && time < 3) {
    highest = 0;
    if (signal > highest) {
      highest = signal;
    }
  }

  if (read == true && signal > 450) {
    digitalWrite(3, HIGH);
    analogWrite(enA, 255);

  }else if (signal < 450) {
    digitalWrite(3, LOW);
    analogWrite(enA, 0);

  }
  //digitalWrite(3, HIGH);
  delay(10);
}