int led_1_pin = 8;
int led_2_pin = 10;
int buzz_pin = 2;
int push_button_white = 6;
int push_button_red = 5;
unsigned long debounceDelay = 30;
int lastButtonState;
bool button_red_pressed = false;
unsigned long lastDebounceTime;




//Pomodoro vars 

unsigned long Start_time ;
bool timer_on = false;
unsigned long Duration = 20;
//study time
const long Highest = 45;
const long Normal = 20;
unsigned long last_duration;
//break time
const long Highest_break  = 20;
const long Lowest_break  = 5;
unsigned long last_break_duration ;
 // time before setting to 5
int stopped_times = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led_1_pin,OUTPUT);
  pinMode(led_2_pin,OUTPUT);
  pinMode(buzz_pin,OUTPUT);
  pinMode(push_button_white, INPUT);
  pinMode(push_button_red, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int CurrentbuttonState = digitalRead(push_button_red);
  
  if (CurrentbuttonState != button_red_pressed && millis()- lastDebounceTime >= debounceDelay){
    Serial.println("[RED BUTTON] change in state");

    button_red_pressed =  !button_red_pressed;
    if (button_red_pressed && !timer_on){ 
      Serial.println("[RED BUTTON] Entered te LOOP");
      digitalWrite(buzz_pin, HIGH);
      delay(500);
      digitalWrite(buzz_pin, LOW);
      Start_timer();
    }

    lastDebounceTime =  millis();
  }
  
  if (timer_on){
    Check_timer(Duration);
  }

  
  
}

void Start_timer(){
  digitalWrite(led_2_pin, HIGH);
  digitalWrite(led_1_pin,LOW);
  Start_time = millis();
  timer_on = true;
  Serial.println("[TIMER] Timer has been Started !");
}

void Check_timer(unsigned long duration){
  duration = duration * 60 * 1000;
  unsigned long current_time = millis();
  Serial.println("[TIMER] time is " + String(current_time - Start_time));
  if (current_time - Start_time >= duration){
    Stop_timer();
  }
}

void Stop_timer(){
  Serial.println("[TIMER] Timer has been Stopped !");
  timer_on = false;
  stopped_times += 1;
  if (stopped_times % 2 !=0 ){
    last_duration = Duration;
    Serial.println("[TIMER] SET to Break time !");
    Duration = last_break_duration + 5;
    if (Duration > Highest_break){
      Duration = Lowest_break;
    }
  }
  else{
    last_break_duration = Duration;
    Serial.println("[TIMER] SET to Study time !");
    Duration = last_duration + 5;
    if (Duration > Highest){
      Duration = Normal;
    }
  }
  digitalWrite(led_1_pin, HIGH);
  digitalWrite(led_2_pin, LOW);
  digitalWrite(buzz_pin, HIGH);
  delay(400);
  digitalWrite(buzz_pin, LOW);
  delay(300);
  digitalWrite(buzz_pin, HIGH);
  delay(300);
  digitalWrite(buzz_pin, LOW);
}
