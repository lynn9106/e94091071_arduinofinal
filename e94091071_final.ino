// L298N 馬達驅動板
// 宣告 MotorA 為右邊
// 宣告 MotorB 為左邊

#define MotorA_I1     8  //定義 I1 接腳
#define MotorA_I2     9  //定義 I2 接腳
#define MotorB_I3    10  //定義 I3 接腳
#define MotorB_I4    11  //定義 I4 接腳
#define MotorA_PWMA    5  //定義 PWMA (PWM調速) 接腳
#define MotorB_PWMB    6  //宣告 PWMB (PWM調速) 接腳

#define SensorLeft    A0  //定義 左感測器 輸入腳
#define SensorMiddle  A1  //定義 中感測器 輸入腳
#define SensorRight   A2  //定義 右感測器 輸入腳
int off_track = 0;

#define LaserPIN A5

const int buzzerPin = 4;

bool go=false;
bool decide=false;
bool servoOn=false;

#include <Servo.h> 
Servo myservo;  
int pos;   
 

void setup()
{
  Serial.begin(9600); 
  
  pinMode(MotorA_I1,OUTPUT);
  pinMode(MotorA_I2,OUTPUT);
  pinMode(MotorB_I3,OUTPUT);
  pinMode(MotorB_I4,OUTPUT);
  pinMode(MotorA_PWMA,OUTPUT);
  pinMode(MotorB_PWMB,OUTPUT);
  
  analogWrite(MotorA_PWMA,150);    //設定馬達 (右) 轉速
  analogWrite(MotorB_PWMB,150);    //設定馬達 (左) 轉速

  pinMode(LaserPIN,OUTPUT);
  digitalWrite(LaserPIN, LOW); 

  pinMode(LaserPIN,OUTPUT);

  pinMode(SensorLeft,   INPUT); 
  pinMode(SensorMiddle, INPUT);
  pinMode(SensorRight,  INPUT);


  myservo.attach(A4); 
  myservo.write(10); 

  randomSeed(analogRead(A0)); 


}

void finish(int pin){
  tone(pin, 100, 100);
  delay(300);
  tone(pin, 100, 100);
  delay(300);
  noTone(pin);
  }

void cancel(int pin){
  tone(pin, 100, 100);
  delay(300);
  tone(pin, 75, 100);
  delay(300);
  noTone(pin);
  }


void advance(int a)    // 前進
{
    digitalWrite(MotorA_I1,HIGH);   
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,HIGH);   
    digitalWrite(MotorB_I4,LOW);
    delay(a * 100);
}

void turnR(int d)    //右轉
{
    digitalWrite(MotorA_I1,LOW);    
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,HIGH);   
    digitalWrite(MotorB_I4,LOW);
    delay(d * 100);
}

void turnL(int e)    //右轉
{
    digitalWrite(MotorA_I1,HIGH);   
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,LOW);    
    digitalWrite(MotorB_I4,HIGH);
    delay(e * 100);
}    

void stopRL(int f)  //停止
{
    digitalWrite(MotorA_I1,HIGH);   
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,HIGH);   
    digitalWrite(MotorB_I4,HIGH);
    delay(f * 100);
}

void back(int g)    //後退
{
    digitalWrite(MotorA_I1,LOW);    
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,LOW);    
    digitalWrite(MotorB_I4,HIGH);
    delay(g * 100);     
}

