
#include <NewPing.h>


bool ActiveBuzzer=false;
bool Activeled=false;
bool SystemActive=false;
bool ActiveLaser=false;
int ActiveDistance=0;
int DistanceTemp=0;
int AlarmDistance=0;
unsigned long Time=0;
unsigned long TimeForBuzzer =0;
int Second=0;
int CurrentDistance=0;
float filter=1000;

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 500 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define LED_PIN 7 //sign led pin
#define BUZZER_PIN 2 //buzer pin
#define INDICATION_PIN 4 //green led
#define LASER_PIN 3

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode (LED_PIN, OUTPUT);
  pinMode (BUZZER_PIN, OUTPUT);
}

void loop() {
  CurrentDistance=sonar.ping_cm();
  if ( CurrentDistance ==0)
     CurrentDistance=500;

  filter = 0.9 * filter + (float)CurrentDistance * 0.1;

  CurrentDistance = (int)filter;
  
  if(millis()-Time>999){
    Time=millis();
    
    if (CurrentDistance<AlarmDistance){
      Second++;
    }
    else{
      Second=0;
    }
  }
  
 
    
  
    DistanceTemp = analogRead(A0);
    AlarmDistance = map(DistanceTemp,0,1024,150,500);
    
    if (CurrentDistance<AlarmDistance)
    {
     
     Activeled=true; 
          
      if (Second>4){
        ActiveBuzzer=true;  //turn buzzer on
    }
    
    }
    else
    {
     ActiveLaser=false;
     Activeled=false;
     ActiveBuzzer=false;
   }
  
  
  
    //Actuate
   if (ActiveLaser){
     digitalWrite(3,HIGH);
    }
    else{
     digitalWrite(3,LOW);
    }
    
  
    if (Activeled){
     digitalWrite(7,HIGH);
    }
    else{
     digitalWrite(7,LOW);
    }

    if (ActiveBuzzer){
      if(Second>0)
      {
        
      digitalWrite(BUZZER_PIN,HIGH);
      }
    }
    else{
      digitalWrite(BUZZER_PIN,LOW);
    }

  
    
  
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print("Ping: ");
    Serial.print(CurrentDistance); // Send ping, get distance in cm and print result (0 = outside set distance range)
    Serial.println("cm");
    Serial.print("ActiveBuzzer: ");
     Serial.println(ActiveBuzzer);
    Serial.print("Activeled: ");
     Serial.println(Activeled);
    Serial.print("SystemActive: ");
     Serial.println(SystemActive);
    Serial.print("ActiveLaser: ");
     Serial.println(ActiveLaser);
    Serial.print("Second: ");
     Serial.println(Second);
    Serial.print("DistanceTemp: ");
     Serial.println(DistanceTemp);
    Serial.print("AlarmDistance: ");
     Serial.println(AlarmDistance);
     Serial.println("****************************************: ");
}
