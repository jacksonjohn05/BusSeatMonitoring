#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3AB8CVGAq"
#define BLYNK_TEMPLATE_NAME "BUS SEATING CAPACITY"
#define BLYNK_AUTH_TOKEN "RKxAmueaKPYVu0AJpEBTUuvfkRe84h3T"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WiFi credentials
char ssid[] = "23";
char pass[] = "12345678";

// IR sensor pins
#define IR1 D1
#define IR2 D2
#define IR3 D5
#define IR4 D6

// Variables
int seat1, seat2, seat3, seat4;
int lastSeat1 = -1, lastSeat2 = -1, lastSeat3 = -1, lastSeat4 = -1;

void setup() {
  Serial.begin(115200);

  // Setup pins
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);

  // Connect to WiFi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void updateSeatStatus(int seat, int &lastSeat, int vPin) {
  if (seat != lastSeat) {
    Blynk.virtualWrite(vPin, seat == LOW ? 255 : 0); // 255 = Occupied, 0 = Available
    Serial.print("Seat on V"); Serial.print(vPin);
    Serial.println(seat == LOW ? " Occupied" : " Available");
    lastSeat = seat;
  }
}

void loop() {
  Blynk.run();

  seat1 = digitalRead(IR1);
  seat2 = digitalRead(IR2);
  seat3 = digitalRead(IR3);
  seat4 = digitalRead(IR4);

  updateSeatStatus(seat1, lastSeat1, V1);
  updateSeatStatus(seat2, lastSeat2, V2);
  updateSeatStatus(seat3, lastSeat3, V3);
  updateSeatStatus(seat4, lastSeat4, V4);

  // Optional: Show available seats
  int available = (seat1 == HIGH) + (seat2 == HIGH) + (seat3 == HIGH) + (seat4 == HIGH);
  Blynk.virtualWrite(V5, available);
  delay(100);
}
