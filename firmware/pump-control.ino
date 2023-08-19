//preliminary firmware to control a pumps PWM rate based on temperature. 

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
const int ntcPin = A0;          // NTC analog pin
const int upSwitchPin = 2;      // Temperature increase switch pin
const int downSwitchPin = 3;    // Temperature decrease switch pin
const int relayPin1 = 4;        // First relay pin
const int relayPin2 = 5;        // Second relay pin

// NTC calibration table
const float ntcCalibration[][2] = {
  {-40, 45313},
  {-20, 15462},
  {-10, 9397},
  {0, 5896},
  {10, 3792},
  {20, 2500},
  {30, 1707},
  {40, 1175},
  {50, 834}
};

const int numCalibrationPoints = sizeof(ntcCalibration) / sizeof(ntcCalibration[0]);

// Constants
const int minPWM = 20;          // Minimum PWM value
const int targetTemp = 20;      // Initial target temperature

// Variables
int currentTemp = 0;
int targetTempIndex = 4;        // Index of initial target temperature (20 degrees)
int currentPWM = 0;
unsigned long previousMillis = 0;
const long interval = 15000;    // Sampling interval in milliseconds
bool relayActivated = false;

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  pinMode(ntcPin, INPUT);
  pinMode(upSwitchPin, INPUT_PULLUP);
  pinMode(downSwitchPin, INPUT_PULLUP);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Set: ");
  lcd.setCursor(0, 1);
  lcd.print("Read: ");
}

void loop() {
  // Read NTC temperature and calculate resistance
  int rawADC = analogRead(ntcPin);
  float voltage = (rawADC / 1023.0) * 5.0;
  float resistance = (5.0 * 50000.0) / voltage - 50000.0;
  
  // Calculate temperature using interpolation
  float temp = interpolateTemperature(resistance);
  
  // Update LCD display
  lcd.setCursor(5, 1);
  lcd.print(temp);
  
  // Check if relay activation conditions are met
  if (temp > 30 && relayActivated) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 120000) {
      digitalWrite(relayPin1, HIGH);
      digitalWrite(relayPin2, HIGH);
    }
  } else {
    previousMillis = millis();
  }
  
  // Check switch inputs
  if (digitalRead(upSwitchPin) == LOW) {
    if (targetTempIndex < numCalibrationPoints - 1) {
      targetTempIndex++;
      updateTargetTemperature();
    }
    delay(250);
  }
  
  if (digitalRead(downSwitchPin) == LOW) {
    if (targetTempIndex > 0) {
      targetTempIndex--;
      updateTargetTemperature();
    }
    delay(250);
  }
  
  // Calculate PWM value based on temperature error
  int tempError = targetTemp - temp;
  currentPWM = map(tempError, -10, 10, minPWM, 255);
  analogWrite(relayPin1, currentPWM);
  
  // Update LCD display
  lcd.setCursor(5, 0);
  lcd.print(targetTemp);
  lcd.setCursor(12, 1);
  lcd.print(currentPWM);
  
  delay(interval);
}

float interpolateTemperature(float resistance) {
  for (int i = 0; i < numCalibrationPoints - 1; i++) {
    if (resistance >= ntcCalibration[i][1] && resistance <= ntcCalibration[i + 1][1]) {
      float tempRange = ntcCalibration[i + 1][0] - ntcCalibration[i][0];
      float resistanceRange = ntcCalibration[i + 1][1] - ntcCalibration[i][1];
      float resistanceDiff = resistance - ntcCalibration[i][1];
      return ntcCalibration[i][0] + (tempRange / resistanceRange) * resistanceDiff;
    }
  }
  return -40.0; // Default value if calibration is out of range
}

void updateTargetTemperature() {
  targetTemp = ntcCalibration[targetTempIndex][0];
  lcd.setCursor(5, 0);
  lcd.print(targetTemp);
}
