// BKOS6 Core Implementation
#include "../../include/core.h"
#include <WiFi.h>
#include <Update.h>
#include <vector>
#include <Preferences.h>

namespace Core {
    
    // Global state
    SystemState systemState;
    Preferences preferences;
    std::vector<String> savedNetworks;
    
    void init() {
        Serial.println("Core::init()");
        
        // Initialize preferences
        preferences.begin("bkos6", false);
        
        // Load saved networks
        uint8_t count = preferences.getUInt("wifi_count", 0);
        for (uint8_t i = 0; i < count; i++) {
            String ssid = preferences.getString("wifi_" + String(i), "");
            if (ssid.length() > 0) {
                savedNetworks.push_back(ssid);
            }
        }
        
        // Initialize system state
        systemState.wifiConnected = false;
        systemState.bluetoothEnabled = false;
        systemState.otaUpdating = false;
        systemState.displayRotated = false;
        systemState.freeHeap = ESP.getFreeHeap();
        systemState.uptimeSeconds = 0;
        
        Serial.println("Core initialized");
    }
    
    void update() {
        // Update system state
        systemState.freeHeap = ESP.getFreeHeap();
        systemState.uptimeSeconds = millis() / 1000;
        systemState.wifiConnected = WiFi.status() == WL_CONNECTED;
        
        // Check for OTA updates every 5 minutes
        static unsigned long lastOTACheck = 0;
        if (millis() - lastOTACheck > 300000) { // 5 minutes
            checkForUpdates();
            lastOTACheck = millis();
        }
    }
    
    SystemState getState() {
        return systemState;
    }
    
    bool checkForUpdates() {
        Serial.println("Checking for OTA updates...");
        // TODO: Implement multi-source OTA check
        return false;
    }
    
    bool performOTA(OTASource source) {
        Serial.print("Performing OTA from source: ");
        switch(source) {
            case OTASource::NEWEST: Serial.println("NEWEST"); break;
            case OTASource::PREVIOUS: Serial.println("PREVIOUS"); break;
            case OTASource::BKOS5A: Serial.println("BKOS5A"); break;
            case OTASource::BKOS5C: Serial.println("BKOS5C"); break;
        }
        // TODO: Implement OTA download and flash
        return false;
    }
    
    void setOTASource(String url) {
        preferences.putString("ota_url", url);
    }
    
    bool connectWiFi(String ssid, String password) {
        Serial.println("Connecting to WiFi: " + ssid);
        WiFi.begin(ssid.c_str(), password.c_str());
        
        // Wait for connection
        for (int i = 0; i < 20; i++) {
            if (WiFi.status() == WL_CONNECTED) {
                Serial.println("WiFi connected");
                // Save network if not already saved
                bool found = false;
                for (const auto& saved : savedNetworks) {
                    if (saved == ssid) found = true;
                }
                if (!found) {
                    savedNetworks.push_back(ssid);
                    preferences.putUInt("wifi_count", savedNetworks.size());
                    preferences.putString("wifi_" + String(savedNetworks.size()-1), ssid);
                }
                return true;
            }
            delay(500);
        }
        Serial.println("WiFi connection failed");
        return false;
    }
    
    bool disconnectWiFi() {
        WiFi.disconnect();
        return true;
    }
    
    std::vector<String> getSavedNetworks() {
        return savedNetworks;
    }
    
    void addNetwork(String ssid, String password) {
        // Already saved in connectWiFi
    }
    
    void removeNetwork(String ssid) {
        for (size_t i = 0; i < savedNetworks.size(); i++) {
            if (savedNetworks[i] == ssid) {
                savedNetworks.erase(savedNetworks.begin() + i);
                preferences.putUInt("wifi_count", savedNetworks.size());
                // Re-save all networks
                for (size_t j = 0; j < savedNetworks.size(); j++) {
                    preferences.putString("wifi_" + String(j), savedNetworks[j]);
                }
                break;
            }
        }
    }
    
    bool tryOpenNetworks(bool enable) {
        preferences.putBool("open_networks", enable);
        return true;
    }
    
    String getVersion() {
        return "BKOS6 v1.0.0-alpha";
    }
    
    uint32_t getFreeHeap() {
        return ESP.getFreeHeap();
    }
    
    uint32_t getUptime() {
        return millis() / 1000;
    }
}
