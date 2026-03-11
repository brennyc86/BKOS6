// BKOS6 Core System
#pragma once

#include <Arduino.h>
#include <vector>
#include <string>

namespace Core {
    
    // System state
    struct SystemState {
        bool wifiConnected;
        bool bluetoothEnabled;
        bool otaUpdating;
        bool displayRotated;
        uint32_t freeHeap;
        uint32_t uptimeSeconds;
    };
    
    // OTA source types
    enum class OTASource {
        NEWEST,     // Latest BKOS6
        PREVIOUS,   // Previous BKOS6
        BKOS5A,     // User's BKOS5a
        BKOS5C      // Other AI's BKOS5c
    };
    
    // Initialize core systems
    void init();
    
    // Update core systems (call in loop)
    void update();
    
    // Get current system state
    SystemState getState();
    
    // OTA functions
    bool checkForUpdates();
    bool performOTA(OTASource source);
    void setOTASource(String url);
    
    // WiFi functions
    bool connectWiFi(String ssid, String password);
    bool disconnectWiFi();
    std::vector<String> getSavedNetworks();
    void addNetwork(String ssid, String password);
    void removeNetwork(String ssid);
    bool tryOpenNetworks(bool enable);
    
    // System info
    String getVersion();
    uint32_t getFreeHeap();
    uint32_t getUptime();
}
