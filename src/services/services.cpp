// BKOS6 Services Implementation
#include "../../include/services.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Preferences.h>
#include <vector>

namespace Services {
    
    Preferences preferences;
    std::vector<LogEntry> logBuffer;
    bool bluetoothActive = false;
    bool apiServerActive = false;
    bool webAppActive = false;
    bool remoteAccessEnabled = false;
    
    void init() {
        Serial.println("Services::init()");
        
        preferences.begin("bkos6_services", false);
        
        // Initialize database
        initDatabase();
        
        // Initialize Bluetooth
        initBluetooth();
        
        // Initialize API
        initAPI();
        
        // Initialize WebApp
        initWebApp();
        
        Serial.println("Services initialized");
    }
    
    void update() {
        // Process log buffer
        static unsigned long lastLogSync = 0;
        if (millis() - lastLogSync > 60000 && logBuffer.size() > 0) { // Every minute
            syncLogsToCloud();
            lastLogSync = millis();
        }
    }
    
    bool sendMessage(MessageService service, String recipient, String message) {
        Serial.print("Sending message via ");
        switch(service) {
            case MessageService::SIGNAL:
                Serial.println("Signal");
                return sendSignal(recipient, message);
            case MessageService::WHATSAPP:
                Serial.println("WhatsApp");
                return sendWhatsApp(recipient, message);
            default:
                return false;
        }
    }
    
    bool sendSignal(String recipient, String message) {
        // TODO: Implement Signal API integration
        Serial.println("Signal: To " + recipient + ": " + message);
        logEvent("signal", "Message sent to " + recipient, 1.0);
        return true;
    }
    
    bool sendWhatsApp(String recipient, String message) {
        // TODO: Implement WhatsApp API integration
        Serial.println("WhatsApp: To " + recipient + ": " + message);
        logEvent("whatsapp", "Message sent to " + recipient, 1.0);
        return true;
    }
    
    void initBluetooth() {
        Serial.println("Bluetooth initialized (placeholder)");
        // TODO: Implement Bluetooth initialization
    }
    
    bool startBluetooth() {
        bluetoothActive = true;
        Serial.println("Bluetooth started");
        return true;
    }
    
    bool stopBluetooth() {
        bluetoothActive = false;
        Serial.println("Bluetooth stopped");
        return true;
    }
    
    bool sendBluetoothCommand(String command) {
        if (!bluetoothActive) return false;
        Serial.println("Bluetooth command: " + command);
        logEvent("bluetooth", "Command sent: " + command, 1.0);
        return true;
    }
    
    bool isBluetoothConnected() {
        return bluetoothActive;
    }
    
    void initAPI() {
        Serial.println("API initialized (placeholder)");
        // TODO: Implement AsyncWebServer initialization
    }
    
    bool startAPIServer() {
        apiServerActive = true;
        Serial.println("API server started on port 80");
        return true;
    }
    
    bool stopAPIServer() {
        apiServerActive = false;
        Serial.println("API server stopped");
        return true;
    }
    
    String handleAPIRequest(String endpoint, String method, String body) {
        if (!apiServerActive) return "{\"error\":\"API server not active\"}";
        
        Serial.println("API Request: " + endpoint + " " + method);
        
        // Simple echo for now
        return "{\"status\":\"ok\",\"endpoint\":\"" + endpoint + "\",\"method\":\"" + method + "\"}";
    }
    
    void initWebApp() {
        Serial.println("WebApp initialized (placeholder)");
    }
    
    bool startWebApp() {
        webAppActive = true;
        Serial.println("WebApp started on port 8080");
        return true;
    }
    
    bool stopWebApp() {
        webAppActive = false;
        Serial.println("WebApp stopped");
        return true;
    }
    
    bool enableRemoteAccess(String domain) {
        remoteAccessEnabled = true;
        Serial.println("Remote access enabled");
        if (domain.length() > 0) {
            Serial.println("Domain: " + domain);
        }
        return true;
    }
    
    bool disableRemoteAccess() {
        remoteAccessEnabled = false;
        Serial.println("Remote access disabled");
        return true;
    }
    
    bool isRemoteAccessEnabled() {
        return remoteAccessEnabled;
    }
    
    void initDatabase() {
        Serial.println("Database initialized (in-memory)");
        preferences.putUInt("log_count", 0);
    }
    
    bool logEvent(String source, String message, float value) {
        LogEntry entry;
        entry.timestamp = millis();
        entry.source = source;
        entry.message = message;
        entry.value = value;
        
        logBuffer.push_back(entry);
        
        // Store in preferences (limited)
        uint32_t count = preferences.getUInt("log_count", 0);
        preferences.putUInt("log_count", count + 1);
        preferences.putString("log_src_" + String(count), source);
        preferences.putString("log_msg_" + String(count), message);
        preferences.putFloat("log_val_" + String(count), value);
        preferences.putULong("log_ts_" + String(count), entry.timestamp);
        
        // Keep buffer size limited
        if (logBuffer.size() > LOG_BUFFER_SIZE) {
            logBuffer.erase(logBuffer.begin());
        }
        
        return true;
    }
    
    std::vector<LogEntry> getLogs(uint32_t since, uint32_t limit) {
        std::vector<LogEntry> result;
        uint32_t count = preferences.getUInt("log_count", 0);
        
        for (uint32_t i = 0; i < count && result.size() < limit; i++) {
            uint32_t index = count - 1 - i; // Most recent first
            uint32_t timestamp = preferences.getULong("log_ts_" + String(index), 0);
            
            if (timestamp > since) {
                LogEntry entry;
                entry.timestamp = timestamp;
                entry.source = preferences.getString("log_src_" + String(index), "");
                entry.message = preferences.getString("log_msg_" + String(index), "");
                entry.value = preferences.getFloat("log_val_" + String(index), 0.0);
                result.push_back(entry);
            }
        }
        
        return result;
    }
    
    bool syncLogsToCloud() {
        if (logBuffer.empty()) return true;
        
        Serial.println("Syncing " + String(logBuffer.size()) + " logs to cloud");
        // TODO: Implement cloud sync
        logBuffer.clear();
        return true;
    }
}
