#define MOTORPIN 3

double currentSpeed = 0.0;
double targetSpeed = 100.0;
double previousError = 0.0;
double integral = 0.0;
double pwmSpeedOutput = 0.0;
double smoothedOutput = 0.0;
double kp = 1.0;
double ki = 0.0;
double kd = 0.0;
double timeInterval = 100;
double alpha = 0.3;
unsigned long currentTime = 0;
unsigned long previousTime = 0;

void setup() {
  previousTime = millis();
}

void loop() {
  currentTime = millis();
  if((currentTime-previousTime)>timeInterval){
    previousTime = currentTime;
    // currentSpeed = getMotorSpeed(); // SHOULD GET MOTOR SPEED FROM AN ENCODER BUT I CANT TEST IT CURRENTLY
    double error = targetSpeed - currentSpeed;
    integral += error * (timeInterval/1000.0);
    double derivative = (error-previousError) / (timeInterval/1000.0);
    pwmSpeedOutput = (kp * error) + (ki * integral) + (kd * derivative);
    smoothedOutput = alpha * pwmSpeedOutput + (1 - alpha) * smoothedOutput;
    analogWrite(MOTORPIN, (int)smoothedOutput); // EXPAMPLE MOTORPIN AS 3
    previousError = error;
  }
}
