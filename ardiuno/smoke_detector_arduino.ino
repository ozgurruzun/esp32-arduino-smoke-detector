int redLed = 2;
int greenLed = 3;
int buzzer = 4;
int smokeA0 = A5;
int signalPin = 7; // ESP32'ye sinyal göndermek için kullanılacak pin
int sensorThres = 500; // Threshold değeri

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(signalPin, OUTPUT); // Sinyal pini çıkış olarak ayarlanır
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokeA0); // Sensör verisini oku

  Serial.print("Pin A5: ");
  Serial.println(analogSensor);

  // Threshold değerine göre LED, buzzer ve sinyal kontrolü
  if (analogSensor > sensorThres) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(buzzer, HIGH);
    digitalWrite(signalPin, HIGH); // ESP32'ye sinyal gönder
    Serial.println("High gas level detected! Signal sent to ESP32.");
  } else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    digitalWrite(buzzer, LOW);
    digitalWrite(signalPin, LOW); // Sinyal kapatılır
  }
  delay(100);
}
