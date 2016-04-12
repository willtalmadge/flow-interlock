#include <ESP8266WiFi.h>

const char WiFiSSID[] = "Li Lab";
const char WiFiPSK[] = "$pinOptics";

const int LED_PIN = 5; // Thing's onboard, green LED
const int ANALOG_PIN = A0; // The only analog pin on the Thing
const int COUNTING_PIN = 2; // Digital pin for counting

volatile int count; // Counted number in a period
byte Status = LOW;
unsigned long checktime; //time to check the count and refresh
unsigned long starttime; //time to make a change on the pulses
int Mcount; //record the max counting number of 1 second during the working time
WiFiServer server(80);

void initHardware()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(COUNTING_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);
  // Don't need to set ANALOG_PIN as input, 
  // that's all it can be.
}

void connectWiFi()
{
  // Set WiFi mode to station (as opposed to AP or AP_STA)
  WiFi.mode(WIFI_STA);

  // WiFI.begin([ssid], [passkey]) initiates a WiFI connection
  // to the stated [ssid], using the [passkey] as a WPA, WPA2,
  // or WEP passphrase.
  WiFi.begin(WiFiSSID, WiFiPSK);
}

void counting(){
  count++;
}

void setup() {
  initHardware();
  connectWiFi();
  server.begin();
  Serial.print("server is at ");
  Serial.println(WiFi.localIP());
  count = 0;
  Mcount = 0;
  attachInterrupt(digitalPinToInterrupt(COUNTING_PIN), counting, RISING);
  starttime = 0;
  checktime = 0;
  //when there is a rising, counted number+1
}
WiFiClient client = server.available();
void loop() { 
  if(millis() - checktime >= 1000){
   // if(count>=Mcount){
      Mcount = count;
      count = 0;
   checktime = millis();
   // }
  }
    // give the web browser time to receive the data
    if(Mcount>=50){
      digitalWrite(LED_PIN, HIGH);
    }
    else{
      digitalWrite(LED_PIN, LOW);
    }
  // put your main code here, to run repeatedly:
}
