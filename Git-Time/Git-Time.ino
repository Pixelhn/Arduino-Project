//任何命令下达前均需要确保模块属于“OK”待定状态，且UART缓存字符数量为0

void * getchars(int start,int charslength);
void cheakchar(int lastchar);
void bootesp();

int subyte, i=0;
int *chars;

void setup() {
    Serial.begin(115200);
    bootesp();
}

void loop(){
    delay(70);
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
}
    
void bootesp(){//启动与初始化
    Serial.println("AT+RST");
    cheaklastchar(121);//y
    Serial.println("ATE0");//关闭回显
    cheaklastchar(75);//K
    Serial.println("AT+CWMODE=1");//STA模式
    cheaklastchar(75);//K
    Serial.println("AT+CWJAP_CUR=\"131\",\"tjlg28-131\"");//连接WiFi
    cheaklastchar(75);//K
    Serial.println("AT+CIPSNTPCFG=1,8,\"ntp.aliyun.com\",\"ntp1.aliyun.com\"");//配置NTP
    cheaklastchar(75);//K
    Serial.println("AT+CIPSTART=\"TCP\",\"123.57.50.208\",8887");   
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
