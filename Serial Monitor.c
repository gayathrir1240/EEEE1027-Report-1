#define enA A4
#define in1 2
#define in2 3
#define in3 5
#define in4 4
#define enB A3
#define R_S A1
#define L_S A2

int MOTOR_SPEED = 200; 

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(R_S, INPUT);
  pinMode(L_S, INPUT);

  analogWrite(enA, MOTOR_SPEED);
  analogWrite(enB, MOTOR_SPEED);

  Serial.begin(9600);
}

void loop() {
  int leftSensor  = digitalRead(L_S);
  int rightSensor = digitalRead(R_S);

  Serial.print("Left: "); Serial.print(leftSensor);
  Serial.print(" | Right: "); Serial.println(rightSensor);

  if (leftSensor == 0 && rightSensor == 0) {
    forward();   
  }
  else if (leftSensor == 1 && rightSensor == 0) {
    turnLeft(); 
  }
  else if (leftSensor == 0 && rightSensor == 1) {
    turnRight(); 
  }
  else if (leftSensor == 1 && rightSensor == 1) {
    Stop();      
  }
}


void forward() {
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


void turnLeft() {
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);
}


void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  
  digitalWrite(in4, LOW);
}


void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
