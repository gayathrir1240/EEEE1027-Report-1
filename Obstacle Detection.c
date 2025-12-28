#include <Servo.h>
#include <Wire.h>

#define R1 2
#define R2 3
#define L1 4
#define L2 5

#define trigPin 6
#define echoPin 9

#define servoPin 6
Servo myServo;

long duration;
int distance;

void setup() {
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin);
  myServo.write(90);  

  Serial.begin(9600);
}

void loop() {
  distance = getDistance();

  if (distance > 0 && distance <= 10) {
    moveStop();
    Serial.println("Obstacle detected");
  } else {
    moveForward();
  }

  delay(50);
}


int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000);

  if (duration == 0) return 0;

  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}


void moveForward() {
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
}

void moveStop() {
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
}
