# ESP32-Based-Teleoperated-Robotic-Arm-System
ESP32-based 6DOF robotic arm controlled wirelessly via PS4 controller using Bluepad32. PCA9685 ensures smooth servo control, with synchronized shoulder motion, joystick-based movement, pressure-sensitive gripper, and one-button home positioning.

# 🤖 ESP32 PS4 Controlled 6DOF Robotic Arm

![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Control](https://img.shields.io/badge/Control-PS4%20Controller-green)
![Driver](https://img.shields.io/badge/PWM-PCA9685-orange)
![License](https://img.shields.io/badge/License-Open--Source-lightgrey)



📌 Overview
This project demonstrates a 6DOF robotic arm controlled wirelessly using a PS4 controller and ESP32. The PCA9685 PWM driver enables smooth and precise control of multiple servo motors, while Bluepad32 provides seamless Bluetooth communication.


  Features
- Wireless PS4 controller control (Bluetooth)
- 6DOF robotic arm
- Smooth servo motion using PCA9685
- Dual shoulder mirrored movement
- Pressure-sensitive gripper (L2/R2)
- One-button home position reset



  Hardware Requirements
- ESP32 Development Board  
- PCA9685 16-Channel PWM Driver  
- Servo Motors (MG996R / SG90)  
- PS4 Controller (DualShock 4)  
- External 5V–6V Power Supply (≥5A recommended)  
- Jumper Wires  



 Wiring Connections

| PCA9685 | ESP32 |
|--------|------|
| VCC | 3.3V / 5V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

 Always use an external power supply for servos.

 Servo Mapping

| Joint | Channel |

 Base -> 0 |
 Shoulder Left -> 1 |
Shoulder Right  ->2 |
 Elbow -> 3 |
 Wrist Pitch -> 4 |
 Wrist Roll -> 5 |
 Gripper -> 6 |


 Controller Mapping _keys

| Control | Action |

| Left Stick X | Base rotation |
| Left Stick Y | Shoulder |
| Right Stick Y | Elbow |
| Right Stick X | Wrist |
| B Button | Wrist roll + |
| X Button | Wrist roll - |
| R2 Trigger | Close gripper |
| L2 Trigger | Open gripper |
| Y Button | Home position |


⚙️ Working Principle
- ESP32 connects to PS4 controller via Bluetooth (Bluepad32)
- Joystick inputs control servo angles
- PCA9685 generates PWM signals
- Shoulder servos move in mirrored motion
- Gripper responds to trigger pressure


  Robotic arm Home Position

void home_position(){
  moveServo(BASE_SERVO,70);
  moveServo(SHOULDER_LEFT,130);
  moveServo(ELBOW_SERVO,130);
  moveServo(WRIST_SERVO,0);
  moveServo(WRIST_ROLL,90);
  moveServo(GRIPPER_SERVO,150);
}

🛠️ Setup Instructions
   1. Install Libraries
        Wire.h
        Adafruit_PWMServoDriver
        Bluepad32
   2. Upload Code
        Select ESP32 board in Arduino IDE
        Upload the code
        3. Pair PS4 Controller
        Enable Bluetooth
        Pair controller using Bluepad32


  Notes
        Use external power supply (≥5A)
        Do not power servos from ESP32
        Calibrate SERVOMIN and SERVOMAX
        Avoid mechanical over-rotation


   Future Improvements
        Mobile App Control
        Motion Recording
        AI Object Detection
