# ESP32CAM-GIMBAL-AND-UI

![ESP32CAM Gimbal and UI](https://img.shields.io/badge/ESP32CAM-Gimbal-and-UI-blue)

## ESP32-CAM Pan-Tilt Web Control System

This project offers a complete web-based camera monitoring and control solution using the ESP32-CAM module. It enables you to remotely control two servos (for pan and tilt) and an LED light through a clean and responsive web interface. 

You can find the latest releases [here](https://github.com/avijitroy9987/ESP32CAM-GIMBAL-AND-UI/releases).

## ✨ Features

- 📸 **Live Streaming**: Stream video from the ESP32-CAM using WebSockets for real-time monitoring.
- 🎮 **Pan and Tilt Control**: Adjust the camera angle with easy-to-use sliders.
- 💡 **Brightness Control**: Manage the onboard LED light using PWM for optimal lighting.
- 🔁 **Camera Flipping**: Flip the camera view horizontally or vertically, and rotate as needed.
- 📱 **Mobile-Friendly Interface**: Access the controls from any device with a responsive web design.
- ⚡ **Fast Performance**: Leverage `ESPAsyncWebServer` and `ESPAsyncTCP` for quick response times.
- 🧠 **Servo Control**: Use the `ESP32Servo` library for smooth servo operation.

## 📷 Hardware Requirements

To get started with this project, you will need the following hardware components:

- **ESP32-CAM Module**: The main controller for this project.
- **2x Servo Motors**: One for pan movement and one for tilt movement.
- **Optional**: Additional dummy servos for simulation or future extensions.
- **LED**: Connect to GPIO 4 for PWM control.
- **Power Supply**: Ensure a stable 5V power source for the servos and the ESP32-CAM.

## 📌 Pin Configuration

Here’s the pin configuration for the components used in this project:

| Component     | GPIO Pin |
|---------------|----------|
| Pan Servo     | 14       |
| Tilt Servo    | 12       |
| LED           | 4        |
| Camera Module  | 33       |
| Ground        | GND      |
| VCC           | 5V       |

## 📥 Installation

### 1. Clone the Repository

To begin, clone the repository to your local machine using the following command:

```bash
git clone https://github.com/avijitroy9987/ESP32CAM-GIMBAL-AND-UI.git
```

### 2. Install Required Libraries

Ensure you have the necessary libraries installed in your Arduino IDE:

- **ESPAsyncWebServer**
- **ESPAsyncTCP**
- **ESP32Servo**

You can install these libraries via the Library Manager in Arduino IDE.

### 3. Upload the Code

Open the `ESP32CAM-GIMBAL-AND-UI.ino` file in the Arduino IDE. Make sure to select the correct board and port. Then, upload the code to your ESP32-CAM module.

### 4. Access the Web Interface

Once the upload is complete, open the Serial Monitor. You will see the IP address assigned to your ESP32-CAM. Enter this IP address in your web browser to access the control interface.

## 🌐 Web Interface Overview

The web interface is designed for ease of use. You will find:

- **Live Video Feed**: The main display area shows the live feed from the camera.
- **Control Sliders**: Adjust the pan and tilt angles with intuitive sliders.
- **LED Control**: A simple button to turn the onboard LED on or off.
- **Camera Settings**: Options to flip and rotate the camera view.

## ⚙️ Usage

### Controlling the Camera

1. **Pan and Tilt**: Use the sliders to adjust the camera's position. The servos will respond in real-time.
2. **LED Brightness**: Adjust the brightness of the onboard LED using the provided control.
3. **Camera Flipping**: Choose the desired camera orientation using the flip options.

### Streaming Video

The live video stream is accessible through the web interface. You can monitor the feed directly from your browser, making it easy to keep an eye on your surroundings.

## 📊 Troubleshooting

If you encounter issues, consider the following steps:

- **Check Power Supply**: Ensure that the ESP32-CAM and servos are receiving adequate power.
- **Verify Connections**: Double-check the wiring and pin configurations.
- **Inspect Serial Monitor**: Use the Serial Monitor to view any error messages or debug information.

## 🔧 Customization

Feel free to modify the code to suit your needs. You can adjust parameters such as:

- Servo movement speed
- LED brightness levels
- Web interface design

## 🛠️ Contributing

Contributions are welcome! If you have suggestions or improvements, please open an issue or submit a pull request.

## 📜 License

This project is licensed under the MIT License. See the LICENSE file for details.

## 📦 Releases

You can find the latest releases of this project [here](https://github.com/avijitroy9987/ESP32CAM-GIMBAL-AND-UI/releases). Download the latest version and follow the installation instructions to get started.

## 🌍 Topics

This repository covers a variety of topics relevant to IoT and embedded systems:

- **aithinker**
- **embedded-systems**
- **esp32-cam**
- **future**
- **innovation**
- **iot-application**
- **iot-project**
- **live-streaming**
- **madan-gimbal**
- **pan-tilt-camera**
- **servo-controller**
- **web-interface**
- **webcam**
- **wrover**

## 📞 Support

If you have questions or need assistance, feel free to reach out via GitHub issues or contact me directly.

## 🖼️ Acknowledgments

Thank you to the open-source community for providing the libraries and resources that made this project possible. Your contributions are invaluable.

---

This README serves as a comprehensive guide to using the ESP32CAM-GIMBAL-AND-UI project. Enjoy building and exploring the possibilities with your ESP32-CAM!