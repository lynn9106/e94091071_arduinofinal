# e94091071_arduinofinal
> *設定完成與重新選擇時buzzer的聲音*

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
    
> *使車子前進、右轉、左轉、停止、後退*

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

    void turnL(int e)    //左轉
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
    
> *使servo隨機停下以選擇目標*
>
> > 隨機取a值，若為0，則使servo由10開始轉至11~180任一處
> > 
> >     void servo()  
> >     {
> >       int a=random(0,2);
> >       if(a==0)
> >       {
> >         int b=random(11,181);
> >         for(pos = 10; pos <= b; pos += 1) 
> >       { myservo.write(pos);             
> >         delay(15);
> >         } 
> >       }
> 
> > 若為1，則使servo由10開始轉至180，再由180轉至10~179任一處
> > 
> >       else
> >       {
> >         int b=random(10,180);
> >         for(pos = 10; pos <= 180; pos += 1) 
> >       {                                  
> >         myservo.write(pos);             
> >         delay(15);                     
> >       } 
> >       for(pos = 180; pos>=b; pos-=1)      
> >       {                                
> >         myservo.write(pos);               
> >         delay(15);                       
> >       } 
> >       }
> >     }

> *讀取藍芽訊號並判斷*
> 
>     int cmd = Serial.read();
> *執行對應指令*
> > **車子前進並隨機選擇前進距離**
> > 
> >     case 'W':
> >     if(!decide)
> >     {  
> >     int t=random(1,4);
> >     if(t==1)
> >     choice(10); 
> >     else if(t==2)
> >     choice(20);
> >     else
> >     choice(35);
>       
> > 使decide為true以結束指令迴圈
> >  
> >     decide=true;
> >     }
> >     else
> >     delay(100);  
> >     break;
> 
> > **開啟servo與laser以選定目標，並在servo停下時令buzzer發出完成的提示聲**
> >     
> >     case 'A':
> >     digitalWrite(LaserPIN, HIGH);
> >     if(!servoOn)
> >     {
> >     servo();
> >     finish(buzzerPin);
> >     servoOn=true;
> >     }
> 
> > 使servoOn為true以結束指令迴圈
> >     
> >     else
> >     delay(100);
> >     break;
