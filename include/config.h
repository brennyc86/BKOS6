// BKOS6 Configuration
#pragma once

// Hardware configuration
#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 480
#define DISPLAY_ROTATION 0  // 0=landscape, 2=180° rotated

// WiFi configuration
#define WIFI_MAX_NETWORKS 10
#define WIFI_OPEN_NETWORKS_ENABLED true

// OTA configuration
#define OTA_SOURCES 4  // Newest, Previous, BKOS5a, BKOS5c

// Bluetooth configuration
#define BLUETOOTH_DEVICE_NAME "BKOS6-Boat"
#define BLUETOOTH_MAX_CONNECTIONS 3

// API configuration
#define API_PORT 80
#define WEBAPP_PORT 8080

// Database configuration
#define DATABASE_ENABLED true
#define LOG_BUFFER_SIZE 100
