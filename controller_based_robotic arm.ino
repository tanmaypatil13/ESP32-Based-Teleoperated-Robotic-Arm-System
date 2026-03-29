#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Bluepad32.h>

Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);

GamepadPtr myGamepad;

// Servo channels
#define BASE_SERVO 0
#define SHOULDER_LEFT 1
#define SHOULDER_RIGHT 2
#define ELBOW_SERVO 3
#define WRIST_SERVO 4
#define WRIST_ROLL 5
#define GRIPPER_SERVO 6

#define SERVOMIN 110
#define SERVOMAX 490

bool shoulderOpposite = true;

int currentPos[7] = {90,90,90,90,90,90,150};

// Convert angle → PWM pulse
int angleToPulse(int angle) {
  return map(angle,0,180,SERVOMIN,SERVOMAX);
}

// Servo movement
void moveServo(int servoChannel,int angle){

  angle = constrain(angle,0,180);

  if(servoChannel==SHOULDER_LEFT || servoChannel==SHOULDER_RIGHT){

    int mirrorAngle = shoulderOpposite ? (180-angle) : angle;

    pca9685.setPWM(SHOULDER_LEFT,0,angleToPulse(angle));
    pca9685.setPWM(SHOULDER_RIGHT,0,angleToPulse(mirrorAngle));

    currentPos[SHOULDER_LEFT] = angle;
  }
  else{

    pca9685.setPWM(servoChannel,0,angleToPulse(angle));
    currentPos[servoChannel] = angle;

  }
}

// Home position
void home_position(){

  moveServo(BASE_SERVO,70);
  moveServo(SHOULDER_LEFT,130);
  moveServo(ELBOW_SERVO,130);
  moveServo(WRIST_SERVO,0);
  moveServo(WRIST_ROLL,90);
  moveServo(GRIPPER_SERVO,150);
}

// Gamepad connected
void onConnectedGamepad(GamepadPtr gp) {
  Serial.println("Gamepad Connected!");
  myGamepad = gp;
}

// Gamepad disconnected
void onDisconnectedGamepad(GamepadPtr gp) {
  Serial.println("Gamepad Disconnected");
  myGamepad = nullptr;
}

void setup(){

  Serial.begin(115200);

  Wire.begin();

  pca9685.begin();
  pca9685.setPWMFreq(50);

  BP32.setup(&onConnectedGamepad, &onDisconnectedGamepad);

  Serial.println("Robotic Arm Ready");

  home_position();
}

void loop(){

  BP32.update();

  if(myGamepad && myGamepad->isConnected()){

    int lx = myGamepad->axisX();
    int ly = myGamepad->axisY();
    int rx = myGamepad->axisRX();
    int ry = myGamepad->axisRY();
    
int r2 = myGamepad->throttle();   // R2 trigger pressure
int l2 = myGamepad->brake();      // L2 trigger pressure

    // BASE
    if(lx > 200) moveServo(BASE_SERVO,currentPos[BASE_SERVO]+1);
    if(lx < -200) moveServo(BASE_SERVO,currentPos[BASE_SERVO]-1);

    // SHOULDER
    if(ly > 200) moveServo(SHOULDER_LEFT,currentPos[SHOULDER_LEFT]+1);
    if(ly < -200) moveServo(SHOULDER_LEFT,currentPos[SHOULDER_LEFT]-1);

    // ELBOW
    if(ry > 200) moveServo(ELBOW_SERVO,currentPos[ELBOW_SERVO]+1);
    if(ry < -200) moveServo(ELBOW_SERVO,currentPos[ELBOW_SERVO]-1);

    // WRIST
    if(rx > 200) moveServo(WRIST_SERVO,currentPos[WRIST_SERVO]+1);
    if(rx < -200) moveServo(WRIST_SERVO,currentPos[WRIST_SERVO]-1);

    // WRIST ROLL
    if(myGamepad->b()) moveServo(WRIST_ROLL,currentPos[WRIST_ROLL]+1);
    if(myGamepad->x()) moveServo(WRIST_ROLL,currentPos[WRIST_ROLL]-1);

    // PRESSURE SENSITIVE GRIPPER

    if(r2 > 20){
      int closeAngle = map(r2,0,1023,150,90);
      moveServo(GRIPPER_SERVO,closeAngle);
    }

    if(l2 > 20){
      int openAngle = map(l2,0,1023,150,180);
      moveServo(GRIPPER_SERVO,openAngle);
    }

    // HOME BUTTON
    if(myGamepad->y()) home_position();

  }

  delay(15);
}   change in this