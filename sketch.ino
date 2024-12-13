#include <WiFi.h>
#include <HTTPClient.h>

#define green_led 2 //Pin used to control green led
#define red_led 40 //Pin used to control red led
#define yellow_led 9 //Pin used to control yellow led

const int buttonPin = 18;  // the number of the pushbutton pin
int buttonState = 0;  // variable for reading the pushbutton status

const int ldrPin = 4;  // the number of the ldr pin
int threshold=600;

void setup() {

  //Initial configuration of the pins to control the leds as outputs of ESP32
  pinMode(yellow_led,OUTPUT);
  pinMode(green_led,OUTPUT);
  pinMode(red_led,OUTPUT);

  // Inputs initialization
  pinMode(buttonPin, INPUT); // Initialize the pushbutton pin as an input

  digitalWrite(yellow_led, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(red_led, LOW);


  Serial.begin(9600); //Debug configuration by serial interface between ESP and computer with baud rate of 9600

  WiFi.begin("Wokwi-GUEST", ""); //WiFi connection open with SSID Wokwi-GUEST

  while (WiFi.status() != WL_CONNECT_FAILED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi"); //Considering out of the above loop, ESP32 now is connected to WiFi (another option is to put this command in the if statement below)

  // Verify button state
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("Button pressed!");
  } else {
    Serial.println("Button not pressed!");
  }

  if(WiFi.status() == WL_CONNECTED){ // If ESP32 is connected to the internet
    HTTPClient http;

    String serverPath = "http://www.google.com.br/"; // Endpoint of HTTP request

    http.begin(serverPath.c_str());

    int httpResponseCode = http.GET(); // Result code of HTTP request

    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
      }
      http.end();
    }

  else {
    Serial.println("WiFi Disconnected");
  }
}

void loop() {
  int ldrstatus=analogRead(ldrPin);

  if(ldrstatus<=threshold){
    Serial.print("its dark turn on led");
    Serial.println(ldrstatus);

  digitalWrite(green_led, HIGH);  
  delay(2000);                   
  digitalWrite(green_led, LOW);    

  digitalWrite(yellow_led, HIGH);
  delay(2000);                   
  digitalWrite(yellow_led, LOW);  

  digitalWrite(red_led, HIGH);
  delay(2000);                    
  digitalWrite(red_led, LOW);

  }else{
    Serial.print("its bright turn off light");
    Serial.println(ldrstatus);
  }
}