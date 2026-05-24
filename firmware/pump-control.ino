#include <LiquidCrystal.h>

// ── Pin assignments ───────────────────────────────────────────────────────────
// LCD uses pins 12, 11, 10, 6, 5, 13
// Buttons and other I/O use pins 2, 3, 4, 7, 8, 9 — no conflicts
const int ntcPin             = A0;  // Analog pin for NTC thermistor
const int pwmPin             = 9;   // PWM pin for pump control (BTS7960)
const int relay1Pin          = 7;   // Relay 1 — automatic out-of-ice alarm
const int relay2Pin          = 8;   // Relay 2 — manual control via button
const int tempUpButton       = 2;   // Button: increase target temperature
const int tempDownButton     = 3;   // Button: decrease target temperature
const int relayControlButton = 4;   // Button: toggle relay 2

// ── Hardware constants ────────────────────────────────────────────────────────
const int   resistorValue = 50000;  // 50k ohm fixed resistor in voltage divider
const int   debounceDelay = 50;     // Button debounce delay (ms)

// ── Smoothing constants ───────────────────────────────────────────────────────
const float tau   = 15.0;           // Response time constant (seconds)
const float dt    = 0.5;            // Loop interval (seconds)
const float alpha = dt / tau;       // Exponential smoothing factor

// ── NTC calibration table (Bosch M12) ────────────────────────────────────────
const int  tempValues[]       = {-40, -20, -10,  0,  10,   20,   30,   40,   50};
const long resistanceValues[] = {45313, 15462, 9397, 5896, 3792, 2500, 1707, 1175, 834};
const int  calibrationPoints  = 9;

// ── State variables ───────────────────────────────────────────────────────────
int           targetTemp       = 15;
float         readTemp         = 20.0;
int           pwmValue         = 0;
bool          relay2Active     = false;
unsigned long lastDebounceTime = 0;

// ── Relay 1 alarm timing (non-blocking) ──────────────────────────────────────
const unsigned long alarmDelay    = 120000UL;
unsigned long       overTempStart = 0;
bool                overTempActive = false;

// ── LCD setup ─────────────────────────────────────────────────────────────────
LiquidCrystal lcd(12, 11, 10, 6, 5, 13);

// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  pinMode(ntcPin,             INPUT);
  pinMode(pwmPin,             OUTPUT);
  pinMode(relay1Pin,          OUTPUT);
  pinMode(relay2Pin,          OUTPUT);
  pinMode(tempUpButton,       INPUT_PULLUP);
  pinMode(tempDownButton,     INPUT_PULLUP);
  pinMode(relayControlButton, INPUT_PULLUP);

  digitalWrite(relay1Pin, LOW);
  digitalWrite(relay2Pin, LOW);
  analogWrite(pwmPin, 0);

  lcd.begin(20, 4);
  lcd.clear();

  readTemp = getTemperature();
  Serial.begin(9600);
}

// ─────────────────────────────────────────────────────────────────────────────
void loop() {
  float currentTemp = getTemperature();
  readTemp += alpha * (currentTemp - readTemp);

  unsigned long now = millis();

  if (digitalRead(tempUpButton) == LOW && (now - lastDebounceTime) > debounceDelay) {
    targetTemp = min(targetTemp + 5, 25);
    lastDebounceTime = now;
  }

  if (digitalRead(tempDownButton) == LOW && (now - lastDebounceTime) > debounceDelay) {
    targetTemp = max(targetTemp - 5, 15);
    lastDebounceTime = now;
  }

  if (digitalRead(relayControlButton) == LOW && (now - lastDebounceTime) > debounceDelay) {
    relay2Active = !relay2Active;
    digitalWrite(relay2Pin, relay2Active ? HIGH : LOW);
    lastDebounceTime = now;
  }

  updatePWM();

  if (readTemp > 30.0) {
    if (!overTempActive) {
      overTempActive = true;
      overTempStart  = millis();
    } else if ((millis() - overTempStart) >= alarmDelay) {
      digitalWrite(relay1Pin, HIGH);
    }
  } else {
    overTempActive = false;
    digitalWrite(relay1Pin, LOW);
  }

  updateLCD();

  Serial.print("Target: ");  Serial.print(targetTemp);
  Serial.print(" Read: ");   Serial.print(readTemp);
  Serial.print(" PWM: ");    Serial.print(pwmValue);
  Serial.print(" Relay2: "); Serial.println(relay2Active ? "ON" : "OFF");

  delay((unsigned long)(dt * 1000));
}

// ─────────────────────────────────────────────────────────────────────────────
float getTemperature() {
  int analogValue = analogRead(ntcPin);
  if (analogValue == 0) return -40.0;

  float voltage    = analogValue * (5.0 / 1023.0);
  float resistance = resistorValue * (voltage / (5.0 - voltage));

  if (resistance >= resistanceValues[0])                    return (float)tempValues[0];
  if (resistance <= resistanceValues[calibrationPoints - 1]) return (float)tempValues[calibrationPoints - 1];

  for (int i = 0; i < calibrationPoints - 1; i++) {
    if (resistance <= resistanceValues[i] && resistance >= resistanceValues[i + 1]) {
      float t = (float)tempValues[i] +
                (resistance - (float)resistanceValues[i]) *
                ((float)(tempValues[i + 1] - tempValues[i]) /
                 (float)(resistanceValues[i + 1] - resistanceValues[i]));
      return t;
    }
  }
  return -40.0;
}

// ─────────────────────────────────────────────────────────────────────────────
void updatePWM() {
  if (readTemp > (float)targetTemp) {
    pwmValue = (int)map((long)(readTemp * 10),
                        (long)(targetTemp * 10),
                        (long)((targetTemp + 20) * 10),
                        26, 255);
    pwmValue = constrain(pwmValue, 26, 255);
  } else {
    pwmValue = 0;
  }
  analogWrite(pwmPin, pwmValue);
}

// ─────────────────────────────────────────────────────────────────────────────
void updateLCD() {
  lcd.setCursor(0, 0);
  lcd.print("Target:  ");
  lcd.print(targetTemp);
  lcd.print((char)223);
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Coolant: ");
  lcd.print(readTemp, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  lcd.setCursor(0, 2);
  lcd.print("Pump PWM:");
  lcd.print(map(pwmValue, 0, 255, 0, 100));
  lcd.print("%    ");

  lcd.setCursor(0, 3);
  lcd.print("Relay2:");
  lcd.print(relay2Active ? "ON " : "OFF");
  lcd.print(" Alarm:");
  lcd.print(digitalRead(relay1Pin) ? "ON " : "OFF");
}
