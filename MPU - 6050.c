#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd_1(8, 9, 4, 5, 6, 7);

#define enA 3
#define in1 12
#define in2 13

#define enB 11
#define in3 A1
#define in4 A2

int MOTOR_SPEED = 210;

unsigned long startTime;

const int MPU = 0x68;  
int16_t AcX, AcY, AcZ;

void setup() {
  Wire.begin();


  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);     
  Wire.endTransmission(true);

 
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  analogWrite(enA, MOTOR_SPEED);
  analogWrite(enB, MOTOR_SPEED);

  lcd_1.begin(16, 2);
  lcd_1.print("Bear Moving...");

  startTime = millis();
}

void loop() {

  unsigned long currentTime = millis();

  
  if (currentTime - startTime < 4000) {
    forward();
  }
  else {
    Stop();

    
    float angle = readAngle();

    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Ramp Angle:");

    lcd_1.setCursor(0, 1);
    lcd_1.print(angle);
    lcd_1.print(" deg");

    while (1); 
  }
}


void forward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


float readAngle() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();


  float angle = atan2(AcX, AcZ) * 180 / PI;

  return angle;
}
