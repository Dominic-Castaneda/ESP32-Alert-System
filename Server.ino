#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "NETGEAR22";
const char* password = "greatoctopus400";

WebServer server(80);

// Pin definitions
#define BUZZER_PIN 16

// Buzzer control variables
unsigned long buzzerStartTime = 0;
const unsigned long buzzerDuration = 1000; // Buzzer on for 1 second
bool buzzerActive = false;

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Print the IP address
    Serial.print("Server IP Address: ");
    Serial.println(WiFi.localIP());

    pinMode(BUZZER_PIN, OUTPUT); // Set the buzzer pin as an output

    // Define the handling function for the path "/"
    server.on("/", HTTP_GET, []() {
        Serial.println("Received a request!");
        buzzerStartTime = millis(); // Start buzzer
        buzzerActive = true;
        server.send(200, "text/plain", "Button was pressed!");
    });

    // Start the server
    server.begin();
}

void loop() {
    // Handle incoming client requests
    server.handleClient();

    // Non-blocking buzzer logic
    if (buzzerActive && (millis() - buzzerStartTime >= buzzerDuration)) {
        digitalWrite(BUZZER_PIN, LOW); // Turn buzzer off
        buzzerActive = false; // Reset buzzer state
    } else if (buzzerActive) {
        digitalWrite(BUZZER_PIN, HIGH); // Keep the buzzer on
    }
}
