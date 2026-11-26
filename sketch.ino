#include <Wire.h>

#define MPU_ADDR 0x68
#define LEFT_BTN 3
#define RIGHT_BTN 10

void setup() {
  Serial.begin(115200);

  // MPU6050 I2C pins
  Wire.begin(8, 9);

  // Pushbuttons
  pinMode(LEFT_BTN, INPUT_PULLUP);
  pinMode(RIGHT_BTN, INPUT_PULLUP);

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  byte error = Wire.endTransmission();

  if (error == 0) {
    Serial.println("MPU6050 connected!");
  } else {
    Serial.println("MPU6050 not found. Check wiring.");
  }
}

void loop() {
  bool left = digitalRead(LEFT_BTN) == LOW;
  bool right = digitalRead(RIGHT_BTN) == LOW;

  // Read gyroscope data
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)MPU_ADDR, (uint8_t)6);

  if (Wire.available() == 6) {
    int16_t gx = (Wire.read() << 8) | Wire.read();
    int16_t gy = (Wire.read() << 8) | Wire.read();
    int16_t gz = (Wire.read() << 8) | Wire.read();

    Serial.print("GX: ");
    Serial.print(gx);
    Serial.print(" GY: ");
    Serial.print(gy);
    Serial.print(" GZ: ");
    Serial.print(gz);
  } else {
    Serial.print("MPU read error");
  }

  Serial.print(" | Left: ");
  Serial.print(left ? "PRESSED" : "Released");
  Serial.print(" | Right: ");
  Serial.println(right ? "PRESSED" : "Released");

  delay(200);
}
