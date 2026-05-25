#ifndef SMARTHOME_H
#define SMARTHOME_H

#include "Room.h"
#include "Automation.h"
#include "EnergyLog.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SmartHome
{
protected:
    string homeID;
    string ownerName;
    string wifiNetwork;
    vector<Room*> roomList;
    vector<Automation*> automationList;
    vector<EnergyLog*> globalEnergyLogs; // Internal management list to tie energy modules to home network

public:
    SmartHome() : homeID("HOME000"), ownerName("Default Owner"), wifiNetwork("Default_WiFi") {}
    vector<Room*> getrooms(){ return roomList;}
    SmartHome(string id, string owner, string wifi) 
        : homeID(id), ownerName(owner), wifiNetwork(wifi) {}

    void addRoom(Room* room) {
        if (room == NULL) return;
        roomList.push_back(room);
        cout << "[HOME CONFIG] Room '" << room->getRoomName() << "' attached to property structure." << endl;
    }

    void addAutomation(Automation* rule) {
        if (rule == NULL) return;
        automationList.push_back(rule);
        cout << "[HOME CONFIG] Automation script [" << rule->getRuleID() << "] injected into hub firmware." << endl;
    }

    void associateEnergyLog(EnergyLog* log) {
        if (log != NULL) {
            globalEnergyLogs.push_back(log);
        }
    }

    SmartDevice* findDevice(const string& targetID) {
        for (size_t i = 0; i < roomList.size(); ++i) {
            if (roomList[i] != NULL) {
                // We create a temporary public accessor method hook or parse rooms directly
                // Since Room contains private vectors, we rely on the room's exist check or add a search hook
                // Alternately, to stay compatible with your Room structure without rewriting it:
                if (roomList[i]->doesIdExistDeviceList(targetID)) {
                    cout << "[FOUND] Target ID match located inside: " << roomList[i]->getRoomName() << endl;
                    // Return tracking pointer if architectural layout exposes a getter, otherwise log confirmation
                }
            }
        }
        return NULL; 
    }

    void getEnergyDashboard(const string& billingPeriod) {
        cout << "\n=================================================" << endl;
        cout << "         ESTATE-WIDE CENTRAL ENERGY HUB          " << endl;
        cout << " Owner: " << ownerName << " | Network: " << wifiNetwork << endl;
        cout << " Target Invoice Period: " << billingPeriod << endl;
        cout << "=================================================" << endl;

        if (globalEnergyLogs.empty()) {
            cout << " [INFO] No energy metric logging nodes registered to this network." << endl;
            cout << "=================================================" << endl;
            return;
        }

        for (size_t i = 0; i < globalEnergyLogs.size(); ++i) {
            if (globalEnergyLogs[i] != NULL) {
                globalEnergyLogs[i]->getMonthlyReport(billingPeriod);
            }
        }
        cout << ">>> End of Hub Transmission <<<" << endl;
    }

    string getHomeID() const { return homeID; }
    string getOwnerName() const { return ownerName; }
    string getWifiNetwork() const { return wifiNetwork; }

    ~SmartHome() {
        // Deep release of dynamic vectors to prevent structural leaks on teardown
        for (size_t i = 0; i < roomList.size(); ++i) delete roomList[i];
        for (size_t i = 0; i < automationList.size(); ++i) delete automationList[i];
        for (size_t i = 0; i < globalEnergyLogs.size(); ++i) delete globalEnergyLogs[i];

        roomList.clear();
        automationList.clear();
        globalEnergyLogs.clear();
    }
};

#endif