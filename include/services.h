// BKOS6 Services
#pragma once

#include <Arduino.h>
#include <vector>

namespace Services {
    
    // Message service types
    enum class MessageService {
        SIGNAL,
        WHATSAPP,
        TELEGRAM,
        EMAIL
    };
    
    // Log entry
    struct LogEntry {
        uint32_t timestamp;
        String source;
        String message;
        float value;
    };
    
    // Initialize services
    void init();
    
    // Update services (call in loop)
    void update();
    
    // Messaging services
    bool sendMessage(MessageService service, String recipient, String message);
    bool sendSignal(String recipient, String message);
    bool sendWhatsApp(String recipient, String message);
    
    // Bluetooth services
    void initBluetooth();
    bool startBluetooth();
    bool stopBluetooth();
    bool sendBluetoothCommand(String command);
    bool isBluetoothConnected();
    
    // API services
    void initAPI();
    bool startAPIServer();
    bool stopAPIServer();
    String handleAPIRequest(String endpoint, String method, String body);
    
    // WebApp services
    void initWebApp();
    bool startWebApp();
    bool stopWebApp();
    
    // Remote access
    bool enableRemoteAccess(String domain = "");
    bool disableRemoteAccess();
    bool isRemoteAccessEnabled();
    
    // Database logging
    void initDatabase();
    bool logEvent(String source, String message, float value = 0.0);
    std::vector<LogEntry> getLogs(uint32_t since = 0, uint32_t limit = 100);
    bool syncLogsToCloud();
}
