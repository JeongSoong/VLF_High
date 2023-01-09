#include <NewPing.h>    //NewPing(초음파 라이브러리) 선언

#define IN1 2// 1번째 모터
#define IN2 3// 1번째 모터
#define ENA 5// 1번째 모터  PWM제어

#define IN3 4   // 2번째 모터
#define IN4 7   // 2번째 모터
#define ENB 6   // 2번째 모터 PWM제어

#define F_Sonar  8  //정면부 초음파 센서 연결 핀
#define R_Sonar  10 //오른쪽 초음파 센서 연결 핀
#define L_Sonar  11 //왼쪽 초음파 센서 연결 핀

#define MaxDistance  400

NewPing F_sensor(F_Sonar,F_Sonar,MaxDistance);
float F_distance; //정면 초음파 센서값을 저장할 변수 선언
float F_distance_D,F_distance1,F_distance2;
NewPing L_sensor(L_Sonar,L_Sonar,MaxDistance);
float L_distance; //왼쪽 초음파 센서값을 저장할 변수 선언
float L_distance_D,L_distance1,L_distance2;
NewPing R_sensor(R_Sonar,R_Sonar,MaxDistance);
float R_distance; //오른쪽 초음파 센서값을 저장할 변수 선언
float R_distance_D,R_distance1,R_distance2;

NewPing sonar[3] =
{
  NewPing (8, 8, 500),
  NewPing (10, 10, 500),
  NewPing (11, 11, 500),
};

void motor_control(int direction, int speed1, int speed2)    //방향 속도 1: 전진 2: 후진 3: 정지
{
  switch(direction)
  {
    case 1: digitalWrite(IN1, HIGH); //직진
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);
            analogWrite(ENA, speed1);
            analogWrite(ENB, speed2);
            break;

    case 2: digitalWrite(IN1,HIGH); //정지
            digitalWrite(IN2,LOW);
            digitalWrite(IN3,LOW);
            digitalWrite(IN4,HIGH);
            analogWrite(ENA, speed1);
            analogWrite(ENA, speed2);
            break;

  }
}
void Ang_Calcul()
{
      Serial.println();
           
  double dist =0;
  double disf1=0;
  double disf3=0;
  double disf2=0;
  double disf4=0;
  double ang =0;
   delay(300);
   F_distance = sonar[0].ping_cm() * 10;
   R_distance = sonar[1].ping_cm() * 10;
   L_distance = sonar[2].ping_cm() * 10;      
  
    delay(300);
    dist=F_distance;
    disf2=L_distance;
    motor_control(1,70,70);
    delay(800);
    motor_control(2,0,0);
    delay(300);
    L_distance = sonar[1].ping_cm() * 10;
    F_distance = sonar[0].ping_cm() * 10;
    disf2=F_distance;
    disf4=R_distance;
    disf1 = dist - disf2;
        Serial.print("F_Total\t:\t");
        Serial.print(dist); 
        Serial.println();
        Serial.print("F_D1\t:\t");
        Serial.print(disf1); 
        Serial.println();
        Serial.print("F_D2\t:\t");
        Serial.print(disf2);
        Serial.println();   
        ang=atan((disf2-disf4)/dist);
        ang= ang * 180 /3.1415;
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.print("Angle \t:\t");
        Serial.println(ang);
        
}


void setup()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    Serial.begin(115200);

    Ang_Calcul();
     
}

void loop()
{
  float F_distance=(float)(F_sensor.ping())*10/US_ROUNDTRIP_CM;
  if(F_distance <= F_distance-100)
  {
      delay(100);
      Serial.print("   F : ");
      Serial.println(F_distance);
      }
      else
      {
        Ang_Calcul();
      } 
} 
