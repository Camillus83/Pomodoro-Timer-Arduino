//pomodoro timer for arduino by Kamil Richter
#include <LiquidCrystal.h> // library for LCD

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int workTime;
int minutesLeft;
unsigned long currentTime;
unsigned long lastTime;
const int setButtonPin=6; 
const int startButtonPin=7;
const int buzzerPin=8;
static int a=0; //by this variable program will know what will happen next, break or work

void setup() {
  lcd.begin(16, 2);
  pinMode(setButtonPin, INPUT_PULLUP);
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  lcd.setCursor(4,0);
  lcd.print("Pomodoro");
  lcd.setCursor(5,1);
  lcd.print("Timer");
}

void loop(){
    workTime=0;
    delay(5000); //delay for showing title
    display(); 
    lastTime=millis();
    countdown(minutesLeft);
    buzzer(buzzerPin);
    lcd.clear();
}
// function that allows you to set time for work/break by set button,
// start button confirms time. When time is over 60 minutes, program returns time at
// 0 minutes again. The interval is 5 minutes.

int timeSet(int time){
    while(digitalRead(startButtonPin) == HIGH){
        if(digitalRead(6) == LOW){
            time=time+5;
            delay(200);
        } else {delay(100);}
    lcd.setCursor(3,1);
    if(time<10)
     {
     lcd.print("0");
     lcd.print(time);}
    else{lcd.print(time);}
    if(time>60)
    {
      time=0;
      continue;}
    }
    return time;
}
// function to countdown work/break time. It uses a millis() function to deduct seconds
void countdown(int time){
    lastTime=millis();
    time=time-1;
    int secondsLeft=60;
    while(time >= 0 ){
    currentTime=millis();
    if((currentTime-lastTime) >= 1000){
        secondsLeft=secondsLeft-1;
        lcd.setCursor(5,1);
        if(time<10){lcd.print("0");}
    lcd.print(time);
    lcd.setCursor(7,1);
    lcd.print(":");
    if(secondsLeft<10){lcd.print("0");}
    lcd.print(secondsLeft);
    lastTime=currentTime;
    if(secondsLeft==0){
        time=time-1;
        secondsLeft=60;
       }
     }  
    }
}
// function to beep when time is over
void buzzer(int pin){
   digitalWrite(pin, HIGH); // when worktime is over buzzer will beep
   delay(3000);
   digitalWrite(pin, LOW);
}
// function to display settings menu, where loop is over a increment. So when work time
// ends, break time starts.
void display(){
lcd.setCursor(1,0);
    lcd.print("Set ");
    if(a%2==0){
        lcd.print("work time: ");
    }
    else { lcd.print("break time"); }
    lcd.setCursor(3,1);
    lcd.print(workTime);
    lcd.print("  minutes");
    minutesLeft=timeSet(workTime);
    lcd.clear();
  	lcd.setCursor(1,0);
    if(a%2==0){
  	lcd.print("Time to focus:");}
      else{lcd.print("Time for break: ");}
  	lcd.setCursor(5, 1);
  	if(minutesLeft<10)
     {
     lcd.print("0");
     }
    lcd.print(minutesLeft);
    lcd.print(":00");
    a=a+1;
}
