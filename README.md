# Fuzzy Logic-based Fan Control System

This project demonstrates a fan control system based on temperature using **Fuzzy Logic**. The system reads the ambient temperature from a DHT11 sensor and adjusts the fan speed accordingly. The fan speed is controlled via PWM based on the fuzzy logic rules set up in the system. The temperature and fan speed are displayed on an LCD.

## Components Required:
- **DHT11 Temperature and Humidity Sensor**
- **Arduino (e.g., Arduino Uno)**
- **LCD 16x2 with I2C**
- **DC Fan**
- **Transistor (e.g., TIP120) or MOSFET**
- **Wires and Breadboard**

## Libraries Used:
- **Adafruit_Sensor** - Library for reading from DHT sensors
- **DHT** - DHT sensor library
- **LiquidCrystal_I2C** - Library for controlling an LCD with I2C
- **Fuzzy** - Fuzzy logic library for setting up and executing fuzzy rules

## Circuit Overview:
1. **DHT11 Sensor**: Reads the ambient temperature and sends it to the Arduino.
2. **LCD Display**: Shows the current temperature and fan speed.
3. **DC Fan**: Controlled by PWM signal to regulate the fan speed based on temperature.
4. **Fuzzy Logic Controller**: The temperature is fuzzified and used to adjust the fan speed based on predefined fuzzy rules.

## Setup:
1. **Wiring**:
   - **DHT11**: Connect the **VCC** pin to 5V, **GND** to ground, and **DATA** to pin 7 of Arduino.
   - **LCD**: Connect the **SDA** and **SCL** pins to the corresponding pins on Arduino (A4, A5 for Uno).
   - **Fan Control**: Use a PWM-capable pin for controlling the fan's speed and two other pins for controlling the direction of rotation via an H-Bridge.

2. **Upload the Code**:
   - Open the Arduino IDE.
   - Select the correct board and port.
   - Copy and paste the code into the editor.
   - Click **Upload**.

## Functionality:
- The fan speed is automatically adjusted based on the current temperature:
  - **Low Temperature (30-34°C)**: Fan speed is low.
  - **Medium Temperature (32-36°C)**: Fan speed is medium.
  - **High Temperature (34-39°C)**: Fan speed is high.
  
- The LCD displays the current temperature and the fan speed in real-time.

## Code Walkthrough:
1. **Fuzzy Logic Setup**: The system uses fuzzy logic to determine the fan speed based on the temperature range. The temperature input is divided into three fuzzy sets: Low, Medium, and High.
2. **Fan Control**: Depending on the defuzzified fan speed value, the fan's speed is adjusted via PWM.
3. **LCD Display**: The LCD continuously updates to show the temperature and corresponding fan speed.

## How to Improve:
- Add humidity control to adjust fan speed based on both temperature and humidity.
- Integrate with a mobile app to monitor temperature and fan status remotely.
- Use more precise sensors for better temperature control.

