# e94091071_arduinofinal
>設定完成與重新選擇時buzzer的聲音

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
    
>使車子前進、右轉、左轉、停止、後退

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
