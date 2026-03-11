// BKOS6 UI Implementation
#include "../../include/ui.h"
#include "../../include/hardware.h"
#include <TFT_eSPI.h>
#include <vector>

extern TFT_eSPI tft; // From hardware.cpp

namespace UI {
    
    // Current screen
    ScreenType currentScreen = ScreenType::HOME;
    std::vector<Widget> widgets;
    
    void init() {
        Serial.println("UI::init()");
        
        // Clear screen
        tft.fillScreen(TFT_BLACK);
        
        // Draw initial screen
        drawScreen();
        
        Serial.println("UI initialized");
    }
    
    void update() {
        // Handle touch input
        static uint16_t lastTouchX = 0, lastTouchY = 0;
        static unsigned long lastTouchTime = 0;
        
        // TODO: Implement touch reading
        // For now, update screen periodically
        static unsigned long lastUpdate = 0;
        if (millis() - lastUpdate > 1000) {
            drawScreen();
            lastUpdate = millis();
        }
    }
    
    void showScreen(ScreenType screen) {
        currentScreen = screen;
        drawScreen();
    }
    
    ScreenType getCurrentScreen() {
        return currentScreen;
    }
    
    void drawScreen() {
        tft.fillScreen(TFT_BLACK);
        
        switch(currentScreen) {
            case ScreenType::HOME:
                drawHomeScreen();
                break;
            case ScreenType::IO_STATUS:
                drawIOStatusScreen();
                break;
            case ScreenType::IO_CONFIG:
                drawIOConfigScreen();
                break;
            default:
                drawHomeScreen();
                break;
        }
        
        // Draw widgets
        for (const auto& widget : widgets) {
            if (widget.visible && widget.draw) {
                widget.draw();
            }
        }
    }
    
    void drawHomeScreen() {
        // Draw exterior screen
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(2);
        tft.setCursor(10, 10);
        tft.println("BKOS6 - Exterior Screen");
        
        // Draw boat representation
        tft.setTextSize(1);
        tft.setCursor(10, 50);
        tft.println("Boat Control System");
        tft.setCursor(10, 70);
        tft.println("Version: 1.0.0-alpha");
        
        // Draw status indicators
        tft.fillRect(10, 100, 20, 20, TFT_GREEN);
        tft.setCursor(35, 105);
        tft.println("System OK");
        
        tft.fillRect(10, 130, 20, 20, TFT_BLUE);
        tft.setCursor(35, 135);
        tft.println("WiFi Connected");
        
        // Draw navigation buttons
        tft.fillRect(600, 400, 180, 60, TFT_DARKGREEN);
        tft.setTextColor(TFT_WHITE);
        tft.setTextSize(2);
        tft.setCursor(620, 420);
        tft.println("IO Status >>");
    }
    
    void drawIOStatusScreen() {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(2);
        tft.setCursor(10, 10);
        tft.println("IO Status Screen");
        
        // Draw IO port status
        tft.setTextSize(1);
        auto ports = Hardware::getIOPorts();
        
        uint16_t y = 50;
        for (const auto& port : ports) {
            if (!port.unused) {
                tft.setCursor(10, y);
                tft.print("GPIO"); tft.print(port.pin);
                tft.print(": "); tft.print(port.name);
                tft.print(" (");

                tft.print(port.type);
                tft.print(") - ");
                tft.print(port.state ? "ON" : "OFF");
                
                if (port.type == "sensor") {
                    tft.print(" "); tft.print(port.value); tft.print("V");
                }
                
                y += 20;
                if (y > 400) break;
            }
        }
        
        // Navigation back
        tft.fillRect(600, 400, 180, 60, TFT_DARKGREEN);
        tft.setTextColor(TFT_WHITE);
        tft.setTextSize(2);
        tft.setCursor(620, 420);
        tft.println("<< Home");
    }
    
    void drawIOConfigScreen() {
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(2);
        tft.setCursor(10, 10);
        tft.println("IO Configuration");
        
        // TODO: Implement IO configuration UI
        tft.setTextSize(1);
        tft.setCursor(10, 50);
        tft.println("Drag and drop IO configuration");
        tft.setCursor(10, 70);
        tft.println("(Placeholder - to be implemented)");
        
        // Navigation
        tft.fillRect(600, 400, 180, 60, TFT_DARKGREEN);
        tft.setTextColor(TFT_WHITE);
        tft.setTextSize(2);
        tft.setCursor(620, 420);
        tft.println("Back");
    }
    
    void handleIOConfigTouch(uint16_t x, uint16_t y) {
        // TODO: Implement touch handling for IO config
    }
    
    void addWidget(Widget widget) {
        widgets.push_back(widget);
    }
    
    void removeWidget(String id) {
        for (size_t i = 0; i < widgets.size(); i++) {
            if (widgets[i].id == id) {
                widgets.erase(widgets.begin() + i);
                break;
            }
        }
    }
    
    void updateWidget(String id, String label) {
        for (auto& widget : widgets) {
            if (widget.id == id) {
                widget.label = label;
                break;
            }
        }
    }
    
    void handleTouch(uint16_t x, uint16_t y) {
        // Handle screen navigation
        if (currentScreen == ScreenType::HOME && x >= 600 && x <= 780 && y >= 400 && y <= 460) {
            showScreen(ScreenType::IO_STATUS);
        } else if (currentScreen == ScreenType::IO_STATUS && x >= 600 && x <= 780 && y >= 400 && y <= 460) {
            showScreen(ScreenType::HOME);
        } else if (currentScreen == ScreenType::IO_CONFIG && x >= 600 && x <= 780 && y >= 400 && y <= 460) {
            showScreen(ScreenType::IO_STATUS);
        }
        
        // Handle widget touches
        for (const auto& widget : widgets) {
            if (widget.visible && widget.onTouch && 
                x >= widget.x && x <= widget.x + widget.width &&
                y >= widget.y && y <= widget.y + widget.height) {
                widget.onTouch(x, y);
            }
        }
    }
    
    bool isTouched() {
        // TODO: Implement touch detection
        return false;
    }
    
    void getTouchPoint(uint16_t &x, uint16_t &y) {
        x = 0; y = 0;
        // TODO: Implement touch point reading
    }
}
