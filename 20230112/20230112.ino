#include <NewPing.h> 
#define MAX_DISTANCE 150

#define IN1 2   // 1번째 모터
#define IN2 3   // 1번째 모터
#define ENA 5   // 1번째 모터  PWM제어

#define IN3 4   // 2번째 모터
#define IN4 7   // 2번째 모터
#define ENB 6   // 2번째 모터 PWM제어

#define F_Sonar  8   //정면부 초음파 센서 연결 핀
#define R_Sonar  10  //오른쪽 초음파 센서 연결 핀
#define L_Sonar  11  //왼쪽 초음파 센서 연결 핀

NewPing R_sensor(R_Sonar,R_Sonar,MAX_DISTANCE);
float R_Sonar_Distance = 0.0;
float R_Sonar_Distance_old = 0.0;
float R_Sonar_Error = 0.0;

NewPing L_sensor(L_Sonar,L_Sonar,MAX_DISTANCE);
float L_Sonar_Distance = 0.0;
float L_Sonar_Distance_old = 0.0;
float L_Sonar_Error = 0.0;

NewPing F_sensor(F_Sonar,F_Sonar,MAX_DISTANCE);
float F_Sonar_Distance = 0.0;
float F_Sonar_Distance_old = 0.0;
float F_Sonar_Error = 0.0;

int motor_diff=0;
int index;
int mission_flag=-1;

NewPing sonar[3] =
{
  NewPing (8, 8, MAX_DISTANCE),
  NewPing (10, 10, MAX_DISTANCE),
  NewPing (11, 11, MAX_DISTANCE),
  
}; 

void motor_control(int Direction, int speed1, int speed2)    //방향 속도 1: 전진 2: 후진 3: 정지
{
  switch(Direction)
  {
    case 1: analogWrite(ENA, speed1);
            analogWrite(ENB, speed2);
            digitalWrite(IN1, HIGH); //직진
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);           
            break;

    case 2: analogWrite(ENA, 80);
            analogWrite(ENB, 120);
            digitalWrite(IN1, LOW); //좌회전
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);           
            break;

    case 3: analogWrite(ENA, 80);
            analogWrite(ENB, 120);
            digitalWrite(IN1, HIGH); //우회전
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);           
            break;                  
  }
}

int line_sensor [5] = {0,0,0,0,0}; // 배열을 선언

int read_line_sensor()
{
  int i;
  int sum = 0;
  int line_index;
  
  for(i = 0; i < 5; i++)
  {
    line_sensor[i] = digitalRead(A0+i);
    sum += line_sensor[i];
    Serial.print(line_sensor[i]);
    Serial.print(" ");
  }
  Serial.println("");
  if(sum==0) line_index = -10;
  if(sum==1)
  {
    if(line_sensor[0]==1) line_index = -4;
    if(line_sensor[1]==1) line_index = -2;
    if(line_sensor[2]==1) line_index = 0;
    if(line_sensor[3]==1) line_index = 2;
    if(line_sensor[4]==1) line_index = 4;
  }
  if(sum==2)
  {
    if((line_sensor[0]==1) && (line_sensor[1]==1)) line_index = -3;
    if((line_sensor[1]==1) && (line_sensor[2]==1)) line_index = -1;
    if((line_sensor[2]==1) && (line_sensor[3]==1)) line_index = 1;
    if((line_sensor[3]==1) && (line_sensor[4]==1)) line_index = 3;
  }
  if(sum==5)
  {
    line_index = 10; 
  }
  Serial.print(line_index);
  Serial.println("");

  return line_index;
}

void line_tracing()
{
  int index;
  index = read_line_sensor();

  switch(index)
  {
    case 10 : motor_control(1, 0, 0); //정지
              break;
    
    case -10 : motor_control(1, 80, 110); //직진
               break; 
              
    case 0 : motor_control(1, 80, 110); //직진
             break;
            
    case -4 : motor_control(1, 0, 120); //좌회전
              break;
           
    case -2 : motor_control(1, 50, 120); //좌회전
              break;
              
    case 2  : motor_control(1, 120, 0); //우회전
              break;
             
    case 4 : motor_control(1, 120, 50); //우회전
             break;
             
    case -3 : motor_control(1, 0, 120); //좌회전
              break;
             
    case -1 : motor_control(1, 50, 120); //좌회전
              break;
            
    case 1 : motor_control(1, 120, 0); //우회전
             break;
    
    case 3 : motor_control(1, 120, 50); //우회전
             break;                                                   
  }          
}

