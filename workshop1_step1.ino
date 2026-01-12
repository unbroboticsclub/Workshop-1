// Motor pins for H-bridge
int IN1 = 9, IN2 = 8, IN3 = 7, IN4 = 6;
int ENA = 5, ENB = 3;

// Motor speed variables
int motorSpeedL = 200; //adjust left motor speed
int motorSpeedR = 200; //adjust right motor speed

void setup() {
  Serial.begin(9600);

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
}

void loop() {
  delay(1000); 
  
  moveForward(); 
  delay(2000); 

  stopMotors();
  delay(1000);

  moveBackward();
  delay(2000); 
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

