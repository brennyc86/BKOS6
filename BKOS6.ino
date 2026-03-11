/*
 * BKOS6 - Modern Boat Control System
 * ESP32-S3 with 7" 800x480 display
 * Modular architecture with OTA, WiFi, Bluetooth, API
 */

// Core includes
#include "include/core.h"
#include "include/hardware.h"
#include "include/ui.h"
#include "include/services.h"

// Global system state
Core::SystemState systemState;

void setup() {
  // Initialize serial
  Serial.begin(115200);
  Serial.println("\n=== BKOS6 Starting ===");
  
  // Initialize hardware
  Hardware::init();
  
  // Initialize core systems
  Core::init();
  
  // Initialize UI
  UI::init();
  
  // Initialize services
  Services::init();
  
  Serial.println("BKOS6 Setup complete");
}

void loop() {
  // Update core systems
  Core::update();
  
  // Update UI
  UI::update();
  
  // Update services
  Services::update();
  
  // Small delay
  delay(10);
}