void linetracking()
{   int SL = digitalRead(SensorLeft);
  int SM = digitalRead(SensorMiddle);
  int SR = digitalRead(SensorRight);
  
  if((SM == LOW) && (SL == LOW) && (SR == LOW))  // 小車脫離黑線
  {
    analogWrite(MotorA_PWMA,100);    //設定馬達 (右) 轉速
    analogWrite(MotorB_PWMB,100);    //設定馬達 (左) 轉速
   if(off_track < 3)
    {
      switch(off_track)
      {
        case 0:
          back(1);
          break;
        
        case 1:
          turnR(1);
          break;
          
        case 2:
          turnL(2);
          break;
      }     
      off_track++;
    }
    else
    {
      stopRL(0);
    }
  }
  else
  {
    off_track = 0;
                   
    if(SM == HIGH)  //中感測器在黑色區域
    {
      digitalWrite(LaserPIN, LOW);  
      if((SL == LOW) && (SR == HIGH))  // 左白右黑, 車體偏右校正
      {
        analogWrite(MotorA_PWMA,90);    //設定馬達 (右) 轉速
        analogWrite(MotorB_PWMB,100);    //設定馬達 (左) 轉速
        advance(0);
      } 
      else if((SL == HIGH) && (SR == LOW))  // 左黑右白, 車體偏左校正
      {
        analogWrite(MotorA_PWMA,100);    //設定馬達 (右) 轉速
        analogWrite(MotorB_PWMB,90);    //設定馬達 (左) 轉速
        advance(0);
      }
      else  // 其他, 直走
      {
        analogWrite(MotorA_PWMA,100);    //設定馬達 (右) 轉速
        analogWrite(MotorB_PWMB,100);    //設定馬達 (左) 轉速
        advance(0);
      }
    } 
    else // SM == LOW 表示中感測器在白色區域, 車體已大幅偏離黑線
    {
     digitalWrite(LaserPIN, HIGH);  
     if((SL == LOW) && (SR == HIGH))  // 左白右黑, 車體快速右轉
      {
        analogWrite(MotorA_PWMA,100);    //設定馬達 (右) 轉速
        analogWrite(MotorB_PWMB,100);    //設定馬達 (左) 轉速
        turnR(0);
      }
      else if((SL == HIGH) && (SR == LOW))  // 左黑右白, 車體快速左轉
      {
        analogWrite(MotorA_PWMA,100);    //設定馬達 (右) 轉速
        analogWrite(MotorB_PWMB,100);    //設定馬達 (左) 轉速
        turnL(0);
      }
    }
  }
}


void choice(int j)  //選擇前進距離
{
    if(!go)
        {
        linetracking();
        delay(j*100);
        stopRL(10);
        turnR(6);
        advance(5);
        stopRL(10);
        go=true;}
    else
       {
        stopRL(0);
        go=true;}
}

void servo()   //隨機停下servo
{
  int a=random(0,2);
  if(a==0)
  {
    int b=random(11,181);
    for(pos = 10; pos <= b; pos += 1) 
  { myservo.write(pos);             
    delay(15);
    } 
  }
  else
  {
    int b=random(10,180);
    for(pos = 10; pos <= 180; pos += 1) 
  {                                  
    myservo.write(pos);             
    delay(15);                     
  } 
  for(pos = 180; pos>=b; pos-=1)      
  {                                
    myservo.write(pos);               
    delay(15);                       
  } 
  }
}


void loop()
{
  int cmd = Serial.read();  // 讀取藍芽訊號並於下方進行判斷
 


  switch(cmd)  // 執行藍芽對應指令
  {
    case 'W':// 前進並隨機選擇距離
      if(!decide)
      {  
        int t=random(1,4);
        if(t==1)
          choice(10); 
        else if(t==2)
          choice(20);
        else
          choice(35);
        decide=true;
      }
      else
        delay(100);  
        break;
 
    case 'A':  // servo旋轉並隨機停下
      digitalWrite(LaserPIN, HIGH);
      if(!servoOn)
      {
       servo();
       finish(buzzerPin);
       servoOn=true;
       }
      else
        delay(100);
      break;
        
    case 'D':  // 關閉laser 重置servo 
      digitalWrite(LaserPIN, LOW);
      myservo.write(10);
      cancel(buzzerPin);
      servoOn=false;
      break;
      
    case 'S':// 重新選擇前進距離
      decide=false;
      go=false;
      cancel(buzzerPin);
      break;

  }
}
