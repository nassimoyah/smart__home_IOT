
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define  trig  D2
#define  echo  D1

long duration;
int distance;
int pot_val ;
// You should get Auth Token in the Blynk App.

char auth[] = "0oqPUuQw20TzK-j02IWac5QJtfcYESRx"; 

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AndroidAP1053";
char pass[] = "enah9098";

BlynkTimer timer;
WidgetLCD lcd(V0);
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
  Blynk.run();
  timer.run();
}
void sendSensor()
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

  Blynk.virtualWrite(V1, distance);
  pot_val = analogRead(A0) ;
  Blynk.virtualWrite(V2, pot_val);
  lcd.print(0, 0, "voidloopRobotech"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(0, 1, "Distance: " + String(distance) + "cm  ");
  delay(1000); 

}

