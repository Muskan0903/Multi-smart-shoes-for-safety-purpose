#include <SoftwareSerial.h>
#include <Wire.h>

// Pin Definitions
#define SIM_TX 8
#define SIM_RX 7
#define GPS_TX 11 
#define GPS_RX 12
#define HC05_TX 6
#define HC05_RX 5
#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER 3
#define PRESSURE_SENSOR A0
#define TOUCH_SENSOR 2

// Modules
SoftwareSerial sim800l(SIM_TX, SIM_RX);
SoftwareSerial gpsSerial(GPS_TX, GPS_RX);
SoftwareSerial bluetooth(HC05_TX, HC05_RX);

// States
String latitude = "", longitude = "";
bool gpsSent = false;
bool callMade = false;
bool alertEnabled = false;
bool lastTouchState = LOW;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(TOUCH_SENSOR, INPUT);
  pinMode(PRESSURE_SENSOR, INPUT);
  digitalWrite(BUZZER, LOW);

  Serial.begin(9600);
  sim800l.begin(9600);
  gpsSerial.begin(9600);
  bluetooth.begin(9600);

  delay(3000); // Let modules initialize
  Serial.println("System Ready.");
}

void loop() {
  handleTouchSensor();

  int pressure = analogRead(PRESSURE_SENSOR);
  Serial.print("Pressure: ");
  Serial.println(pressure);

  if (pressure > 15) {
    if (!callMade) {
      makeCall();
      callMade = true;
    }

    getGPS();
    if (latitude != "" && longitude != "" && !gpsSent) {
      sendSMS(latitude, longitude);
      sendBluetoothLocation(latitude, longitude);
      gpsSent = true;
    }
  } else {
    gpsSent = false;
    callMade = false;
  }

  // DEBUG: Print SIM800L responses to Serial Monitor
  while (sim800l.available()) {
    Serial.write(sim800l.read());
  }

  delay(500);
}

// TOUCH SENSOR TOGGLE + ULTRASONIC + BUZZER CONTROL
void handleTouchSensor() {
  bool currentTouchState = digitalRead(TOUCH_SENSOR);

  if (currentTouchState == HIGH && lastTouchState == LOW) {
    alertEnabled = !alertEnabled;

    if (alertEnabled) {
      // Beep once for 0.1 second when turning on
      digitalWrite(BUZZER, HIGH);
      delay(100); // 0.1 second
      digitalWrite(BUZZER, LOW);
    } else {
      // Beep twice for 0.1 second each when turning off
      for (int i = 0; i < 2; i++) {
        digitalWrite(BUZZER, HIGH);
        delay(100); // 0.1 second
        digitalWrite(BUZZER, LOW);
        delay(100); // Short delay between beeps
      }
    }

    Serial.print("Ultrasonic & Buzzer: ");
    Serial.println(alertEnabled ? "ENABLED" : "DISABLED");

    delay(300); // Debounce
  }

  lastTouchState = currentTouchState;

  if (alertEnabled) {
    long distance = getDistance();
    Serial.print("Distance: ");
    Serial.println(distance);

    if (distance > 0 && distance <= 50) {
      digitalWrite(BUZZER, HIGH);
      Serial.println("BUZZER ON - Object close!");
    } else {
      digitalWrite(BUZZER, LOW);
    }
  } else {
    digitalWrite(BUZZER, LOW);
  }
}

// Get distance from ultrasonic sensor
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  return duration * 0.034 / 2;
}

// Read GPS, extract usable lat/lon
void getGPS() {
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    if (c == '$') {
      String sentence = gpsSerial.readStringUntil('\n');
      if (sentence.startsWith("GPGGA")) {
        parseGPS(sentence);
      }
    }
  }
}

// Parse GPGGA sentence and convert coordinates
void parseGPS(String nmea) {
  int commas[15], index = 0;
  for (int i = 0; i < nmea.length(); i++) {
    if (nmea[i] == ',') commas[index++] = i;
  }

  if (index > 4) {
    String rawLat = nmea.substring(commas[1] + 1, commas[2]);
    String latDir = nmea.substring(commas[2] + 1, commas[3]);
    String rawLon = nmea.substring(commas[3] + 1, commas[4]);
    String lonDir = nmea.substring(commas[4] + 1, commas[5]);

    if (rawLat.length() >= 6 && rawLon.length() >= 6) {
      float lat = convertToDecimal(rawLat);
      float lon = convertToDecimal(rawLon);

      if (latDir == "S") lat *= -1;
      if (lonDir == "W") lon *= -1;

      latitude = String(lat, 6);
      longitude = String(lon, 6);

      Serial.println("Latitude: " + latitude);
      Serial.println("Longitude: " + longitude);
    }
  }
}

// Convert NMEA degree+minute to decimal degrees
float convertToDecimal(String nmeaCoord) {
  float raw = nmeaCoord.toFloat();
  int degrees = int(raw / 100);
  float minutes = raw - (degrees * 100);
  return degrees + (minutes / 60.0);
}

// Send SMS with lat, lon, and maps link
void sendSMS(String lat, String lon) {
  String link = "https://www.google.com/maps/search/?api=1&query=" + lat + "," + lon;

  sim800l.println("AT");
  delay(1000);
  sim800l.println("AT+CMGF=1"); // Text mode
  delay(1000);
  sim800l.println("AT+CMGS=\"+91xxxxxxxxxx\""); // Replace with your number
  delay(1000);
  sim800l.print("Emergency Location:\nLat: ");
  sim800l.print(lat);
  sim800l.print("\nLon: ");
  sim800l.print(lon);
  sim800l.print("\n");
  sim800l.println(link);
  delay(500);
  sim800l.write(26); // CTRL+Z
  delay(5000);

  Serial.println("SMS Sent.");
}

// Make emergency call
void makeCall() {
  sim800l.println("ATD+91xxxxxxxxxx;"); // Replace with your number
  delay(20000); // Let it ring
  sim800l.println("ATH"); // Hang up
  Serial.println("Call made and ended.");
}
 
// Send location over Bluetooth
void sendBluetoothLocation(String lat, String lon) {
  String link = "https://www.google.com/maps/search/?api=1&query=" + lat + "," + lon;
  bluetooth.println("Emergency Location:");
  bluetooth.println("Lat: " + lat);
  bluetooth.println("Lon: " + lon);
  bluetooth.println(link);
  Serial.println("Location sent over Bluetooth.");
}
