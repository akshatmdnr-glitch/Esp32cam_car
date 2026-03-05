# ESP32-CAM Object Detection Car 🚗📷

A small autonomous robotic car built using **ESP32-CAM** that performs **basic object detection** and reacts to detected objects. The system combines **computer vision inference on the ESP32**, motor control, and WiFi streaming to create a simple edge-AI robotic platform.

This project demonstrates how low-cost embedded hardware can perform **real-time perception and actuation**, making it useful for learning **embedded AI, robotics, and autonomous systems**.

---

## Features

* 📷 Live camera feed using **ESP32-CAM**
* 🧠 Basic **object detection model (YOLO / Edge Impulse)** running on-device
* 🚗 **Motor control** for robotic car movement
* 📡 WiFi interface for streaming and monitoring
* ⚡ Lightweight edge inference suitable for microcontrollers
* 🛠 Simple hardware architecture for robotics experimentation

---

## Hardware Used

* ESP32-CAM (AI Thinker)
* L298N Motor Driver
* 2WD Robot Chassis
* DC Gear Motors
* Li-ion Battery Pack
* Jumper Wires

---

## Software Stack

* **Arduino Framework**
* **ESP32 Camera Library**
* **Edge Impulse / TinyML Object Detection**
* **Async Web Server**
* **C++**

---

## System Architecture

Camera → Image Capture → Object Detection Model → Decision Logic → Motor Control

1. ESP32-CAM captures frames.
2. Frames are passed to the **object detection model**.
3. Detected objects trigger **control logic**.
4. The car reacts (stop, move, avoid, or interact).

---

## Example Behaviors

* Stop when an object is detected
* Follow a detected object
* Trigger movement when a specific object appears

---

## Repository Structure

```
ESP32-CAM-Object-Detection-Car
│
├── src/
│   ├── main.ino
│   ├── motor_control.cpp
│   ├── camera_stream.cpp
│
├── model/
│   ├── object_detection_model.tflite
│
├── include/
│
└── README.md
```

---

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/esp32-cam-object-detection-car.git
cd esp32-cam-object-detection-car
```

### 2. Install Dependencies

Install in **Arduino IDE**:

* ESP32 Board Package
* ESP32 Camera Library
* AsyncTCP
* ESPAsyncWebServer

### 3. Upload the Code

Select:

```
Board: AI Thinker ESP32-CAM
```

Upload the firmware using an **FTDI programmer**.

---

## Applications

* Autonomous robotics experiments
* Embedded computer vision
* Edge AI research
* Smart surveillance robots

---

## Future Improvements

* SLAM based navigation
* Multi-object tracking
* ROS2 integration
* Remote control interface
* Path planning

---

## Author

**Akshat Mishra**

Robotics | Game AI | Autonomous Systems

LinkedIn:
https://www.linkedin.com/in/akshat-mishra-541167251/

---

## License

MIT License
