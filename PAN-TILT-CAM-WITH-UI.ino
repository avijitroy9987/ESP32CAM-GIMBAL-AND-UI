#include "esp_camera.h"
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <iostream>
#include <sstream>
#include <ESP32Servo.h>

#define DUMMY_SERVO1_PIN 12     
#define DUMMY_SERVO2_PIN 13     
#define PAN_PIN 14
#define TILT_PIN 15

Servo dummyServo1;
Servo dummyServo2;
Servo panServo;
Servo tiltServo;

//Camera related constants
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

const char* ssid     = "hello world";
const char* password = "87654321";

AsyncWebServer server(80);
AsyncWebSocket wsCamera("/Camera");
AsyncWebSocket wsServoInput("/ServoInput");
uint32_t cameraClientId = 0;

#define LIGHT_PIN 4
const int PWMLightChannel = 4;

const char* htmlHomePage PROGMEM = R"HTMLHOMEPAGE(
<!DOCTYPE html>
<html>
  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <style>
    .noselect {
      -webkit-touch-callout: none;
      -webkit-user-select: none;
      -khtml-user-select: none;
      -moz-user-select: none;
      -ms-user-select: none;
      user-select: none;
    }

    .slidecontainer {
      width: 100%;
    }

    .slider {
      -webkit-appearance: none;
      width: 100%;
      height: 30px;
      border-radius: 10px;
      background: #121212;
      outline: none;
      opacity: 0.7;
      -webkit-transition: .2s;
      transition: opacity .2s;
    }

    .slider:hover {
      opacity: 1;
    }

    .slider::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 40px;
      height: 40px;
      border-radius: 50%;
      background: red;
      cursor: pointer;
    }

    .slider::-moz-range-thumb {
      width: 40px;
      height: 40px;
      border-radius: 50%;
      background: red;
      cursor: pointer;
    }

    #cameraImage {
      transition: transform 0.5s ease;
      max-width: 100%;
      height: auto;
    }

    #controlsTable {
      position: relative;
      bottom: 0;
      margin-top: 20px;
      width: 720px;
      margin-left: auto;
      margin-right: auto;
      table-layout: fixed;
    }

    .control-label {
      text-align: center;
      font-weight: bold;
      margin-top: 8px;
    }

    .flip-button {
      padding: 10px 20px;
      background-color: teal;
      color: white;
      border: none;
      border-radius: 10px;
      font-size: 18px;
      cursor: pointer;
      margin: 10px 5px;
    }
    </style>

  </head>
  <body class="noselect" align="center" style="background-color:#404040">

    <div style="position: relative; display: inline-block; margin-top: 100px; margin-bottom: 150px;">
  <img id="cameraImage" src="" style="width:1020px;height:820px">
</div>

    <div class="control-container" id="controlContainer">
      <table id="controlsTable" CELLSPACING=10>
        <tr>
          <td colspan=3>
            <div class="slidecontainer">
              <input type="range" min="0" max="180" value="90" class="slider" id="Pan" oninput='sendButtonInput("Pan",value)'>
              <div class="control-label">Pan</div>
            </div>
          </td>
        </tr> 
        <tr>       
          <td colspan=3>
            <div class="slidecontainer">
              <input type="range" min="0" max="180" value="90" class="slider" id="Tilt" oninput='sendButtonInput("Tilt",value)'>
              <div class="control-label">Tilt</div>
            </div>
          </td>   
        </tr>
        <tr>       
          <td colspan=3>
            <div class="slidecontainer">
              <input type="range" min="0" max="255" value="0" class="slider" id="Light" oninput='sendButtonInput("Light",value)'>
              <div class="control-label">Light</div>
            </div>
          </td>   
        </tr>      
      </table>

      <!-- Flip Buttons Moved Below Sliders -->
      <div style="margin-top: 20px;">
        <button class="flip-button" onclick="flipCamera()">Flip</button>
        <button class="flip-button" onclick="flipVertical()">Flip Vertical</button>
        <button class="flip-button" onclick="rotateCamera()">Rotate</button>
      </div>
    </div>

    <script>
      var webSocketCameraUrl = "ws:\/\/" + window.location.hostname + "/Camera";
      var webSocketServoInputUrl = "ws:\/\/" + window.location.hostname + "/ServoInput";      
      var websocketCamera;
      var websocketServoInput;

      function initCameraWebSocket() {
        websocketCamera = new WebSocket(webSocketCameraUrl);
        websocketCamera.binaryType = 'blob';
        websocketCamera.onopen = function(event){};
        websocketCamera.onclose = function(event){setTimeout(initCameraWebSocket, 2000);};
        websocketCamera.onmessage = function(event) {
          var imageId = document.getElementById("cameraImage");
          imageId.src = URL.createObjectURL(event.data);
        };
      }

      function initServoInputWebSocket() {
        websocketServoInput = new WebSocket(webSocketServoInputUrl);
        websocketServoInput.onopen = function(event) {
          sendButtonInput("Pan", document.getElementById("Pan").value);
          sendButtonInput("Tilt", document.getElementById("Tilt").value);
          sendButtonInput("Light", document.getElementById("Light").value);          
        };
        websocketServoInput.onclose = function(event){setTimeout(initServoInputWebSocket, 2000);};
        websocketServoInput.onmessage = function(event){};        
      }

      function initWebSocket() {
        initCameraWebSocket();
        initServoInputWebSocket();
      }

      function sendButtonInput(key, value) {
        var data = key + "," + value;
        websocketServoInput.send(data);
      }

      function flipCamera() {
        const img = document.getElementById("cameraImage");
        if (img.style.transform.includes("scaleX(-1)")) {
          img.style.transform = img.style.transform.replace("scaleX(-1)", "scaleX(1)");
        } else {
          img.style.transform += " scaleX(-1)";
        }
      }

      function flipVertical() {
        const img = document.getElementById("cameraImage");
        if (img.style.transform.includes("scaleY(-1)")) {
          img.style.transform = img.style.transform.replace("scaleY(-1)", "scaleY(1)");
        } else {
          img.style.transform += " scaleY(-1)";
        }
      }

      function rotateCamera() {
        const img = document.getElementById("cameraImage");
        const current = img.style.transform;
        const match = current.match(/rotate(\d+)deg/);
        let angle = match ? parseInt(match[1]) : 0;
        angle = (angle + 90) % 360;
        img.style.transform = current.replace(/rotate\d+deg/, '') + ' rotate(' + angle + 'deg)';
      }

      window.onload = initWebSocket;
      document.getElementById("controlsTable").addEventListener("touchend", function(event){
        event.preventDefault()
      });      
    </script>
  </body>    
