/*
 * Home Automation System - Remote Controlled Light Bulb
 * 
 * Circuit Components:
 * - Arduino board (e.g., Arduino Uno)
 * - IR Receiver (e.g., TSOP38238)
 * - Relay module (5V)
 * - Light bulb with socket
 * - Power source for light bulb (AC or DC depending on bulb)
 * - IR Remote control
 * - Resistors (220 ohm for LED indicators)
 * - Jumper wires
 * - Breadboard
 * 
 * Circuit Connections:
 * - IR Receiver: 
 *   - VCC to Arduino 5V
 *   - GND to Arduino GND
 *   - Signal to Arduino Digital Pin 11
 * - Relay Module:
 *   - VCC to Arduino 5V
 *   - GND to Arduino GND
 *   - IN to Arduino Digital Pin 7
 *   - COM and NO connected to light bulb circuit
 * - Status LED:
 *   - Anode to Arduino Digital Pin 13 through 220 ohm resistor
 *   - Cathode to GND
 */

#include <IRremote.h>

// Pin definitions
const int RECV_PIN = 11;    // IR receiver pin
const int RELAY_PIN = 7;    // Relay control pin
const int STATUS_LED = 13;  // Status LED pin

// Remote control button codes (these will vary based on your remote)
// You'll need to run an IR receiver test sketch to get your remote's codes
const unsigned long POWER_BUTTON = 0xFFA25D;  // Example code, replace with your remote's code
const unsigned long BRIGHTNESS_UP = 0xFF629D; // Example code, replace with your remote's code
const unsigned long BRIGHTNESS_DOWN = 0xFFE21D; // Example code, replace with your remote's code

// State variables
bool lightState = false;
int brightness = 255;  // For future PWM control if needed

// IR receiver setup
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
  
  // Initialize pins to OFF state
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(STATUS_LED, LOW);
  
  // Start the IR receiver
  irrecv.enableIRIn();
  
  Serial.println("Home Automation System - Remote Controlled Light");
  Serial.println("Press the power button on your remote to toggle the light");
}

void loop() {
  // Check if IR signal is received
  if (irrecv.decode(&results)) {
    processIRCommand(results.value);
    irrecv.resume(); // Receive the next value
  }
  
  // Update the status LED to match the light state
  digitalWrite(STATUS_LED, lightState ? HIGH : LOW);
  
  delay(100); // Small delay for stability
}

void processIRCommand(unsigned long command) {
  Serial.print("Command received: 0x");
  Serial.println(command, HEX);
  
  switch (command) {
    case POWER_BUTTON:
      toggleLight();
      break;
    case BRIGHTNESS_UP:
      // For future PWM implementation
      increaseBrightness();
      break;
    case BRIGHTNESS_DOWN:
      // For future PWM implementation
      decreaseBrightness();
      break;
    default:
      // Unknown command
      break;
  }
}

void toggleLight() {
  lightState = !lightState;
  digitalWrite(RELAY_PIN, lightState ? HIGH : LOW);
  
  Serial.print("Light turned ");
  Serial.println(lightState ? "ON" : "OFF");
}

void increaseBrightness() {
  // For future PWM implementation
  if (brightness < 255) {
    brightness += 25;
    if (brightness > 255) brightness = 255;
    Serial.print("Brightness increased to: ");
    Serial.println(brightness);
  }
}

void decreaseBrightness() {
  // For future PWM implementation
  if (brightness > 0) {
    brightness -= 25;
    if (brightness < 0) brightness = 0;
    Serial.print("Brightness decreased to: ");
    Serial.println(brightness);
  }
}
