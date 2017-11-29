#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = <SSID>;
const char* password = <PASSWORD>;

// constants won't change. They're used here to set pin numbers:
const int buttonPin = D5;     // button CALL API
const int buttonPin2 = D6;    // button SWITCH API
const int ledPin =  LED_BUILTIN;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
// variables will change:
int buttonState2 = 0;         // variable for reading the pushbutton status

// compteur
int cpt = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin2, INPUT_PULLUP);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
}

void callAPICoffee() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://serlibutton.cleverapps.io/api/button/button-coffee");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
 
    }
 
    http.end();   //Close connection
 
  }
}

void callAPIApero() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://serlibutton.cleverapps.io/api/button/button-apero");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
 
    }
 
    http.end();   //Close connection
 
  }
}

void callPlaySoundSonosAPI() {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://192.168.86.10:5005/button-sound");
    http.GET();                                                                 
    http.end();   //Close connection
 
  }
}

void callSaySonosAPI() {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://192.168.86.10:5005/button-say");
    http.GET();                                                                 
    http.end();   //Close connection
 
  }
}

void loop() {
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // read the state of the pushbutton value:
  buttonState2 = digitalRead(buttonPin2);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // RESTART CPT
    cpt = 0;
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    if(buttonState2 == 0) {
      if(cpt == 0) {
        // INC CPT +1
        cpt = 1;
        // CALL API SAY SONOS
        callSaySonosAPI();
      }
    } else {
      if(cpt == 0) {
        // INC CPT +1
        cpt = 1;
        // CALL API PLAY SOUND SONOS
        callPlaySoundSonosAPI();
      }
    }
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  delay(100);
}
