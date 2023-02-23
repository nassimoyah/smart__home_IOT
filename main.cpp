

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define  trig  D2
#define  echo  D1

long duration;
int distance;
int GAZ_val ;
// You should get Auth Token in the Blynk App.

char auth[] = "get the auth code from blynk platfor "; 

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "your SSID ";
char pass[] = "PASSWORD ";

BlynkTimer timer;

void setup()
{
  // Debug console
  pinMode(trig, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echo, INPUT);   // Sets the echoPin as an Inpu
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();  // RUN BLYNK EVENT
  timer.run();
}
void FUNCTIONS()
{
  digitalWrite(trig, LOW);   // Makes trigPin low
  delayMicroseconds(2);       // 2 micro second delay

  digitalWrite(trig, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trig, LOW);   // trigPin low

  duration = pulseIn(echo, HIGH);   //Read echo pin, time in microseconds
  distance = duration * 0.034 / 2;   //Calculating actual/real distance

  Serial.print("Distance = ");        //Output distance on arduino serial monitor
  Serial.println(distance);
  distance = map(distance,0,10,100,0) ;
  Blynk.virtualWrite(V1, distance); /// SEND DATA TO THE CLOUD 
  

  
  
  GAZ_val = analogRead(A0) ;
 
  Blynk.virtualWrite(V2, GAZ_val); /// SEND GAZ DATA 
 

}
