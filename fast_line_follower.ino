// Motor and sensor pins
int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 7;
int enA = 5;
int enB = 6;
int out1 = 12;
int out2 = 11;
int out3 = 10;
int out4 = 9;
int out5 = 8;
int i = 0;
int led = 13;

// PID constants
float Kp = 20;
float Ki = 20;  // Adjust Ki based on your robot's behavior
float Kd = 10;

// PID variables
float error = 0;
float last_error = 0;
float integral = 0;
float derivative = 0;
float correction = 0;
int base_speed = 200;
int left_speed;
int right_speed;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(out1, INPUT);
  pinMode(out2, INPUT);
  pinMode(out3, INPUT);
  pinMode(out4, INPUT);
  pinMode(out5, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int s1 = digitalRead(out1);
  int s2 = digitalRead(out2);
  int s3 = digitalRead(out3);
  int s4 = digitalRead(out4);
  int s5 = digitalRead(out5);

  // Calculate the error based on sensor values
  error = calculateError(s1, s2, s3, s4, s5);

  // PID calculations
  integral += error;  // Accumulate the error over time
  derivative = error - last_error;  // Change in error
  correction = Kp * error + Ki * integral + Kd * derivative;  // PID formula
  last_error = error;  // Store current error for next iteration

  // Adjust motor speeds based on correction
  left_speed = base_speed + correction;
  right_speed = base_speed - correction;

  // Ensure the motor speeds are within range
  left_speed = constrain(left_speed, 0, 255);
  right_speed = constrain(right_speed, 0, 255);

  // Move the robot
  if (error == 0) {
    forward(base_speed, base_speed);  // Go straight
  } else if (error > 0) {
    right(left_speed, right_speed);  // Turn right
  } else if (error < 0) {
    left(left_speed, right_speed);  // Turn left
  }
  
delayMicroseconds(100);// Small delay for smoother operation
}

float calculateError(int s1, int s2, int s3, int s4, int s5) {
  // Calculate error based on sensor readings
  if (s1 == 0) return -2;
  if (s2 == 0  && s1 != 0) return -1;
  if (s3 == 0) return 0;
  if (s4 == 0  && s5 != 0) return 1;
  if (s5 == 0) return 2;

  // If no sensor is detecting the line, stop the robot
  if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1) {
    stop();
    return 0;  // Return a default value
  }
}

void forward(int left_speed, int right_speed) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, left_speed);
  analogWrite(enB, right_speed);
  digitalWrite(13, HIGH);
  delayMicroseconds(10);
  digitalWrite(13, LOW);
}

void right(int left_speed, int right_speed) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, left_speed);
  analogWrite(enB, right_speed);
}

void left(int left_speed, int right_speed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, left_speed);
  analogWrite(enB, right_speed);
}

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
