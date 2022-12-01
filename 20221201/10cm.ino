#define F_Sonar 8

int IN1Pin = 2;
int IN2Pin = 3;
int IN3Pin = 4;
int IN4Pin = 7;
int ENAPin = 5;
int ENBPin = 6;

//float F_Sonar_sensor()
//  {
//    float duration = 0.0;
//    float distance = 0.0;
//    
//    pinMode(F_Sonar, OUTPUT);
//    digitalWrite(F_Sonar, LOW);
//    digitalWrite(F_Sonar, HIGH);
//    delay(10);
//    digitalWrite(F_Sonar, LOW);
//    
//    pinMode(F_Sonar, INPUT);
//    duration = pulseIn(F_Sonar, HIGH);
//    distance = (duration * 340.0)/2.0/10000.0;
//  
//    return distance;
//  }

void setup()
{
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(IN3Pin, OUTPUT);
  pinMode(IN4Pin, OUTPUT);
  pinMode(F_Sonar, OUTPUT);
  Serial.begin (115200);
}

void loop()
{
  float duration = 0.0;
  float distance = 0.0;
 
  pinMode(F_Sonar, OUTPUT);
  digitalWrite(F_Sonar, LOW);
  digitalWrite(F_Sonar, HIGH);
  delay(10);
  digitalWrite(F_Sonar, LOW);
 
  pinMode(F_Sonar, INPUT);
  duration = pulseIn(F_Sonar, HIGH);
  distance = (duration * 340.0)/2.0/10000.0;
 
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  analogWrite(ENAPin, 80);
  analogWrite(ENBPin, 80);
  // delay(2000);

  if(distance <= 10)
  {  
    analogWrite(ENAPin, 0);
    analogWrite(ENBPin, 0);    
    digitalWrite(IN1Pin, HIGH);
    digitalWrite(IN2Pin, LOW);
    digitalWrite(IN3Pin, HIGH);
    digitalWrite(IN4Pin, LOW);
    analogWrite(ENAPin, 150);
    analogWrite(ENBPin, 80);
    delay(620);
  }
 
  else
  {
    digitalWrite(IN1Pin, HIGH);
    digitalWrite(IN2Pin, LOW);
    digitalWrite(IN3Pin, LOW);
    digitalWrite(IN4Pin, HIGH);
    analogWrite(ENAPin, 80);
    analogWrite(ENBPin, 80);
  }
}
