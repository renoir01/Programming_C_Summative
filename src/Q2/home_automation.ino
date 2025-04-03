/*
 * Agricultural IoT Automation System
 * 
 * This system demonstrates a smart agricultural automation solution that uses
 * IR remote control to manage irrigation and environmental controls in a greenhouse
 * or field setting. It showcases embedded systems programming for agricultural technology.
 * 
 * Circuit Components:
 * - Arduino board (e.g., Arduino Uno)
 * - IR Receiver (e.g., TSOP38238) for remote control input
 * - Relay modules (5V) for controlling irrigation valves and environmental systems
 * - Soil moisture sensors for automated irrigation decisions
 * - Temperature and humidity sensors (DHT22) for climate monitoring
 * - Status LEDs for system state indication
 * - Optional: LCD display for real-time data visualization
 * 
 * Circuit Connections:
 * - IR Receiver: 
 *   - VCC to Arduino 5V
 *   - GND to Arduino GND
 *   - Signal to Arduino Digital Pin 11
 * - Relay Modules:
 *   - VCC to Arduino 5V
 *   - GND to Arduino GND
 *   - IN1 (Irrigation) to Arduino Digital Pin 7
 *   - IN2 (Fan) to Arduino Digital Pin 6
 *   - IN3 (Heater) to Arduino Digital Pin 5
 * - Soil Moisture Sensor:
 *   - VCC to Arduino 5V
 *   - GND to Arduino GND
 *   - Analog Out to Arduino Analog Pin A0
 * - DHT22 Temperature/Humidity Sensor:
 *   - VCC to Arduino 5V
 *   - GND to Arduino GND
 *   - Data to Arduino Digital Pin 2
 * - Status LEDs:
 *   - Irrigation LED: Digital Pin 13 through 220 ohm resistor
 *   - Fan LED: Digital Pin 12 through 220 ohm resistor
 *   - Heater LED: Digital Pin 8 through 220 ohm resistor
 */

#include <IRremote.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
const int RECV_PIN = 11;       // IR receiver pin
const int IRRIGATION_PIN = 7;  // Irrigation valve relay
const int FAN_PIN = 6;         // Ventilation fan relay
const int HEATER_PIN = 5;      // Heating system relay
const int IRRIGATION_LED = 13; // Irrigation status LED
const int FAN_LED = 12;        // Fan status LED
const int HEATER_LED = 8;      // Heater status LED
const int MOISTURE_SENSOR = A0; // Soil moisture sensor
const int DHT_PIN = 2;         // DHT22 temperature/humidity sensor

// Remote control button codes (these will vary based on your remote)
// You'll need to run an IR receiver test sketch to get your remote's codes
const unsigned long IRRIGATION_TOGGLE = 0xFFA25D;  // Example code for irrigation control
const unsigned long FAN_TOGGLE = 0xFF629D;         // Example code for fan control
const unsigned long HEATER_TOGGLE = 0xFFE21D;      // Example code for heater control
const unsigned long AUTO_MODE = 0xFF22DD;          // Example code for automatic mode
const unsigned long MANUAL_MODE = 0xFF02FD;        // Example code for manual mode
const unsigned long DATA_DISPLAY = 0xFFC23D;       // Example code for data display

// System state variables
bool irrigationState = false;
bool fanState = false;
bool heaterState = false;
bool autoModeEnabled = false;
unsigned long lastSensorReadTime = 0;
const unsigned long SENSOR_READ_INTERVAL = 5000; // Read sensors every 5 seconds in auto mode

// Sensor thresholds for automatic control
const int DRY_THRESHOLD = 500;      // Soil moisture threshold for irrigation
const float TEMP_HIGH_THRESHOLD = 30.0; // Temperature threshold for fan (Celsius)
const float TEMP_LOW_THRESHOLD = 15.0;  // Temperature threshold for heater (Celsius)

// Sensor data variables
int soilMoisture = 0;
float temperature = 0.0;
float humidity = 0.0;

// Initialize sensors and display
DHT dht(DHT_PIN, DHT22);
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

