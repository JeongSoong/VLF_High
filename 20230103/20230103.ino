#define F1_Sonar 8
#define F2_Sonar 8
#define L_Sonar 10
#define R_Sonar 11

int IN1Pin = 2;
int IN2Pin = 3;
int IN3Pin = 4;
int IN4Pin = 7;
int ENAPin = 5;
int ENBPin = 6;

float F1_Sonar_sensor()
{
  float duration = 0.0;
  float distance = 0.0;
  pinMode(F1_Sonar, OUTPUT);
  digitalWrite(F1_Sonar,LOW);
  digitalWrite(F1_Sonar,HIGH);
  delay(10);
  digitalWrite(F1_Sonar,LOW);
  pinMode(F1_Sonar,INPUT);
  duration = pulseIn(F1_Sonar, HIGH);
  distance = (duration * 340.0)/2.0/10000.0;
  return distance;
}

float F2_Sonar_sensor()
{
  float duration = 0.0;
  float distance = 0.0;
  pinMode(F2_Sonar, OUTPUT);
  digitalWrite(F2_Sonar,LOW);
  digitalWrite(F2_Sonar,HIGH);
  delay(10);
  digitalWrite(F2_Sonar,LOW);
  pinMode(F2_Sonar,INPUT);
  duration = pulseIn(F2_Sonar, HIGH);
  distance = (duration * 340.0)/2.0/10000.0;
  return distance;
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(F1_Sonar, OUTPUT);
  pinMode(F2_Sonar, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  float F1_distance, F2_distance, D;
  F1_distance = F1_Sonar_sensor();
  F2_distance = F2_Sonar_sensor();
  D = F1_distance - F2_distance;
  
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  analogWrite(ENAPin, 0);
  analogWrite(ENBPin, 0);
  delay(1000);
    
  Serial.print("  F1:");
  Serial.print(F1_distance);
  Serial.print("cm");
  Serial.print("\n");

  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);
  analogWrite(ENAPin, 40);
  analogWrite(ENBPin, 40);
  delay(1000);

  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  analogWrite(ENAPin, 0);
  analogWrite(ENBPin, 0);

  Serial.print("  F2:");
  Serial.print(F2_distance);
  Serial.print("cm");
  Serial.print("\n");

  Serial.print("  D:");
  Serial.print(F1_distance - F2_distance);
  Serial.print("cm");
  Serial.print("\n");  
}
