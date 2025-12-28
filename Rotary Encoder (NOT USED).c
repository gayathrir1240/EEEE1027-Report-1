#include <LiquidCrystal.h>

LiquidCrystal lcd_1(8, 9, 4, 5, 6, 7);

#define enA 3
#define in1 12
#define in2 13

#define enB 11
#define in3 A1
#define in4 A2

#define IR_LEFT 4
#define IR_RIGHT 5

#define ENC_A 2
#define ENC_B 3

int MOTOR_SPEED = 150;

volatile long encoderCount = 0;
float distanceCM = 0.0;
const float WHEEL_DIAMETER_CM = 6.5;
const int PULSES_PER_REV = 20;

const float TARGET_DISTANCE = 90.0;
bool stoppedOnce = false;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  analogWrite(enA, MOTOR_SPEED);
  analogWrite(enB, MOTOR_SPEED);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENC_A), encoderISR, CHANGE);

  lcd_1.begin(16, 2);
  lcd_1.print("Bear Moving");
}

void encoderISR() {
  int aState = digitalRead(ENC_A);
  int bState = digitalRead(ENC_B);
  if (aState == bState) {
    encoderCount++;
  } else {
    encoderCount--;
  }
  distanceCM = (encoderCount / (float)PULSES_PER_REV) * (PI * WHEEL_DIAMETER_CM);
}

void loop() {
  lcd_1.setCursor(0, 1);
  lcd_1.print("Dist:");
  lcd_1.print(distanceCM);
  lcd_1.print("cm   ");

  if (!stoppedOnce && distanceCM >= TARGET_DISTANCE) {
    Stop();
    lcd_1.setCursor(0, 0);
    lcd_1.print("90cm STOP");
    delay(2000);
    stoppedOnce = true;
  }

  int leftVal = digitalRead(IR_LEFT);
  int rightVal = digitalRead(IR_RIGHT);

  if (leftVal == LOW && rightVal == LOW) {
    Stop();
    delay(200);
    leftVal = digitalRead(IR_LEFT);
    rightVal = digitalRead(IR_RIGHT);
    if (leftVal == LOW && rightVal == LOW) {
      smallForwardStep();
    }
    Stop();
    delay(180);
    return;
  } else if (leftVal == LOW && rightVal == HIGH) {
    Stop();
    delay(250);
    if (digitalRead(IR_RIGHT) == HIGH) smallRightTurn();
    Stop();
    delay(180);
    return;
  } else if (leftVal == HIGH && rightVal == LOW) {
    Stop();
    delay(250);
    if (digitalRead(IR_LEFT) == HIGH) smallLeftTurn();
    Stop();
    delay(180);
    return;
  } else {
    Stop();
  }
}

void smallForwardStep() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(200);
}

void smallLeftTurn() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(250);
}

void smallRightTurn() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(250);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
