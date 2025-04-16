#include <WiFi.h>

// WiFi credentials and server address
const char* ssid = "NETGEAR22";
const char* password = "greatoctopus400";
const char* serverIP = "192.168.0.31";

// Pin definitions
#define BUTTON_PIN 12
#define LED_PIN 2 // Adjust to your LED's connected pin

// Constants
const unsigned long DEBOUNCE_TIME = 50; // Debounce time in milliseconds

// Variables for debouncing
unsigned long lastDebounceTime = 0;
int lastButtonState = HIGH;
int buttonState;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  // Initialize WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int readButton = digitalRead(BUTTON_PIN);
  
  // Check for a button state change
  if (readButton != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
    // If the button state has changed:
    if (readButton != buttonState) {
      buttonState = readButton;
      
      // Button press logic
      if (buttonState == LOW) {
        Serial.println("Button Pressed!");
        if (sendRequest()) {
          // Turn on the LED if the server received the message
          digitalWrite(LED_PIN, HIGH);
          delay(20000); // LED on for 1 second
          digitalWrite(LED_PIN, LOW);
        }
      }
    }
  }
  
  lastButtonState = readButton;
}

bool sendRequest() {
  WiFiClient client;
  const int maxRetries = 10; // Maximum number of connection attempts
  int attempt = 0;
  bool connected = false;

  // Attempt to connect to the server with retries
  while (!connected && attempt < maxRetries) {
    if (client.connect(serverIP, 80)) {
      connected = true; // Successful connection
      Serial.println("Connected to Server");

      // Send HTTP request to the server
      client.println("GET / HTTP/1.1");
      client.println("Host: " + String(serverIP));
      client.println("Connection: close");
      client.println();

      // Wait for server response
      while (client.connected() && !client.available()) {
        delay(1); // Small delay to allow data to arrive
      }

      // Read and print the server response (basic check)
      if (client.available()) {
        String response = client.readStringUntil('\r');
        Serial.println("Server Response: " + response);
        client.stop(); // Close the connection
        return true; // Indicate success
      }
    } else {
      attempt++;
      Serial.print("Connection attempt ");
      Serial.print(attempt);
      Serial.println(" failed, retrying...");
      delay(1000); // Wait a bit before retrying
    }
  }

  if (!connected) {
    Serial.println("Connection to Server Failed after retries");
    return false; // Indicate failure after all retries
  }
  return false; // Fallback return statement
}
