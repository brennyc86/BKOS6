// BKOS6 User Interface
#pragma once

#include <Arduino.h>
#include <vector>

namespace UI {
    
    // Screen types
    enum class ScreenType {
        HOME,           // Exterior screen
        IO_STATUS,      // IO status screen
        IO_CONFIG,      // IO configuration
        WIFI_CONFIG,    // WiFi configuration
        OTA_UPDATE,     // OTA update screen
        SETTINGS        // System settings
    };
    
    // Widget types
    struct Widget {
        String id;
        uint16_t x, y, width, height;
        String label;
        bool visible;
        void (*draw)();
        void (*onTouch)(uint16_t x, uint16_t y);
    };
    
    // Initialize UI
    void init();
    
    // Update UI (call in loop)
    void update();
    
    // Screen management
    void showScreen(ScreenType screen);
    ScreenType getCurrentScreen();
    void drawScreen();
    
    // Home screen (exterior screen)
    void drawHomeScreen();
    void updateHomeScreen();
    
    // IO Status screen
    void drawIOStatusScreen();
    void updateIOStatusScreen();
    
    // IO Configuration screen
    void drawIOConfigScreen();
    void handleIOConfigTouch(uint16_t x, uint16_t y);
    
    // Widget management
    void addWidget(Widget widget);
    void removeWidget(String id);
    void updateWidget(String id, String label);
    
    // Touch handling
    void handleTouch(uint16_t x, uint16_t y);
    bool isTouched();
    void getTouchPoint(uint16_t &x, uint16_t &y);
}
