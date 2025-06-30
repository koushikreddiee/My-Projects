
#include "esp_camera.h"
#include <WiFi.h>
#include <FirebaseESP32.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Replace with your Firebase project credentials
#define FIREBASE_HOST "your-project.firebaseio.com"
#define FIREBASE_AUTH "your_firebase_database_secret"

// Pin where the LDR sensor is connected
#define LDR_PIN 34

// Firebase setup
FirebaseData firebaseData;

void startCameraServer();

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // Camera config
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_VGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;

  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  // Start web server
  startCameraServer();
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  Serial.println(ldrValue);

  // Threshold for laser trip detection (adjust as needed)
  if (ldrValue < 500) {
    Serial.println("Intrusion Detected!");
    
    // Capture image
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      return;
    }

    // Upload alert to Firebase
    String path = "/alerts/" + String(millis());
    if (Firebase.setString(firebaseData, path, "Intrusion detected at " + String(millis()))) {
      Serial.println("Data sent to Firebase");
    } else {
      Serial.println("Firebase push failed");
    }

    esp_camera_fb_return(fb);
    delay(10000); // Wait to avoid spamming
  }
  delay(500);
}

void startCameraServer() {
  Serial.println("Camera server started");
  // Basic endpoint handling can be added here if needed
}
