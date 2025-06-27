# IoT Gas Leakage Alert System 🚨

This is an Arduino-based project that detects gas leakage using MQ gas sensors and sends alerts via SMS and phone calls using a GSM module. A servo motor is also triggered for emergency mechanical action (e.g., to trigger an alarm or ventilation).

## 📦 Project Files

- **iot-gas-leakage-alert-system.zip**: Contains the Arduino `.ino` file and folder structure for this project.

## 🧠 Components Used

- Arduino UNO
- MQ2 Gas Sensor
- SIM800L GSM Module (or Adafruit FONA)
- Servo Motor
- Breadboard and connecting wires
- Power supply (5V/9V)

## 📱 Features

- Realtime gas detection using MQ2 sensor
- Sends SMS alert to two mobile numbers
- Makes phone calls to same numbers automatically
- Rotates a servo motor to trigger emergency action
- Can be enhanced with buzzer, LED or mobile app

## 🔗 Sample SMS Content

```
Gas Leakage Detected location-- https://maps.app.goo.gl/yMoMVtFcwRjUmwLm6
```

## 🔧 How to Use

1. Extract the ZIP file
2. Open the `.ino` file using Arduino IDE
3. Upload it to your Arduino UNO board
4. Connect the sensor and GSM hardware as per the circuit
5. Power on and wait for gas detection – SMS, call and servo actions will be triggered automatically.

## 📃 License

This project is licensed under the MIT License – feel free to use, modify and share!
