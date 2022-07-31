//NHJ-K


#define Hall_Sensor A0
#define motor1pin1 5
#define motor1pin2 6
#define motor2pin1 9
#define motor2pin2 10

const bool USE_MPH = true; 
const int WHEEL_DIAMETER = 18; 
const int RPM_SAMPLE_PERIOD = 10; 
const int MIN_KPH = 4;
const int MIN_HIEGHT = 14; 
const int MAX_HIEGHT = 50; 

int read_speed(){
  static bool firstTime = true; 
    static long thisMagValue = 0;
    static int rpm = 0;
    static long mph = 0;
    static long kph = 0;
    static float magnetCount = 0.00; 
    static unsigned long timeOld = 0; 

    long previousMagValue = thisMagValue; 
    thisMagValue = analogRead(Hall_Sensor);

    if(!firstTime) 
    {
        //delay(500);
        int change = abs(thisMagValue-previousMagValue);

        if (change > 1000)
        {
            ++magnetCount;
        }
        // Every RPM_SAMPLE_PERIOD seconds we reset the magnetData array to 0 
        if(floor((millis()-timeOld)/1000)==RPM_SAMPLE_PERIOD)
        {
            timeOld = millis();
            magnetCount = 0;
        }
        if(abs((((float)(millis()-timeOld)/1000)/60))>0.01)
        {
            rpm = (magnetCount/2) / (((float)(millis()-timeOld)/1000)/60);
        }
        delay(15);
        kph = ((WHEEL_DIAMETER * PI)* rpm) / 1666.67; 
        //Serial.println("KPH :");
        //Serial.print(kph);
        }

    firstTime = false;
    return(kph);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1,OUTPUT);
  pinMode(motor1pin2,OUTPUT);
  pinMode(motor2pin1,OUTPUT);
  pinMode(motor2pin2,OUTPUT);
  Serial.begin(115200);
  digitalWrite(motor1pin1,!LOW);
  digitalWrite(motor1pin2,!LOW);
  digitalWrite(motor2pin1,!LOW);
  digitalWrite(motor2pin2,!LOW);
}
void loop() {
  
  // put your main code here, to run repeatedly:
  long kph1 = read_speed();
  Serial.println(kph1);
  if(kph1==0){
    digitalWrite(motor1pin1,!LOW);
  digitalWrite(motor1pin2,!LOW);
  digitalWrite(motor2pin1,!LOW);
  digitalWrite(motor2pin2,!LOW);
  }
  if(kph1<3 && kph1>=1){
     digitalWrite(motor1pin1,!HIGH);
     digitalWrite(motor1pin2,!LOW);
     digitalWrite(motor2pin1,!HIGH);
     digitalWrite(motor2pin2,!LOW);
  }
  if(kph1>=3 && kph1 <5){
    digitalWrite(motor1pin1,!LOW);
     digitalWrite(motor1pin2,!HIGH);
     digitalWrite(motor2pin1,!LOW);
     digitalWrite(motor2pin2,!HIGH);
  }
  //delay(100);
}
