/*8. Room Aggregation (holds
List<SmartDevice>)
Attributes: roomID, roomName, floor,
List<SmartDevice>. Methods: addDevice(),
removeDevice(), turnAllOff(), getRoomStatus().
*/
#ifndef ROOM_H
#define ROOM_H

#include "SmartDevice.h"
#include "Thermostat.h"
#include "SecurityCamera.h"
#include "SmartSpeaker.h"
#include "SmartAppliance.h"
#include "SmartLigth.h"
#include "SmartLock.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
class Room
{
protected:
    string roomID;
    string roomName;
    string floor;
    vector<SmartDevice *> deviceList;
    vector<SmartAppliance *> ApplianceList;

public:
    Room() : roomID("RM000"), roomName("Default Room"), floor("ground") {}
    Room(string id, string name, string fl) : roomID(id), roomName(name), floor(fl) {}
    bool doesIdExistDeviceList(const string &targetID)
    {
        for (size_t i = 0; i < deviceList.size(); i++)
        {
            if (deviceList[i]->getId() == targetID)
            {
                return true;
            }
        }
        return false;
    }
    vector<SmartDevice *> getSmartDevice(){return  deviceList;}
    vector<SmartAppliance *> getSmartApp(){return  ApplianceList;}
    bool doesIdExistAppliancesList(const string &targetID)
    {
        for (size_t i = 0; i < ApplianceList.size(); i++)
        {
            if (ApplianceList[i]->getId() == targetID)
            {
                return true;
            }
        }
        return false;
    }
    void AppliancesMenu()
    {
        int choice = 0;
        cout << "\n========================================" << endl;
        cout << "   ADD SMART APPLIANCES TO ROOM: " << roomName << endl;
        cout << "========================================" << endl;
        cout << " 1. Smart Lock\n2. Smart Speaker\n3. Back " << endl;
        cout << "Choice (1-3): ";
        while (cin.fail() || choice < 1 || choice > 5)
        {
            cout << "Invalid selection! Enter 1-4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 3)
            addDevice();
        SmartAppliance *newDevice;
        if (choice == 1)
            newDevice = new SmartLock();
        else if (choice == 2)
            newDevice = new SmartSpeaker();
        if (newDevice != NULL)
        {
            string id;
            do
            {
                cout << "Enter Id Of Device Name : " << newDevice->getName() << " " << endl;
                cin >> id;
                if (doesIdExistAppliancesList(id))
                    cout << "Id Already Exsist ! Try Again!" << endl;
            } while (doesIdExistAppliancesList(id));
            newDevice->AddInfo(id);
            ApplianceList.push_back(newDevice);
            cout << "[SUCCESS] '" << newDevice->getName() << "' added to " << roomName << endl;
        }
    }
    void addDevice()
    {
        int choice = 0;
        cout << "\n========================================" << endl;
        cout << "   ADD DEVICE TO ROOM: " << roomName << endl;
        cout << "========================================" << endl;
        cout << "1. Thermostat\n2. Security Camera\n3. Smart Ligth\n4. Smart Appliances Menu\n5. Cancel" << endl;
        cout << "Choice (1-5): ";
        while (cin.fail() || choice < 1 || choice > 5)
        {
            cout << "Invalid selection! Enter 1-4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 5)
            return;
        string cleanID;
        while (true)
        {
            cout << "Enter a UNIQUE Device ID: ";
            cin >> cleanID;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (doesIdExistDeviceList(cleanID))
            {
                cout << "[ERROR] ID '" << cleanID << "' already exists in this room! Try again.\n"
                     << endl;
            }
            else
            {
                break;
            }
        }
        SmartDevice *newDevice;
        if (choice == 1)
            newDevice = new Thermostat();
        else if (choice == 2)
            newDevice = new SecurityCamera();
        else if (choice == 3)
            newDevice = new SmartLigth();
        else if (choice == 4){
            AppliancesMenu();return;}
        if (newDevice != NULL)
        {
            newDevice->AddInfo(cleanID);
            deviceList.push_back(newDevice);
            cout << "[SUCCESS] '" << newDevice->getName() << "' added to " << roomName << endl;
        }
    }
    void removeDevice(const string &targetID)
    {
        for (size_t i = 0; i < deviceList.size(); ++i)
        {
            if (deviceList[i]->getId() == targetID)
            {
                cout << "[REMOVED] Device '" << deviceList[i]->getName() << "' dropped from system." << endl;
                delete deviceList[i];
                deviceList.erase(deviceList.begin() + i);
                return;
            }
        }
        for (size_t i = 0; i < ApplianceList.size(); ++i)
        {
            if (ApplianceList[i]->getId() == targetID)
            {
                cout << "[REMOVED] Appliance '" << ApplianceList[i]->getName() << "' dropped from system." << endl;
                delete ApplianceList[i];
                ApplianceList.erase(ApplianceList.begin() + i);
                return;
            }
        }
        cout << "[ERROR] No connected hardware match found for ID: " << targetID << endl;
    }

    void turnAllOff()
    {
        cout << "\n[BROADCAST] Shutting down all infrastructure elements inside: " << roomName << endl;
        for (size_t i = 0; i < deviceList.size(); ++i)
        {
            if (deviceList[i]->getStatus() != "Device is OFF")
            {
                deviceList[i]->toggle();
            }
        }
        for (size_t i = 0; i < ApplianceList.size(); ++i)
        {
            if (ApplianceList[i]->getStatus() != "Device is OFF")
            {
                ApplianceList[i]->toggle();
            }
        }
        cout << "[COMPLETE] All room systems are now offline." << endl;
    }

    void getRoomStatus()
    {
        cout << "\n=========================================" << endl;
        cout << " ROOM INFRASTRUCTURE STATUS: " << roomName << " (Floor: " << floor << ")" << endl;
        cout << "=========================================" << endl;
        cout << " -> Core Hardware Tracked Array Nodes:" << endl;
        if (deviceList.empty()) cout << "    [No registered core devices]" << endl;
        for (size_t i = 0; i < deviceList.size(); ++i)
        {
            cout<<"------------[ "<<i+1<<" Device ]------------"<<endl;
            deviceList[i]->getReport();
            cout<<"--------------------------------------------"<<endl;
        }
        cout << "\n -> Dynamic Integrated Appliances Array:" << endl;
        if (ApplianceList.empty()) cout << "    [No registered appliance modules]" << endl;
        for (size_t i = 0; i < ApplianceList.size(); ++i)
        {
            cout<<"------------[ "<<i+1<<" Device ]------------"<<endl;
            ApplianceList[i]->getReport();
            cout<<"--------------------------------------------"<<endl;
        }
        cout << "=========================================" << endl;
    }
    string getRoomID() const { return roomID; }
    string getRoomName() const { return roomName; }
    string getFloor() const { return floor; }
    ~Room()
    {
        for (size_t i = 0; i < deviceList.size(); ++i) 
            delete deviceList[i];
        for (size_t i = 0; i < ApplianceList.size(); ++i) 
            delete ApplianceList[i];
            
        deviceList.clear();
        ApplianceList.clear();
    }
};
#endif