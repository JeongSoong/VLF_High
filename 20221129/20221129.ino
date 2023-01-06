#define IN1 2
#define IN2 3
#define ENA 5

#define IN3 4
#define IN4 7
#define ENB 6

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop()
{
  digitalWrite(IN1, HIGH);//직진
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);
  delay(2000);

  digitalWrite(IN1, HIGH);//우로 회전
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);
  delay(1300);

  digitalWrite(IN1, LOW);//좌로회전
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);
  delay(1400);

  digitalWrite(IN1, LOW);//후진
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 130);
  analogWrite(ENB, 130);
  delay(2000);
}
