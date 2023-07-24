This Arduino code is designed to control a robot car for a competition, specifically the World Robot Olympiad (WRO). The robot car is equipped with various sensors and actuators to navigate through the competition arena and achieve specific tasks.

Components Used:

Pixy2 Camera: A vision sensor that can detect color signatures. In this code, it identifies objects of two colors: red and green.

Ultrasonic Sensors: Three ultrasonic sensors are placed on the left, right, and center of the car. These sensors measure the distance of the car from nearby obstacles (e.g., walls) and play a vital role in obstacle avoidance.

Servo Motor: The servo motor is used for steering the car. It can rotate within a range of 38 degrees left to 128 degrees right, which allows the car to turn left or right.

DC Motor: This motor is used to control the movement of the car and allows it to move forward or backward.

Functionality:

Color-Based Steering:

The Pixy2 camera continuously scans its field of view for color signatures (red and green).
If a red object is detected, the car steers to pass by the right side of the object.
If a green object is detected, the car steers to pass by the left side of the object.
Obstacle Avoidance:

The three ultrasonic sensors measure the distances from nearby obstacles.
If the left sensor detects an obstacle too close to the car, it steers the car to the right to avoid the obstacle.
If the right sensor detects an obstacle too close to the car, it steers the car to the left to avoid the obstacle.
The center sensor helps maintain balance and ensures the car avoids obstacles while moving straight.
Competition Achievement:

This code was used for a WRO competition, where the robot car successfully demonstrated effective color-based steering and obstacle avoidance strategies. The car's precise control and smart navigation enabled it to secure the runner-up position in the competition.
