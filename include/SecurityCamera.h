/*4. SecurityCamera Inherits from SmartDevice Attributes: resolution, isRecording,
motionSensitivity, angle. Methods: startRecording(),
captureSnapshot(), setMotionAlert(). 
Methods from SmartDevice: toggle(), getStatus(), restart(), generateReport() */

#ifndef SECURITYCAMERA_H
#define SECURITYCAMERA_H

#include "SmartDevice.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

class SecurityCamera : public SmartDevice {
protected:
    string resolution;
    bool isRecording;
    string motionSensitivity; 
    int angle;              

public:
    
    SecurityCamera() 
        : SmartDevice(), resolution("1080p"), isRecording(false), motionSensitivity("medium"), angle(180) {}

    
    SecurityCamera(string id, string name, string location, bool isOn, string firmWareVersion, 
                   string res, bool rec, string sensitivity, int ang)
        : SmartDevice(id, name, location, isOn, firmWareVersion), 
          resolution(res), isRecording(rec), motionSensitivity(sensitivity), angle(ang) {}
    

    void startRecording() {
        if (!isOn) {
            cout << "[ERROR] Cannot record. Camera '" << name << "' is powered OFF." << endl;
            return;
        }
        
        if (isRecording) {
            cout << "[INFO] Camera '" << name << "' is already recording." << endl;
        } else {
            isRecording = true;
            cout << "[STATUS] Camera '" << name << "' has started recording video in " << resolution << "." << endl;
        }
    }

    void captureSnapshot() {
        if (!isOn) {
            cout << "[ERROR] Cannot capture snapshot. Camera '" << name << "' is powered OFF." << endl;
            return;
        }
        
        cout << "[CAMERA] *Click!* Snapshot saved successfully from '" << name << "' [" << resolution << "]." << endl;
    }

    void setMotionAlert() {
        if (!isOn) {
            cout << "[ERROR] Cannot configure alerts. Camera '" << name << "' is powered OFF." << endl;
            return;
        }

        string sensitivity;
        do {
            cout << "Enter Motion Sensitivity level (low / medium / high): ";
            cin >> sensitivity;
            
            transform(sensitivity.begin(), sensitivity.end(), sensitivity.begin(), ::tolower);

            if (!(sensitivity == "low" || sensitivity == "medium" || sensitivity == "high")) {
                cout << "Invalid input! Please type 'low', 'medium', or 'high'." << endl << endl;
            }
        } while (!(sensitivity == "low" || sensitivity == "medium" || sensitivity == "high"));

        motionSensitivity = sensitivity;
        cout << "[SUCCESS] Motion alerts activated. Sensitivity set to: | " << motionSensitivity << " |" << endl;
    }


    void toggle() override {
        if (isOn) {
            isOn = false;
            isRecording = false; 
            cout << "Security Camera | Name: " << name << " | is now Off." << endl;
        } else {
            isOn = true;
            cout << "Security Camera | Name: " << name << " | is now On." << endl;
        }
    }

    string getStatus() override {
        if (!isOn) return "Device is OFF";
        return isRecording ? "Device is ON [RECORDING]" : "Device is ON [STANDBY]";
    }

    void restart() override {
        cout << "Restarting Security Camera: " << name << " (ID: " << deviceid << ")..." << endl;
        bool wasRecording = isRecording;
        
        isOn = false;
        isRecording = false;
        cout << "[STATUS] Power cycle applied. Disconnected." << endl;
        Sleep(3000);
        
        isOn = true;
        cout << "[STATUS] System rebooted successfully." << endl;
        
        if (wasRecording) {
            isRecording = true;
            cout << "[STATUS] Automatically resuming video stream recording loop..." << endl;
        }
    }

    void getReport() override {
        cout << "----- Security Camera Report -----" << endl;
        cout << "ID                : " << deviceid << endl;
        cout << "Name              : " << name << endl;
        cout << "Location          : " << location << endl;
        cout << "Power State       : " << (isOn ? "ON" : "OFF") << endl;
        cout << "Firmware Version  : " << firmWareVersion << endl;
        cout << "Resolution        : " << resolution << endl;
        cout << "Recording Status  : " << (isRecording ? "ACTIVE" : "STOPPED") << endl;
        cout << "Motion Alert Level: " << motionSensitivity << endl;
        cout << "Lens View Angle   : " << angle << "°" << endl;
        cout << "----------------------------------" << endl;
    }

    void AddInfo(string a)override {
        deviceid=a;
        cout << "Enter Name of Security Camera: ";
        cin >> name;
        cout << "Enter Location of Security Camera: ";
        cin >> location;
        cout << "Enter Firmware Version: ";
        cin >> firmWareVersion;
        
        cout << "Enter Resolution (e.g., 1080p, 2K, 4K): ";
        cin >> resolution;
        int ang;
        do {
            cout << "Enter Lens Viewing Angle (0 to 360 degrees): ";
            cin >> ang;

            // Pure integer stream validation state check
            while (cin.fail() || cin.peek() == '.') {
                cout << "Invalid input! Please enter a whole degree number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> ang;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (ang < 0 || ang > 360) {
                cout << "Error: Camera physical lens boundary cannot exceed 0° - 360° scope." << endl << endl;
            }
        } while (ang < 0 || ang > 360);

        angle = ang;
        isRecording = false; 
        setMotionAlert();    
    }

    ~SecurityCamera() override {}
};

#endif