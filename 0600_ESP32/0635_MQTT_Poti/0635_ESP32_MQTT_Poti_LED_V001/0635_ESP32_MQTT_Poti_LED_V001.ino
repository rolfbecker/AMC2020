/*********
  Rolf Becker, 2020-06-25
  Inspired by Rui Santos from https://randomnerdtutorials.com  
*********/

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

// Replace the next variables with your SSID/Password combination
const char* ssid = "GUEST";
const char* password = "Hello World!";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server   = "hsrw.space";
const char* mqtt_username = "user";
const char* mqtt_password = "mqtt";
const unsigned int mqtt_bufsize = 100;

// *****************************************************************
// CHANGE batman IN THE FOLLOWING THREE CHAR ARRAYS TO ANOTHER NAME!
// *****************************************************************
const char* myname = "batman";
const char* poti_topic = "/amc2020/batman/poti"; // topic to publish under
const char* led_topic = "/amc2020/batman/led";   // topic to subscribe

// LED Pin (Digital out, subscribe), Poti Pin (Analog in, publish)
const int ledPin  =  4;
const int potiPin = 34;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

// Environment variables to be measured and transmitted.
float temperature = 0;
float humidity = 0;
int potiValue = 0;


void setup() {
  Serial.begin(115200);

  setup_wifi();

  client.setBufferSize (mqtt_bufsize);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(ledPin, OUTPUT);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int len) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < len; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic sub_topic, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == led_topic) {
    Serial.print("Changing LED to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(myname, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(led_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    
    potiValue = analogRead(potiPin);
    
    potiValue /= 16; // Why am I doing this?
    
    char potiString[8];
    dtostrf(potiValue, 1, 2, potiString);
    Serial.print("Poti: ");
    Serial.println(potiString);
    client.publish(poti_topic, potiString);
  }
}
