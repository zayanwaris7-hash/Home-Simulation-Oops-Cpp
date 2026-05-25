/*. 
EnergyLog Association (to SmartDevice) Attributes: logID, deviceReference, kilowattHours,
timestamp. Methods: recordUsage(),
getMonthlyReport(), compareToAverage().
*/
#ifndef ENERGY_LOG_H
#define ENERGY_LOG_H

#include "SmartDevice.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct EnergyEntry {
    double kwh;
    string timeLogged;
};

class EnergyLog
{
protected:
    string logID;
    SmartDevice* deviceReference;
    vector<EnergyEntry> history;

public:
    EnergyLog() : logID("LOG000"), deviceReference(NULL) {}

    EnergyLog(string id, SmartDevice* device) : logID(id), deviceReference(device) {}

    void recordUsage(double kwh, const string& timestamp) {
        if (deviceReference == NULL) {
            cout << "[ERROR] No device reference linked to this log instance." << endl;
            return;
        }
        if (kwh < 0.0) {
            cout << "[ERROR] Energy values cannot be negative numbers." << endl;
            return;
        }
        EnergyEntry entry;
        entry.kwh = kwh;
        entry.timeLogged = timestamp;
        history.push_back(entry);
        cout << "[LOGGED] Mapped " << kwh << " kWh to device '" 
             << deviceReference->getName() << "' on " << timestamp << endl;
    }
    void getMonthlyReport(const string& yearMonth) {
        if (deviceReference == NULL) return;
        double totalKWh = 0.0;
        int matchCount = 0;
        cout << "\n=========================================" << endl;
        cout << " ENERGY REPORT FOR TARGET PERIOD: " << yearMonth << endl;
        cout << " Device: " << deviceReference->getName() << " (ID: " << deviceReference->getId() << ")" << endl;
        cout << "=========================================" << endl;
        for (size_t i = 0; i < history.size(); ++i) {
            if (history[i].timeLogged.find(yearMonth) == 0) {
                cout << " -> " << history[i].timeLogged << " | Consumption: " << history[i].kwh << " kWh" << endl;
                totalKWh += history[i].kwh;
                matchCount++;
            }
        }
        if (matchCount == 0) {
            cout << " [INFO] No recorded data segments found for this month range." << endl;
        } else {
            cout << "-----------------------------------------" << endl;
            cout << " Cumulative Period Consumption: " << totalKWh << " kWh" << endl;
        }
        cout << "=========================================" << endl;
    }

    void compareToAverage(double regionalAverageKWh) {
        if (history.empty()) {
            cout << "[ERROR] Data log empty. Cannot compile tracking comparisons." << endl;
            return;
        }
        double aggregateSum = 0.0;
        for (size_t i = 0; i < history.size(); ++i) {
            aggregateSum += history[i].kwh;
        }
        double deviceAverage = aggregateSum / history.size();
        cout << "\n--- Consumption Analysis Node: " << logID << " ---" << endl;
        cout << "Device Running Average : " << deviceAverage << " kWh" << endl;
        cout << "Target Benchmark Range : " << regionalAverageKWh << " kWh" << endl;

        if (deviceAverage > regionalAverageKWh) {
            double variance = ((deviceAverage - regionalAverageKWh) / regionalAverageKWh) * 100.0;
            cout << "[WARNING] Consuming " << variance << "% MORE energy than baseline limits!" << endl;
        } else {
            double variance = ((regionalAverageKWh - deviceAverage) / regionalAverageKWh) * 100.0;
            cout << "[OPTIMAL] Saving " << variance << "% efficiency overhead vs typical baseline metrics." << endl;
        }
    }

    void setDeviceReference(SmartDevice* device) { deviceReference = device; }
    SmartDevice* getDeviceReference() const { return deviceReference; }
    string getLogID() const { return logID; }

    ~EnergyLog() {
        history.clear();
    }
};

#endif