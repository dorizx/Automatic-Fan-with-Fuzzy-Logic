#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include <Fuzzy.h>

int DHTPIN = 7;
int DHTTYPE = DHT11;

int FAN_PIN_ENA = 9;
int FAN_PIN_IN3 = 10;
int FAN_PIN_IN4 = 11;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Fuzzy Logic Setup
Fuzzy *fuzzy = new Fuzzy();
FuzzyInput *temperature;
FuzzyOutput *fanSpeed;

void setupFuzzyLogic() {
    temperature = new FuzzyInput(1);
    FuzzySet *tempLow = new FuzzySet(30, 30, 33, 34);
    FuzzySet *tempMed = new FuzzySet(32, 33, 35, 36);
    FuzzySet *tempHigh = new FuzzySet(34,36, 38, 39);
    temperature->addFuzzySet(tempLow);
    temperature->addFuzzySet(tempMed);
    temperature->addFuzzySet(tempHigh);
    fuzzy->addFuzzyInput(temperature);

    fanSpeed = new FuzzyOutput(1);
    FuzzySet *speedLow = new FuzzySet(0, 50, 50, 100);
    FuzzySet *speedMed = new FuzzySet(100, 150, 150, 200);
    FuzzySet *speedHigh = new FuzzySet(200, 250, 250, 255);
    fanSpeed->addFuzzySet(speedLow);
    fanSpeed->addFuzzySet(speedMed);
    fanSpeed->addFuzzySet(speedHigh);
    fuzzy->addFuzzyOutput(fanSpeed);

    FuzzyRuleAntecedent *ifTempLow = new FuzzyRuleAntecedent();
    ifTempLow->joinSingle(tempLow);
    FuzzyRuleConsequent *thenSpeedLow = new FuzzyRuleConsequent();
    thenSpeedLow->addOutput(speedLow);
    fuzzy->addFuzzyRule(new FuzzyRule(1, ifTempLow, thenSpeedLow));

    FuzzyRuleAntecedent *ifTempMed = new FuzzyRuleAntecedent();
    ifTempMed->joinSingle(tempMed);
    FuzzyRuleConsequent *thenSpeedMed = new FuzzyRuleConsequent();
    thenSpeedMed->addOutput(speedMed);
    fuzzy->addFuzzyRule(new FuzzyRule(2, ifTempMed, thenSpeedMed));

    FuzzyRuleAntecedent *ifTempHigh = new FuzzyRuleAntecedent();
    ifTempHigh->joinSingle(tempHigh);
    FuzzyRuleConsequent *thenSpeedHigh = new FuzzyRuleConsequent();
    thenSpeedHigh->addOutput(speedHigh);
    fuzzy->addFuzzyRule(new FuzzyRule(3, ifTempHigh, thenSpeedHigh));
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");

  pinMode(FAN_PIN_ENA, OUTPUT);
  pinMode(FAN_PIN_IN3, OUTPUT);
  pinMode(FAN_PIN_IN4, OUTPUT);

  setupFuzzyLogic();
}

void loop() {
  delay(2000);
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature!");
    return;
  }

  // Fuzzify the temperature input
  fuzzy->setInput(1, temperature);
  fuzzy->fuzzify();

  int fan_speed = fuzzy->defuzzify(1); // Defuzzify the output

  analogWrite(FAN_PIN_ENA, fan_speed);
  digitalWrite(FAN_PIN_IN3, HIGH);
  digitalWrite(FAN_PIN_IN4, LOW);

  lcd.setCursor(0, 1);
  lcd.print("Fan Speed: ");
  if (fan_speed < 100) {
    lcd.print(fan_speed);
  } else if (fan_speed < 200) {
    lcd.print(fan_speed);
  } else {
    lcd.print(fan_speed);
  }

  lcd.setCursor(12, 0);
  lcd.print(temperature);
}