</html>
)HTMLHOMEPAGE";

void handleRoot(AsyncWebServerRequest *request) 
{
  request->send_P(200, "text/html", htmlHomePage);
}

void handleNotFound(AsyncWebServerRequest *request) 
{
    request->send(404, "text/plain", "File Not Found");
}

void onServoInputWebSocketEvent(AsyncWebSocket *server, 
                      AsyncWebSocketClient *client, 
                      AwsEventType type,
                      void *arg, 
                      uint8_t *data, 
                      size_t len) 
{                      
  switch (type) 
  {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      panServo.write(90);
      tiltServo.write(90);
      ledcWrite(PWMLightChannel, 0);
      break;
    case WS_EVT_DATA:
      AwsFrameInfo *info;
      info = (AwsFrameInfo*)arg;
      if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) 
      {
        std::string myData = "";
        myData.assign((char *)data, len);
        Serial.printf("Key,Value = [%s]\n", myData.c_str());        
        std::istringstream ss(myData);
        std::string key, value;
        std::getline(ss, key, ',');
        std::getline(ss, value, ',');
        if ( value != "" )
        {
          int valueInt = atoi(value.c_str());
          if (key == "Pan")
          {
            panServo.write(valueInt);
          }
          else if (key == "Tilt")
          {
            tiltServo.write(valueInt);   
          }
          else if (key == "Light")
          {
            ledcWrite(PWMLightChannel, valueInt);         
          }           
        }
      }
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
    default:
      break;  
  }
}

void onCameraWebSocketEvent(AsyncWebSocket *server, 
                      AsyncWebSocketClient *client, 
                      AwsEventType type,
                      void *arg, 
                      uint8_t *data, 
                      size_t len) 
{                      
  switch (type) 
  {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      cameraClientId = client->id();
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      cameraClientId = 0;
      break;
    case WS_EVT_DATA:
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
    default:
      break;  
  }
}

void setupCamera()
{
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  config.frame_size = FRAMESIZE_VGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) 
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }  

  if (psramFound())
  {
    heap_caps_malloc_extmem_enable(20000);  
    Serial.printf("PSRAM initialized. malloc to take memory from psram above this size");    
  }  
}

void sendCameraPicture()
{
  if (cameraClientId == 0)
  {
    return;
  }
  unsigned long  startTime1 = millis();
  //capture a frame
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) 
  {
      Serial.println("Frame buffer could not be acquired");
      return;
  }

  unsigned long  startTime2 = millis();
  wsCamera.binary(cameraClientId, fb->buf, fb->len);
  esp_camera_fb_return(fb);
    
  //Wait for message to be delivered
  while (true)
  {
    AsyncWebSocketClient * clientPointer = wsCamera.client(cameraClientId);
    if (!clientPointer || !(clientPointer->queueIsFull()))
    {
      break;
    }
    delay(1);
  }
  
  unsigned long  startTime3 = millis();  
  Serial.printf("Time taken Total: %d|%d|%d\n",startTime3 - startTime1, startTime2 - startTime1, startTime3-startTime2 );
}

void setUpPinModes()
{
  dummyServo1.attach(DUMMY_SERVO1_PIN);
  dummyServo2.attach(DUMMY_SERVO2_PIN);  
  panServo.attach(PAN_PIN);
  tiltServo.attach(TILT_PIN);

  //Set up flash light
  ledcSetup(PWMLightChannel, 1000, 8);
  pinMode(LIGHT_PIN, OUTPUT);    
  ledcAttachPin(LIGHT_PIN, PWMLightChannel);
}


void setup(void) 
{
  setUpPinModes();
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);
      
  wsCamera.onEvent(onCameraWebSocketEvent);
  server.addHandler(&wsCamera);

  wsServoInput.onEvent(onServoInputWebSocketEvent);
  server.addHandler(&wsServoInput);

  server.begin();
  Serial.println("HTTP server started");

  setupCamera();
}


void loop() 
{
  wsCamera.cleanupClients(); 
  wsServoInput.cleanupClients(); 
  sendCameraPicture(); 
}
