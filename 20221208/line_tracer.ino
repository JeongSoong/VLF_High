//#define MOTOR_R_IN1 2
//#define MOTOR_R_IN2 3
//#define MOTOR_R_ENA 5
//#define MOTOR_R_ENB 8
//#define MOTOR_R_PWM 10

//#define MOTOR_L_IN1 4
//#define MOTOR_L_IN2 7
//#define MOTOR_L_ENA 6
//#define MOTOR_L_ENB 9
//#define MOTOR_L_PWM 11

//NewPing sonar[SONAR_NUM] 
//{// Sensor object array.
  //NewPing (4, 5, MAX DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  //NewPing (6, 7, MAX DISTANCE) , 
  //NewPing (8, 9, MAX DISTANCE)
//};

#define IN1Pin 2
#define IN2Pin 3
#define ENAPin 5

#define IN3Pin 4
#define IN4Pin 7
#define ENBPin 6

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
    line_index = -10; 
  }
  Serial.print(line_index);
  Serial.println("");

  return line_index;
}

//void motor_control (int speed_1, int dir_1, int speed_r, int dir_r)
//{
  //if (dir_1 == 1) // 전진
  //{
    //digitalWrite (MOTOR_L_IN1, HIGH) ; 
    //digitalWrite (MOTOR_L_IN2, LOW);
    //analogWrite (MOTOR_L_ENB, speed_1);
  //}
    //else if(dir_1 == -1)//후진
    //{
      //digitalWrite (MOTOR_L_IN1, LOW); 
      //digitalWrite (MOTOR_L_IN2, HIGH);
      //analogWrite (MOTOR_L_ENB, speed_1);
    //}
      //else
      //{
        //digitalWrite (MOTOR_L_IN1, LOW); 
        //digitalWrite (MOTOR_L_IN2, LOW);
        //analogWrite (MOTOR_L_ENB, 0);
      //}
        //if (dir_r ==1) // 전진
        //{
          //digitalWrite (MOTOR_R_IN1, HIGH); 
          //digitalWrite (MOTOR_R_IN2, LOW);
          //analogWrite (MOTOR_R_ENB, speed_r);
        //}
        //else if(dir_r == -1)//후진
        //{
          //digitalWrite (MOTOR_R_IN1, LOW); 
          //digitalWrite (MOTOR_R_IN2, HIGH);
          //analogWrite (MOTOR_R_ENB, speed_r);
        //}
        //else
        //{
          //digitalWrite (MOTOR_R_IN1, LOW); 
          //digitalWrite (MOTOR_R_IN2, LOW);
          //analogWrite (MOTOR_R_ENB, speed_r);
        //}
//}

void setup () 
{
  // put your setup code here, to run once:
  Serial. begin (9600); //9600 속도로 통신을 시작 한다.
}

void loop()
{
  int index;
  index = read_line_sensor();
  
  switch(index)
  {
    case -10 :   //정지
            digitalWrite(IN1Pin, HIGH);
            digitalWrite(IN2Pin, LOW);
            digitalWrite(IN3Pin, HIGH);
            digitalWrite(IN4Pin, LOW);
            analogWrite(ENAPin, 0);
            analogWrite(ENBPin, 0);
            break;
    case 0 :     //전진
             digitalWrite(IN1Pin, HIGH);
             digitalWrite(IN2Pin, LOW);
             digitalWrite(IN3Pin, LOW);
             digitalWrite(IN4Pin, HIGH);
             analogWrite(ENAPin, 130);
             analogWrite(ENBPin, 130);
             break;
    case 2 :     //좌회전
            digitalWrite(IN1Pin, HIGH);
            digitalWrite(IN2Pin, LOW);
            digitalWrite(IN3Pin, HIGH);
            digitalWrite(IN4Pin, LOW);
            analogWrite(ENAPin, 130);
            analogWrite(ENBPin, 130);
            break;
    case 4 :     //좌회전
            digitalWrite(IN1Pin, HIGH);
            digitalWrite(IN2Pin, LOW);
            digitalWrite(IN3Pin, HIGH);
            digitalWrite(IN4Pin, LOW);
            analogWrite(ENAPin, 130);
            analogWrite(ENBPin, 130);
            break;                  
    case -2 :     //우회전
           digitalWrite(IN1Pin, LOW);
           digitalWrite(IN2Pin, HIGH);
           digitalWrite(IN3Pin, LOW);
           digitalWrite(IN4Pin, HIGH);
           analogWrite(ENAPin, 130);
           analogWrite(ENBPin, 130);
           break;
    case -4  :    //우회전
           digitalWrite(IN1Pin, LOW);
           digitalWrite(IN2Pin, HIGH);
           digitalWrite(IN3Pin, LOW);
           digitalWrite(IN4Pin, HIGH);
           analogWrite(ENAPin, 130);
           analogWrite(ENBPin, 130);
           break;
    case -3 :     //우회전
           digitalWrite(IN1Pin, LOW);
           digitalWrite(IN2Pin, HIGH);
           digitalWrite(IN3Pin, LOW);
           digitalWrite(IN4Pin, HIGH);
           analogWrite(ENAPin, 130);
           analogWrite(ENBPin, 130);
           break;
    case -1 :     //우회전
           digitalWrite(IN1Pin, LOW);
           digitalWrite(IN2Pin, HIGH);
           digitalWrite(IN3Pin, LOW);
           digitalWrite(IN4Pin, HIGH);
           analogWrite(ENAPin, 130);
           analogWrite(ENBPin, 130);
           break;
    case 1 :     //좌회전
           digitalWrite(IN1Pin, HIGH);
            digitalWrite(IN2Pin, LOW);
            digitalWrite(IN3Pin, HIGH);
            digitalWrite(IN4Pin, LOW);
            analogWrite(ENAPin, 130);
            analogWrite(ENBPin, 130);
            break;
    case 3 :     //좌회전
           digitalWrite(IN1Pin, HIGH);
            digitalWrite(IN2Pin, LOW);
            digitalWrite(IN3Pin, HIGH);
            digitalWrite(IN4Pin, LOW);
            analogWrite(ENAPin, 130);
            analogWrite(ENBPin, 130);
            break;
                                                     
  }          
}
