#include <LiquidCrystal.h>

// Constants
const int ntcPin = A0;             // Analog pin for NTC thermistor
const int pwmPin = 9;              // PWM pin for pump control
const int relay1Pin = 7;           // Digital pin for relay 1
const int relay2Pin = 8;           // Digital pin for relay 2
const int tempUpButton = 2;        // Button to increase target temperature
const int tempDownButton = 3;      // Button to decrease target temperature
const int relayControlButton = 4;  // Button to control relays
const int resistorValue = 50000;   // 50k ohm resistor
const int debounceDelay = 50;      // Debounce delay in ms
const float tau = 15.0;            // Response time constant (in seconds)
const float dt = 0.5;              // Loop time interval (in seconds)
const float alpha = dt / tau;      // Exponential smoothing factor

// Calibration table
const int tempValues[] = {-40, -20, -10, 0, 10, 20, 30, 40, 50};
const long resistanceValues[] = {45313, 15462, 9397, 5896, 3792, 2500, 1707, 1175, 834};

// Variables
int targetTemp = 15;               // Target temperature (initially 15°C)
float readTemp = 0;                // Current temperature
int pwmValue = 0;                  // PWM value (0-255)
bool relayActive = false;          // Relay control state
unsigned long lastDebounceTime = 0;// Debounce timer

// LCD setup
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(ntcPin, INPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(tempUpButton, INPUT_PULLUP);
  pinMode(tempDownButton, INPUT_PULLUP);
  pinMode(relayControlButton, INPUT_PULLUP);

  lcd.begin(20, 4);
  lcd.clear();
  
  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay2Pin, LOW);

  Serial.begin(9600);
}

void loop() {
  float currentTemp = getTemperature();
  readTemp += alpha * (currentTemp - readTemp);

  if (digitalRead(tempUpButton) == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    targetTemp = min(targetTemp + 5, 25);
    lastDebounceTime = millis();
  }
  
  if (digitalRead(tempDownButton) == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    targetTemp = max(targetTemp - 5, 15);
    lastDebounceTime = millis();
  }
  
  if (digitalRead(relayControlButton) == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    relayActive = !relayActive;
    digitalWrite(relay2Pin, relayActive ? HIGH : LOW);
    lastDebounceTime = millis();
  }

  updatePWM();
  updateLCD();

  if (relayActive && readTemp > 30) {
    delay(120000); // 120 seconds delay
    digitalWrite(relay1Pin, HIGH);
  } else {
    digitalWrite(relay1Pin, LOW);
  }

  delay(dt * 1000); // Delay for dt seconds
}

float getTemperature() {
  int analogValue = analogRead(ntcPin);
  float voltage = analogValue * (5.0 / 1023.0);
  float resistance = (5.0 / voltage - 1) * resistorValue;

  float temp = 0;
  for (int i = 0; i < 8; i++) {
    if (resistance <= resistanceValues[i] && resistance >= resistanceValues[i + 1]) {
      temp = tempValues[i] + (resistance - resistanceValues[i]) * (tempValues[i + 1] - tempValues[i]) / (resistanceValues[i + 1] - resistanceValues[i]);
      break;
    }
  }
  
  return temp;
}

void updatePWM() {
  if (readTemp < targetTemp) {
    pwmValue = map(readTemp, -40, targetTemp, 26, 255); // Scale PWM value (minimum 10% = 26 out of 255)
  } else {
    pwmValue = 0;
  }
  
  analogWrite(pwmPin, pwmValue);
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Target Temp: ");
  lcd.print(targetTemp);
  lcd.setCursor(0, 1);
  lcd.print("Read Temp: ");
  lcd.print(readTemp);
  lcd.setCursor(0, 2);
  lcd.print("PWM Value: ");
  lcd.print(pwmValue);
  lcd.setCursor(0, 3);
  lcd.print("Relay Active: ");
  lcd.print(relayActive ? "Yes" : "No");
}
