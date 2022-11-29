int IN1Pin = 3;
int IN2Pin = 4;

int ENPin = 5;

void setup()
{
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  analogWrite(ENPin, 130);
  Serial.begin(9600);
  Serial.println("start !!");
}

void loop()
{
  if(Serial.available())
  {
    char in_data;
    in_data = Serial.read();
    Serial.print("data : ");
    Serial.println(in_data);

    if(in_data == '1')
    {
      digitalWrite(IN1Pin, HIGH);
      digitalWrite(IN2Pin, LOW);
    }
    else if(in_data == '2')
    {
      digitalWrite(IN1Pin, LOW);
      digitalWrite(IN1Pin, HIGH);
    }
    else if(in_data == '3')
    digitalWrite(IN1Pin, HIGH);
    digitalWrite(IN1Pin, HIGH);
  }
}
