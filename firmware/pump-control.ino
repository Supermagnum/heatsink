#include <LiquidCrystal.h>

// Pins for temperature adjustment switches
const int tempUpPin = 2;
const int tempDownPin = 3;

// Pins for relays
const int pumpRelayPin = 4;
const int secondRelayPin = 5;

// Pin for NTC
const int ntcPin = A0;

// Calibration table values
const int calibrationTemps[] = {-40, -20, -10, 0, 10, 20, 30, 40, 50};
const int calibrationValues[] = {45313, 15462, 9397, 5896, 3792, 2500, 1707, 1175, 834};
const int calibrationSize = sizeof(calibrationTemps) / sizeof(calibrationTemps[0]);

// PWM minimum and maximum values
const int pwmMin = 51; // 20% of 255
const int pwmMax = 255;

// NTC parameters
const int seriesResistor = 50000; // 50K resistor
const int betaValue = 3950;       // Beta value of NTC
const int ntcNominal = 5896;      // NTC resistance at 0 Celsius

// LCD setup
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Variables
int setTemp = 20;       // Initial set temperature
int currentTemp = 0;    // Current temperature read from NTC
int currentPWM = 0;     // Current PWM value
boolean relayActive = false;

void setup() {
  pinMode(tempUpPin, INPUT_PULLUP);
  pinMode(tempDownPin, INPUT_PULLUP);
  pinMode(pumpRelayPin, OUTPUT);
  pinMode(secondRelayPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Set: ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
}

void loop() {
  // Read temperature adjustment switches
  if (digitalRead(tempUpPin) == LOW && setTemp < 25) {
    setTemp += 5;
  }
  if (digitalRead(tempDownPin) == LOW && setTemp > 15) {
    setTemp -= 5;
  }

  // Read temperature from NTC
  int ntcReading = analogRead(ntcPin);
  double ntcResistance = seriesResistor * (1023.0 / ntcReading - 1.0);
  double steinhart = ntcResistance / ntcNominal;  // (R/Ro)
  steinhart = log(steinhart);                     // ln(R/Ro)
  steinhart /= betaValue;                         // 1/B * ln(R/Ro)
  steinhart += 1.0 / (273.15 + 25.0);             // + (1/To)
  steinhart = 1.0 / steinhart;                    // Invert
  currentTemp = int(steinhart - 273.15);          // Convert to Celsius

  // Calculate PWM based on temperature
  if (currentTemp <= setTemp) {
    currentPWM = map(currentTemp, setTemp, 15, pwmMin, pwmMax);
  } else {
    currentPWM = map(currentTemp, setTemp, 25, pwmMin, pwmMax);
  }
  analogWrite(pumpRelayPin, currentPWM);

  // Display values on LCD
  lcd.setCursor(5, 0);
  lcd.print(setTemp);
  lcd.setCursor(6, 1);
  lcd.print(currentTemp);
  lcd.setCursor(12, 1);
  lcd.print(currentPWM);

  // Check temperature threshold for relay activation
  if (currentTemp > 30 && relayActive == false) {
    delay(120000); // Wait for 120 seconds
    digitalWrite(secondRelayPin, HIGH);
    relayActive = true;
  }
}
