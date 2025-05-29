# ESP32CAM-GIMBAL-AND-UI
# ESP32-CAM Pan-Tilt Web Control System

This project provides a complete web-based camera monitoring and control solution using the ESP32-CAM module. It enables remote control of two servos (for pan and tilt) and an LED light using a clean and responsive web interface.

## ✨ Features

- 📸 Live streaming from the ESP32-CAM using WebSockets
- 🎮 Pan and Tilt control with sliders
- 💡 Brightness control of onboard light (via PWM)
- 🔁 Camera flipping (horizontal, vertical) and rotation
- 📱 Mobile-friendly responsive interface
- ⚡ Fast performance using `ESPAsyncWebServer` and `ESPAsyncTCP`
- 🧠 Servo control using `ESP32Servo` library

## 📷 Hardware Requirements

- ESP32-CAM module
- 2x Servo motors (pan and tilt)
- Optional: Additional dummy servos (for simulation or extension)
- LED (connected to GPIO 4, controlled via PWM)
- Power supply (ensure stable 5V for servos and ESP32-CAM)

## 📌 Pin Configuration

| Component     | GPIO Pin |
|---------------|----------|
| Pan Servo     | 14       |
| Tilt Servo    | 15       |
| Dummy Servo 1 | 12       |
| Dummy Servo 2 | 13       |
| Light LED     | 4 (PWM)  |
| Camera Pins   | Default ESP32-CAM configuration |

## 📡 Setup Instructions

1. **Install Arduino IDE** and ESP32 board support.
2. **Install Required Libraries:**
   - `ESPAsyncWebServer`
   - `ESPAsyncTCP`
   - `ESP32Servo`
3. **Update WiFi Credentials:**
   Replace the `ssid` and `password` in the code with your own WiFi network.

4. **Upload the Code** to the ESP32-CAM using an FTDI programmer.
5. **Access the Interface:**
   - Open serial monitor to see the IP address assigned.
   - Open the IP in your browser.
   - Use sliders and buttons to control pan, tilt, and light.

## 🌐 Web Interface

- Live camera stream
- Sliders to control Pan, Tilt, and Light
- Buttons for horizontal/vertical flip and rotation

## 🔧 Notes

- Servo angles range from 0° to 180°.
- Light PWM ranges from 0 (off) to 255 (max brightness).
- Be cautious about servo power consumption — consider external power for stability.

## 🧑‍💻 Author

Created by [MADAN R]

## 🪪 License

See [LICENSE](LICENSE) file for licensing information.
