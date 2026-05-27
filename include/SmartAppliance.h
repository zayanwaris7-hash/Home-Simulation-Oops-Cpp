/*5. SmartAppliance Inherits from SmartDevice
(intermediate base)
Attributes: powerRating, runMode. Methods:
startCycle(), getPowerUsage().*/
/* Abstract base class. Attributes: deviceID, name,
location, isOn, firmwareVersion. Methods: toggle(),
getStatus(), restart(), generateReport(). */
#ifndef SMARTAPPLIANCE_H
#define SMARTAPPLIANCE_H
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cctype>
#include "SmartDevice.h"
using namespace std;
class SmartAppliance : public SmartDevice
{
protected:
    float powerRating;
    string runMode;

public:
    SmartAppliance() : powerRating(0.0), runMode("stop") {}
    SmartAppliance(string a, string b, string c, int d, string e, float f, string g)
        : SmartDevice(a, b, c, d, e), powerRating(f), runMode(g) {}
    void toggle() override
    {
        if (isOn)
        {
            isOn = false;
            runMode="stop";
            cout << "Name:" << name << " | is now Off." << endl;
        }
        else
        {
            isOn = true;
            runMode="start";
            cout << " Name:" << name << " | is now On." << endl;
        }
    }
    string getStatus()override
    {
        return isOn ? "Device is ON" : "Device is OFF";
    }
    void restart()override
    {
        if (isOn)
        {
            cout << "Restarting device: " << name << " (ID: " << deviceid << ")..." << endl;
            isOn = false;
            runMode= "stop";
            cout << "[STATUS] Power cut. Device is offline." << endl;
            Sleep(3000);
            isOn = true;
            cout << "[STATUS] Device booted back online." << endl;
            cout << "[STATUS] Brigthness is Restoring  : | power Rating :" << powerRating << " | Run Mode: " << runMode << " |." << endl;
        }else{
            cout<<"[STATUS] Device is currently Offline..."<<endl;
            cout<<"...."<<endl;
            cout<<"...."<<endl;
            Sleep(3000);
            runMode= "start";
            isOn=true;
            cout <<"[STATUS] Device booted back online." << endl;
        }
    }
    void getReport()override
    {
        string m=getStatus();
        cout << "-----Smart Ligth------" << endl;
        cout << "Id : " << deviceid << endl;
        cout << "Name : " << name << endl;
        cout << "Location : " << location << endl;
        cout << "Status : " << m << endl;
        cout << "FirWirmVersion : " << firmWareVersion << endl;
        cout << "Power Rating : " << powerRating << endl;
        cout << "Run Mode : " << runMode << endl;
    }
    void AddInfo(string a)override
    {
        deviceid=a;
        cout << endl;

        cout << "Enter Name of Smart Appliance : ";
        cin >> name;
        cout << endl;

        cout << "Enter Location of Smart Appliance : ";
        cin >> location;
        cout << endl;

        cout << "Enter FirmWare Version of Smart Appliance : ";
        cin >> firmWareVersion;
        cout << endl;
        while (true) 
        {
            cout << "Enter Power Rating (e.g., 1.2, 4.6): ";
            cin >> powerRating;
            
            if (cin.fail()) 
            {
                cout << "Invalid Input! Please enter a numeric float value." << endl;
                cin.clear();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } 
            else 
            {
               // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }
        do{
            cout<<"Enter Run Mode : ";
            cin>>runMode;
            transform(runMode.begin(), runMode.end(), runMode.begin(), ::tolower);
            if(!(runMode=="start" || runMode=="stop")) cout<<"Invalid Input (must be start|stop)"<<endl;
        }while(!(runMode=="start" || runMode=="stop"));
    }
    void startCycle() {
         cout<<"Name : "<<name<<" Location : "<<location<<"is starting..."<<endl;
         Sleep(3000);
         runMode="start";
         cout<<"[STATUS] Started"<<endl;
    }
    float getPowerUsage() { return powerRating;}
    ~SmartAppliance() override {}
};
#endif