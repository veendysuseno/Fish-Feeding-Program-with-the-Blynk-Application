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
