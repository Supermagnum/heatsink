//preliminary firmware to control a pumps PWM rate based on temperature. 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ntcPin = A0;
const int upSwitchPin = 2;
const int downSwitchPin = 3;
const int relayPin1 = 4;
const int relayPin2 = 5;

const int targetTempMin = 15;
const int targetTempMax = 25;
const int tempStep = 5;
const int minPWM = 20;

const int ntcResistance[] = {45313, 15462, 9397, 5896, 3792, 2500, 1707, 1175, 834};
const int ntcTemperatures[] = {-40, -20, -10, 0, 10, 20, 30, 40, 50};
const int numCalibrationPoints = sizeof(ntcResistance) / sizeof(ntcResistance[0]);

int currentTempIndex = 3; // Default to 0°C
int currentPWM = minPWM;
int setTemp = ntcTemperatures[currentTempIndex];
bool relay1Active = false;
bool relay2Active = false;

unsigned long lastTempUpdateMillis = 0;

void setup() {
  pinMode(upSwitchPin, INPUT_PULLUP);
  pinMode(downSwitchPin, INPUT_PULLUP);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Set:   C  PWM:   %");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastTempUpdateMillis >= 15000) { // Update temperature every 15 seconds
    lastTempUpdateMillis = currentMillis;
    
    int rawADC = analogRead(ntcPin);
    double ntcResistance = calcNTCResistance(rawADC);
    double temp = calcTemperature(ntcResistance);
    
    updateTemp(temp);
    updatePWM();
    updateRelays(temp);
    updateLCD();
  }

  // Check switches and update set temperature
  if (digitalRead(upSwitchPin) == LOW) {
    increaseTemp();
  }
  if (digitalRead(downSwitchPin) == LOW) {
    decreaseTemp();
  }
}

double calcNTCResistance(int rawADC) {
  double voltage = rawADC * (5.0 / 1023.0);
  double ntcVoltage = voltage * (50000.0 / (50000.0 + 10000.0)); // NTC in series with 50K resistor
  return (5.0 / ntcVoltage - 1.0) * 10000.0;
}

double calcTemperature(double ntcResistance) {
  // Interpolate temperature based on calibration table
  // You can implement the interpolation logic here using the provided calibration values
}

void updateTemp(double temp) {
  // Update the current temperature index and setTemp based on the calculated temperature
}

void increaseTemp() {
  // Increase the current temperature index and setTemp
}

void decreaseTemp() {
  // Decrease the current temperature index and setTemp
}

void updatePWM() {
  // Update the PWM value based on the difference between setTemp and current temperature
}

void updateRelays(double temp) {
  // Check if temperature exceeds 30°C and activate relays accordingly
}

void updateLCD() {
  // Update the LCD with the current set temperature, current temperature, and PWM value
}
