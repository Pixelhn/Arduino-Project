//任何命令下达前均需要确保模块属于“OK”待定状态，且UART缓存字符数量为0
#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);//LCD

void * getchars(int start,int charslength);
void cheakchar(int lastchar);
void bootesp();

int subyte, i=0;
int *chars;
char displaychars;

void setup() {
    pinMode(13,OUTPUT);
    digitalWrite(13,LOW);
    Serial.begin(115200);
    bootesp();
    lcd.init();                  
    lcd.backlight();
    
}

void loop(){
    Serial.println("AT+CIPSNTPTIME?");
    delay(7);
    chars=getchars(58,24);
    cheaklastchar(75);//K
    Serial.println("AT+CIPSEND=24");
    cheaklastchar(62);//>
    for(i=0;i<24;i++){
        Serial.write(*(chars+i));
    }
    Serial.print("\r");
    cheaklastchar(75);//75
    lcd.clear();
    lcd.setCursor(4, 0);
    for(i=11;i<20;i++){
      displaychars = *(chars+i);
      lcd.print(displaychars);
    }  
}
    
void bootesp(){//启动与初始化
    Serial.println("AT+RST");
    cheaklastchar(121);//y
    Serial.println("ATE0");//关闭回显
    cheaklastchar(75);//K
    Serial.println("AT+CWMODE=1");//STA模式
    cheaklastchar(75);//K
    Serial.println("AT+CWJAP_CUR=\"SSID\",\"PASSWORD\"");//连接WiFi
    cheaklastchar(75);//K
    Serial.println("AT+CIPSNTPCFG=1,8,\"ntp.aliyun.com\",\"ntp1.aliyun.com\"");//配置NTP
    cheaklastchar(75);//K
    Serial.println("AT+CIPSTART=\"TCP\",\"IP\",PORT");   
    cheaklastchar(75);//K
}

void  cheaklastchar(int lastchar){//强制检索最后字符
    int subyte;
    for(subyte=Serial.read();1;subyte=Serial.read()){//检索字符
        if(subyte==lastchar){
            subyte=Serial.read();
            subyte=Serial.read();
            break;
        }
    }
}

void * getchars(int start,int charslength){//以标志字符出现后开始截取一定长度字符
    int subyte;
    static int needchars[24];
    for(subyte=Serial.read();!(subyte==start);subyte=Serial.read()){
    } 
    for(i=0;i<charslength;i++){
      needchars[i]=Serial.read();
    }
    return needchars;
}  