// IR receiver setup
IRrecv irrecv(RECV_PIN);
decode_results results;

/**
 * Setup function - initializes the system
 */
void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(IRRIGATION_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(IRRIGATION_LED, OUTPUT);
  pinMode(FAN_LED, OUTPUT);
  pinMode(HEATER_LED, OUTPUT);
  
  // Initialize pins to OFF state
  digitalWrite(IRRIGATION_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(HEATER_PIN, LOW);
  digitalWrite(IRRIGATION_LED, LOW);
  digitalWrite(FAN_LED, LOW);
  digitalWrite(HEATER_LED, LOW);
  
  // Initialize sensors
  dht.begin();
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AgriTech System");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  
  // Start the IR receiver
  irrecv.enableIRIn();
  
  Serial.println("Agricultural IoT Automation System");
  Serial.println("Use remote to control irrigation, ventilation, and heating");
  Serial.println("Auto mode will control systems based on sensor readings");
  
  delay(2000);
  updateLCD();
}

/**
 * Main loop function
 */
void loop() {
  // Check if IR signal is received
  if (irrecv.decode(&results)) {
    processIRCommand(results.value);
    irrecv.resume(); // Receive the next value
  }
  
  // In auto mode, periodically read sensors and adjust systems
  if (autoModeEnabled && (millis() - lastSensorReadTime > SENSOR_READ_INTERVAL)) {
    readSensors();
    automaticControl();
    lastSensorReadTime = millis();
    updateLCD();
  }
  
  // Update status LEDs to match system states
  digitalWrite(IRRIGATION_LED, irrigationState ? HIGH : LOW);
  digitalWrite(FAN_LED, fanState ? HIGH : LOW);
  digitalWrite(HEATER_LED, heaterState ? HIGH : LOW);
  
  delay(100); // Small delay for stability
}

/**
 * Process IR remote commands
 * 
 * @param command The IR command code received
 */
void processIRCommand(unsigned long command) {
  Serial.print("Command received: 0x");
  Serial.println(command, HEX);
  
  switch (command) {
    case IRRIGATION_TOGGLE:
      toggleIrrigation();
      break;
    case FAN_TOGGLE:
      toggleFan();
      break;
    case HEATER_TOGGLE:
      toggleHeater();
      break;
    case AUTO_MODE:
      enableAutoMode(true);
      break;
    case MANUAL_MODE:
      enableAutoMode(false);
      break;
    case DATA_DISPLAY:
      readSensors();
      displaySensorData();
      break;
    default:
      // Unknown command
      break;
  }
  
  updateLCD();
}

/**
 * Toggle irrigation system
 */
void toggleIrrigation() {
  if (autoModeEnabled) {
    Serial.println("Cannot manually toggle in AUTO mode");
    return;
  }
  
  irrigationState = !irrigationState;
  digitalWrite(IRRIGATION_PIN, irrigationState ? HIGH : LOW);
  
  Serial.print("Irrigation ");
  Serial.println(irrigationState ? "ON" : "OFF");
}

/**
 * Toggle ventilation fan
 */
void toggleFan() {
  if (autoModeEnabled) {
    Serial.println("Cannot manually toggle in AUTO mode");
    return;
  }
  
  fanState = !fanState;
  digitalWrite(FAN_PIN, fanState ? HIGH : LOW);
  
  Serial.print("Fan ");
  Serial.println(fanState ? "ON" : "OFF");
}

/**
 * Toggle heating system
 */
void toggleHeater() {
  if (autoModeEnabled) {
    Serial.println("Cannot manually toggle in AUTO mode");
    return;
  }
  
  heaterState = !heaterState;
  digitalWrite(HEATER_PIN, heaterState ? HIGH : LOW);
  
  Serial.print("Heater ");
  Serial.println(heaterState ? "ON" : "OFF");
}

/**
 * Enable or disable automatic mode
 * 
 * @param enable True to enable auto mode, false to disable
 */
void enableAutoMode(bool enable) {
  autoModeEnabled = enable;
  
  if (autoModeEnabled) {
    Serial.println("AUTO mode enabled - Systems will be controlled by sensor readings");
    readSensors();
    automaticControl();
  } else {
    Serial.println("MANUAL mode enabled - Use remote to control systems");
    // Turn all systems off when switching to manual mode
    irrigationState = false;
    fanState = false;
    heaterState = false;
    digitalWrite(IRRIGATION_PIN, LOW);
    digitalWrite(FAN_PIN, LOW);
    digitalWrite(HEATER_PIN, LOW);
  }
}

/**
 * Read data from all sensors
 */
void readSensors() {
  // Read soil moisture
  soilMoisture = analogRead(MOISTURE_SENSOR);
  
  // Read temperature and humidity
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  
  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.println("Sensor Readings:");
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}

/**
 * Control systems automatically based on sensor readings
 */
void automaticControl() {
  // Control irrigation based on soil moisture
  if (soilMoisture < DRY_THRESHOLD && !irrigationState) {
    irrigationState = true;
    digitalWrite(IRRIGATION_PIN, HIGH);
    Serial.println("AUTO: Irrigation turned ON - Soil is dry");
  } else if (soilMoisture >= DRY_THRESHOLD && irrigationState) {
    irrigationState = false;
    digitalWrite(IRRIGATION_PIN, LOW);
    Serial.println("AUTO: Irrigation turned OFF - Soil moisture adequate");
  }
  
  // Control fan based on temperature
  if (temperature > TEMP_HIGH_THRESHOLD && !fanState) {
    fanState = true;
    digitalWrite(FAN_PIN, HIGH);
    Serial.println("AUTO: Fan turned ON - Temperature too high");
  } else if (temperature <= TEMP_HIGH_THRESHOLD && fanState) {
    fanState = false;
    digitalWrite(FAN_PIN, LOW);
    Serial.println("AUTO: Fan turned OFF - Temperature normal");
  }
  
  // Control heater based on temperature
  if (temperature < TEMP_LOW_THRESHOLD && !heaterState) {
    heaterState = true;
    digitalWrite(HEATER_PIN, HIGH);
    Serial.println("AUTO: Heater turned ON - Temperature too low");
  } else if (temperature >= TEMP_LOW_THRESHOLD && heaterState) {
    heaterState = false;
    digitalWrite(HEATER_PIN, LOW);
    Serial.println("AUTO: Heater turned OFF - Temperature normal");
  }
}

/**
 * Display sensor data on serial monitor
 */
void displaySensorData() {
  Serial.println("\n===== Agricultural Environment Data =====");
  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisture);
  
  // Convert raw moisture reading to percentage for better understanding
  int moisturePercent = map(soilMoisture, 0, 1023, 0, 100);
  Serial.print(" (");
  Serial.print(moisturePercent);
  Serial.println("%)");
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  Serial.println("System Status:");
  Serial.print("Irrigation: ");
  Serial.println(irrigationState ? "ON" : "OFF");
  Serial.print("Fan: ");
  Serial.println(fanState ? "ON" : "OFF");
  Serial.print("Heater: ");
  Serial.println(heaterState ? "ON" : "OFF");
  Serial.print("Mode: ");
  Serial.println(autoModeEnabled ? "AUTOMATIC" : "MANUAL");
  Serial.println("=========================================");
}

/**
 * Update LCD display with current data
 */
void updateLCD() {
  lcd.clear();
  
  // First row: Mode and main sensor reading
  lcd.setCursor(0, 0);
  lcd.print(autoModeEnabled ? "AUTO " : "MANUAL ");
  
  // Show soil moisture on first row
  lcd.print("M:");
  int moisturePercent = map(soilMoisture, 0, 1023, 0, 100);
  lcd.print(moisturePercent);
  lcd.print("%");
  
  // Second row: Temperature, humidity and system status
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print((int)temperature);
  lcd.print("C ");
  
  // Show system status using symbols
  lcd.print("I");
  lcd.print(irrigationState ? "+" : "-");
  lcd.print("F");
  lcd.print(fanState ? "+" : "-");
  lcd.print("H");
  lcd.print(heaterState ? "+" : "-");
}
