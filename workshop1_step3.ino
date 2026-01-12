#include <Wire.h>
#include <MPU6050_light.h>
MPU6050 mpu(Wire);

// Motor pins for H-bridge
int IN1 = 9, IN2 = 8, IN3 = 7, IN4 = 6;
int ENA = 5, ENB = 3;

// Motor speed variables
int motorSpeedL = 150; //adjust left motor speed
int motorSpeedR = 120; //adjust right motor speed

// Ultrasonic sensor pins
int trigPin = 10, echoPin = 11;

void setup() {
  Serial.begin(9600);

  // declare Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // declare motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Set motor speed using PWM
  analogWrite(ENA, motorSpeedL);  // Motor A speed
  analogWrite(ENB, motorSpeedR);  // Motor B speed

  // Initialize MPU6050
  Wire.begin();
  mpu.begin();
}

void loop() {
  delay(1000); //wait for 1 second

  moveForward();  
  delay(1000);

  stopMotors();
  delay(200);
  
  turn180();
}

void moveForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

long getDistance() {
  digitalWrite(trigPin, LOW); //resets signal for 2ms
  delay(2);
  digitalWrite(trigPin, HIGH); //sends signal for 10ms
  delay(10);
  digitalWrite(trigPin, LOW); //resets the signal

  //measures how long sound wave travelled
  long duration = pulseIn(echoPin, HIGH); 
  return (duration / 2) / 29.1; // Convert to cm
}

void rotateCCW() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turn180() {
  mpu.update();
  float initialAngle = mpu.getAngleZ();
  float currentAngle = mpu.getAngleZ();

  float targetAngle = initialAngle + 180;

  float tolerance = 2;
  rotateCCW();

  while (abs(targetAngle - currentAngle) > tolerance) {
    mpu.update();
    currentAngle = mpu.getAngleZ();
  }
  stopMotors();
}
