#include <Pixy2.h>
#include <Servo.h>

Pixy2 pixy;
Servo steeringServo;
const int redSignature = 1; // Red color signature
const int greenSignature = 2; // Green color signature

// Ultrasonic sensor pins
const int leftSensorPin = A0;
const int centerSensorPin = A1;
const int rightSensorPin = A2;

// Servo and DC motor pins
const int servoPin = 9;
const int motorPin = 10;

// Sensor thresholds for obstacle avoidance
const int obstacleThresholdLeft = 15; 
const int obstacleThresholdRight = 15; 

// Servo angles for left and right steering limits
const int leftSteeringAngle = 38;
const int rightSteeringAngle = 128;

// Function to read ultrasonic sensor distance
float readUltrasonicSensor(int sensorPin) {
  long duration, distanceCm;
  pinMode(sensorPin, OUTPUT);
  digitalWrite(sensorPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorPin, LOW);
  pinMode(sensorPin, INPUT);
  duration = pulseIn(sensorPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  return distanceCm;
}

void setup() {
  Serial.begin(9600);
  pixy.init();
  steeringServo.attach(servoPin);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Read Pixy2 camera
  pixy.ccc.getBlocks();
  int redBlockCount = pixy.ccc.numBlocks;
  int greenBlockCount = 0;

  // Look for red and green color blocks
  for (int i = 0; i < redBlockCount; i++) {
    if (pixy.ccc.blocks[i].signature == redSignature) {
      redBlockCount++;
    }
    else if (pixy.ccc.blocks[i].signature == greenSignature) {
      greenBlockCount++;
    }
  }

  // Read ultrasonic sensor distances
  float leftDistance = readUltrasonicSensor(leftSensorPin);
  float centerDistance = readUltrasonicSensor(centerSensorPin);
  float rightDistance = readUltrasonicSensor(rightSensorPin);

  // Steering based on Pixy2 camera detection
  if (redBlockCount > 0) {
    // Red object detected, steer right
    steeringServo.write(rightSteeringAngle);
    delay(1500);
    steeringServo.write(leftSteeringAngle); // Return to the center position
  }
  else if (greenBlockCount > 0) {
    // Green object detected, steer left
    steeringServo.write(leftSteeringAngle);
    delay(1500); 
    steeringServo.write(rightSteeringAngle); // Return to the center position
  }

  // Obstacle avoidance based on ultrasonic sensor readings
  if (leftDistance < obstacleThresholdLeft && centerDistance >= rightDistance) {
    // Obstacle detected on the left, steer right
    steeringServo.write(rightSteeringAngle);
    delay(2000); 
    steeringServo.write(leftSteeringAngle); // Return to the center position
  }
  else if (rightDistance < obstacleThresholdRight && centerDistance >= leftDistance) {
    // Obstacle detected on the right, steer left
    steeringServo.write(leftSteeringAngle);
    delay(2000);
    steeringServo.write(rightSteeringAngle); // Return to the center position
  }

  // Move forward
  digitalWrite(motorPin, HIGH);
  delay(1000); 
  digitalWrite(motorPin, LOW);
}