void read_sonar_sensor(void)  //초음파 센서 값을 읽는 함수
{
    
 R_Sonar_Distance = sonar[1].ping_cm() * 10;
 L_Sonar_Distance = sonar[2].ping_cm() * 10;
 F_Sonar_Distance = sonar[0].ping_cm() * 10;
 if(R_Sonar_Distance == 0) R_Sonar_Distance = MAX_DISTANCE *10.0;
 if(L_Sonar_Distance == 0) L_Sonar_Distance = MAX_DISTANCE *10.0;
 if(F_Sonar_Distance == 0) F_Sonar_Distance = MAX_DISTANCE *10.0;
}

void update_sonar_old(void)
{
  R_Sonar_Distance_old = R_Sonar_Distance;  //측정된거된값을 과거에 넣는다
  L_Sonar_Distance_old = L_Sonar_Distance;  //측정된거된값을 과거에 넣는다
  F_Sonar_Distance_old = F_Sonar_Distance;  //측정된거된값을 과거에 넣는다
}

void update_sonar_error(void)
{
  R_Sonar_Error = R_Sonar_Distance - R_Sonar_Distance_old;  //현재 값에서 옛날 값을 뺀것
  L_Sonar_Error = L_Sonar_Distance - L_Sonar_Distance_old;  //현재 값에서 옛날 값을 뺀것
  F_Sonar_Error = F_Sonar_Distance - F_Sonar_Distance_old;  //옛날 값에서 현재 값을 뺀것
}

void avoid_obs()
{ 
 
    motor_control(3,80, 110);
    delay(800);
    motor_control(1, 80, 110);
    delay(1000);
    motor_control(2, 80, 110);
    delay(800);
    motor_control(1, 80, 110);
    delay(1200);
    motor_control(2, 80, 110);
    delay(600);
    while(1)
    {
      index=read_line_sensor();
      motor_control(1, 80, 110);
      if(index != -10)
      {
        motor_control(3, 80, 110);
        delay(250);
        break;
      }
    }
  
}

void wall_following()
{
  read_sonar_sensor();
  update_sonar_error();
  update_sonar_old();

  if(R_Sonar_Distance < L_Sonar_Distance)
  {
    motor_control(1,40,150); //좌회전
  }
  if(R_Sonar_Distance > L_Sonar_Distance)
  {
    motor_control(1,120,70); //우회전
  }
  if(R_Sonar_Distance = L_Sonar_Distance)
  {
    motor_control(1,80,110);
  }
}

void wall_following_CW()
{
  if(F_Sonar_Distance <=750)
  {
    motor_control(3,80, 110);
    delay(800);
    mission_flag++;
  }
}

int track_following()
{

  if(index != -10)
  {
    mission_flag = 4;
  }
}

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(115200);
  motor_control(1, 0, 0);
  delay(300);
  mission_flag = 0;
}

void loop() 
{ 
   index=read_line_sensor();   
   read_sonar_sensor();
  // track_following();

   if(mission_flag == 0)
   {
    if(F_Sonar_Distance<=300)
    {
      avoid_obs();
      }
    else{
      line_tracing();
      }
    if(L_Sonar_Distance + R_Sonar_Distance <= 1500)
    {
    mission_flag = 1;
    }
   }

   if(mission_flag == 1)
   {
    wall_following();
    wall_following_CW();
   }

   if(mission_flag == 2)
   {
    wall_following();
    wall_following_CW();
   }
   if(mission_flag == 3){
    wall_following();
    
    if(index != -10)
     {
      mission_flag = 4;
     }
    }

   if(mission_flag == 4){
     line_tracing();
    }
}
