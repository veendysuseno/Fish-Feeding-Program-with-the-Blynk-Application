# Fish Feeding Program with the Blynk Application

This project uses an ESP8266 to control a fish feeder system with a servo motor and an HC-SR04 ultrasonic distance sensor. The system can be controlled and monitored through the Blynk application.

## Components

- **ESP8266**: WiFi module for connectivity.
- **HC-SR04**: Ultrasonic distance sensor to measure the level of fish food.
- **Servo Motor**: To dispense fish food.
- **Blynk App**: For remote control and monitoring.

## Libraries

- **ESP8266WiFi**: For WiFi connectivity on the ESP8266.
- **BlynkSimpleEsp8266**: For integrating with the Blynk platform.
- **HCSR04**: For interfacing with the HC-SR04 ultrasonic sensor.
- **Servo**: For controlling the servo motor.

## Code Overview

### Initialization

- **Setup**:
  - Initializes serial communication.
  - Connects to Blynk with the provided credentials.
  - Sets up a timer to periodically send sensor data.
  - Attaches the servo motor to a specific pin.

### Main Loop

- **Loop**:
  - Handles Blynk and timer tasks.
  - Updates the feed level based on sensor data every second.
  - Maps the feed level to a percentage and sends it to Blynk.

### Blynk Control

- **BLYNK_WRITE(V3)**:
  - Controls the position of the servo motor based on a virtual button in the Blynk app.

### Sensor Data

- **sendSensor()**:
  - Sends the current feed level to the Blynk app.

## Code

```cpp
/* Program Pemberi Pakan Ikan dengan Aplikasi Blynk dibuat oleh Indobot */
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <HCSR04.h>
#include <Servo.h>

BlynkTimer timer;
HCSR04 hc(D7, D6);
Servo myservo;

char auth[] = "l5uC-hnc4Y6CHBrX7mntiWWLL1hIBoLb";
char ssid[] = "MAI";
char pass[] = "sup4rtin4h";

unsigned long TSekarang;
unsigned long TAkhir;
float TinggiSensor = 17;
float TingkatPakan = 0;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
  myservo.attach(D8);
}

void loop() {
  Blynk.run();
  timer.run();

  TSekarang = millis();
  if (TSekarang - TAkhir > 1000) {
    TingkatPakan = TinggiSensor - hc.dist();

    if (TingkatPakan < 0) {
      TingkatPakan = 0;
    }
    else if (TingkatPakan > 17) {
      TingkatPakan = 17;
    }

    TingkatPakan = map(TingkatPakan, 0, 17, 0, 100);  //Ubah ke persen(%)
    TAkhir = TSekarang;
  }
}

BLYNK_WRITE(V3) {
  int tombolservo = param.asInt();
  if (tombolservo == 1) {
    myservo.write(90);
  }
  else {
    myservo.write(0);
  }
}

void sendSensor() {
  Blynk.virtualWrite(V2, TingkatPakan);
}
```

## Usage

1. Setup:

   - Connect the HC-SR04 sensor to pins D7 and D6.
   - Connect the servo motor to pin D8.
   - Ensure you have the correct Blynk credentials and WiFi details in the code.

2. Run:
   - Upload the code to the ESP8266.
   - Open the Blynk app and set up virtual pins V2 and V3 to display sensor data and control the servo motor, respectively.
