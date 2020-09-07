# 1.Digital输入与输出

```c
pinMode(pin,mode);
```

配置引脚模式

**pin**：所要配置的引脚

**mode**：设置的模式；`INPUT` 输入模式；或`OUTPUT`输出模式

```c
digitalWrite(pin,HIGH);
```

设置一个输出模式引脚的电平

**pin**：所要设置的引脚；`HIGH` 高电平；或`LOW`低电平

```c
digitalRead(pin)
```

读取一个输入模式引脚的电平

返回值：0 低电平接通GND时； 1 高电平接通5V或3.3V时

----

# 2.Analog模拟输入ADC与模拟输出PWM

```
analogRead(pin);
```

ADC模拟读取

读取模拟输入中针脚的值

**pin**；所要读取的模拟针脚

返回值；范围0～1023

```
analogWrite(pin,value)
```

PWM模拟输出，输出模拟电压

**pin**：所要输出PWM的针脚

**value**：输出的占空比 范围 0～255

无需定义引脚属性

# 3.UART通信

```
Serial.begin(115200);
```

设置UART的端口通信波特率（传递速度）

```
Serial.print(str);
Serial.println(str);
```

传输数据 

Serial.print(str,HEX);十六机制

Serial.print(str,OCT);八进制

Serial.print(str,BIn);二

```
Serial.available();
```

判断是串行端口否接收到数据

```
Serial.read();
```

读取串行端口接受到的数据，返回数据，int型



# 4.Pulse脉冲

```
pulseln(pin,state,timeout);
```

读取引脚的脉冲时间长度

**pin**：读取输入模式的引脚

**state**：脉冲响应状态 HIGH或LOW

**timeout**：超过时间 超过时间还未读到则返回0