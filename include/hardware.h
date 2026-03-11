// BKOS6 Hardware Abstraction Layer
#pragma once

#include <Arduino.h>

namespace Hardware {
    
    // Display configuration
    struct DisplayConfig {
        uint16_t width = 800;
        uint16_t height = 480;
        uint8_t rotation = 0; // 0=landscape, 2=180°
        uint8_t brightness = 100;
        bool backlightOn = true;
    };
    
    // IO Port configuration
    struct IOPort {
        uint8_t pin;
        String name;
        String type; // "input", "output", "sensor"
        bool state;
        bool unused;
        float value; // For sensors
    };
    
    // Initialize hardware
    void init();
    
    // Display functions
    void initDisplay();
    void setDisplayRotation(uint8_t rotation);
    void setBrightness(uint8_t percent);
    DisplayConfig getDisplayConfig();
    
    // IO functions
    void initIO();
    std::vector<IOPort> getIOPorts();
    bool configureIOPort(uint8_t pin, String name, String type);
    bool setIOPortState(uint8_t pin, bool state);
    bool getIOPortState(uint8_t pin);
    
    // Sensor functions
    void initSensors();
    float readSensor(uint8_t pin);
    void setSensorTrigger(uint8_t pin, bool rising, bool falling, void (*callback)(uint8_t, bool));
    
    // System functions
    void reboot();
    void deepSleep(uint32_t seconds);
}
