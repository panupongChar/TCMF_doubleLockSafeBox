#include <usbdrv.h>
#include <Wire.h> 
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
Servo myservo;

#define RQ_SET_LED 0
#define RQ_GET_SWITCH 1
#define RQ_GET_PW 2
#define RQ_SEND_RESULT 3

#define BTP !(digitalRead(PIN_PB0)&&digitalRead(PIN_PB1)&&digitalRead(PIN_PB2)&&digitalRead(PIN_PB3)&&digitalRead(PIN_PB4)&&digitalRead(PIN_PB5))

int i;
uint8_t password[8];
uint8_t unsubmit[8];
int index=0;
bool submit=false;
bool opened=false;
bool reset=true;
bool getreset=false;
unsigned long timecount;

void printsetting(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Setting...");
}

void printreset(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Password :");
}

void printpassword(){
  lcd.clear();
  lcd.setCursor(0,0);
  if(!submit){
    lcd.print("Enter Password :");
  }
  else{
    lcd.print(" Password Sent! ");
  }
  int a;
  for(a=0;a<index;a++){
    lcd.setCursor(a+4,1);
    if(password[a]==1){
      lcd.print("A");
    }
    else if(password[a]==2){
      lcd.print("B");
    }
    else if(password[a]==3){
      lcd.print("C");
    }
    else if(password[a]==4){
      lcd.print("D");
    }
  }
}

void printwrong(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Wrong Password");
}

void printopened(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("     Safebox");
  lcd.setCursor(0,1);
  lcd.print("     Opened");
}

void printclosed(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("     Safebox");
  lcd.setCursor(0,1);
  lcd.print("     Closed");
}

//////////////////////////////////////////////////////////////////////
usbMsgLen_t usbFunctionSetup(uint8_t data[8])
{
  usbRequest_t *rq = (usbRequest_t*)data;
  static uint8_t switch_state[6];

  if (rq->bRequest == RQ_SET_LED)
  {
    uint8_t led_val = rq->wValue.bytes[0];
    uint8_t led_no  = rq->wIndex.bytes[0];

    if (led_no == 0)
      digitalWrite(PIN_PD3, led_val);

    return 0;  // return no data back to host
  }
  else if (rq->bRequest == RQ_GET_SWITCH)
  {
    if (digitalRead(PIN_PB4) == HIGH) /* switch A is not pressed */ 
      switch_state[0] = 0;
    else
      switch_state[0] = 1;
    if (digitalRead(PIN_PB3) == HIGH) /* switch B is not pressed */ 
      switch_state[1] = 0;
    else
      switch_state[1] = 1;
    if (digitalRead(PIN_PB2) == HIGH) /* switch C is not pressed */ 
      switch_state[2] = 0;
    else
      switch_state[2] = 1;
    if (digitalRead(PIN_PB0) == HIGH) /* switch D is not pressed */ 
      switch_state[3] = 0;
    else
      switch_state[3] = 1;
    if (digitalRead(PIN_PB5) == HIGH) /* switch Back is not pressed */ 
      switch_state[4] = 0;
    else
      switch_state[4] = 1;
    if (digitalRead(PIN_PB1) == HIGH) /* switch Enter is not pressed */ 
      switch_state[5] = 0;
    else
      switch_state[5] = 1;
    /* point usbMsgPtr to the data to be returned to host */
    usbMsgPtr = (uint8_t*) &switch_state;

    /* return the number of bytes of data to be returned to host */
    return sizeof(switch_state);
  }
  else if (rq->bRequest == RQ_GET_PW){
    if(submit){
      usbMsgPtr = (uint8_t*) &password;
      //submit=false; //when do the full project comment out this line pls
      index=0;
    }
    else{
      usbMsgPtr = (uint8_t*) &unsubmit;
    }
    return sizeof(password);
  }
  else if(rq->bRequest == RQ_SEND_RESULT){
    if(submit){
      uint8_t result = rq->wValue.bytes[0];
      if(result==0){ //0 means wrong password
        digitalWrite(PIN_PD3, HIGH);
        submit=false;
        opened=false;
        myservo.write(90);
        printwrong();
        timecount=millis();
        getreset=true;
      }
      else if(result==1){ //1 means correct password (both hardpass and softpass)
        digitalWrite(PIN_PD3, LOW);
        submit=false;
        opened=true;
        myservo.write(0);
        printopened();
      }
    }
    return 0;
  }

  return 0;   /* nothing to do; return no data back to host */
}

//////////////////////////////////////////////////////////////////////
void setup()
{
    pinMode(PIN_PB0,INPUT_PULLUP);
    pinMode(PIN_PB1,INPUT_PULLUP);
    pinMode(PIN_PB2,INPUT_PULLUP);
    pinMode(PIN_PB3,INPUT_PULLUP);
    pinMode(PIN_PB4,INPUT_PULLUP);
    pinMode(PIN_PC1,INPUT);
    pinMode(PIN_PD3,OUTPUT);
    
    lcd.init();  //initialize the lcd
    lcd.backlight();  //open the backlight 
    myservo.attach(PIN_PD5);
    myservo.write(90);
    digitalWrite(PIN_PD3,HIGH);
    
    int i;
    for(i=0;i<8;i++){
      unsubmit[i]=0;
    }
    printsetting();
    usbInit();

    /* enforce re-enumeration of USB devices */
    usbDeviceDisconnect();
    delay(300);
    usbDeviceConnect();
}

//////////////////////////////////////////////////////////////////////
void loop()
{
  usbPoll();
  if(getreset&&millis()-timecount>1500){
    reset=true;
    getreset=false;
  }
  usbPoll();
  if(reset){
    printreset();
    reset=false;
  }
  usbPoll();
  if(!submit&&!opened){
    usbPoll();
    if(BTP){
      //digitalWrite(PIN_PD3, HIGH); //remove this line when lcd prompt
      //delay(5); //remove this line when lcd prompt
      if(!digitalRead(PIN_PB0)&&index<=7){ //if A pressed and password not full
        password[index]=1;
        index++;
        while(!digitalRead(PIN_PB0));
      }
      else if(!digitalRead(PIN_PB2)&&index<=7){ //if B pressed and password not full
        password[index]=2;
        index++;
        while(!digitalRead(PIN_PB2));
      }
      else if(!digitalRead(PIN_PB3)&&index<=7){ //if C pressed and password not full
        password[index]=3;
        index++;
        while(!digitalRead(PIN_PB3));
      }
      else if(!digitalRead(PIN_PB4)&&index<=7){ //if D pressed and password not full
        password[index]=4;
        index++;
        while(!digitalRead(PIN_PB4));
      }
      else if(!digitalRead(PIN_PB1)&&index>0){ //if BACK pressed and password not blank
        index--;
        while(!digitalRead(PIN_PB1));
      }
      else if(!digitalRead(PIN_PB5)&&index==8){ //if ENTER pressed and password is full
        submit=true;
        while(!digitalRead(PIN_PB5));
      }
      //digitalWrite(PIN_PD3, LOW); //remove this line when lcd prompt
      //delay(5); //remove this line when lcd prompt
      printpassword();
    }
  }
  else if(opened){
    usbPoll();
    if(digitalRead(PIN_PC1)){
      printclosed();
      timecount=millis();
      getreset=true;
      myservo.write(90);
      submit=false;
      opened=false;
    }
  }
}
