/*Attributes: targetTemperature, currentTemperature,
mode (heat/cool/auto). Methods: setTemperature(),
changeMode(), schedule(), cancelSchedule().
Methods: toggle(),
getStatus(), restart(), generateReport(). */

#ifndef THERMOSTAT_H
#define THERMOSTAT_H
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cctype>
#include <limits>
#include "SmartDevice.h"
using namespace std;
bool isPureString(const string &input)
{
    if (input.empty())
        return false;

    // string::const_iterator acts exactly like a "for...in" pointer
    for (string::const_iterator it = input.begin(); it != input.end(); ++it)
    {
        char c = *it; // De-reference 'it' to get the actual character 'c'
        
        if (c == ' ')
            continue;
            
        if (!isalpha(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }
    return true;
}
class Shedulable
{
public:
    virtual void schedule() = 0;
    virtual void cancelschedule() = 0;
};
class Thermostat : public SmartDevice, public Shedulable
{
private:
    int targetTemp;
    int currentTemp;
    string mode;
    int d, m, y;

public:
    Thermostat() : targetTemp(0), currentTemp(0), mode("auto") {}
    Thermostat(string id, string name, string location, bool isOn, string firnwareVersion, int tt, int ct, string m, int day, int month, int year)
        : SmartDevice(id, name, location, isOn, firnwareVersion), targetTemp(tt), currentTemp(ct), mode(m), d(day), m(month), y(year) {}
    void setTemperature()
    {
        int ct, tt;
        do
        {
            cout << "Enter Current Temprature in Kelvin : ";
            cin >> ct;
            cout << endl;
            while (cin.fail() || cin.peek() == '.')
            {
                cout << "Invalid input! Please enter a pure whole integer (if in float like 288.90 write 300 [aproxmiate]): ";

                cin.clear();                                         // 1. Reset the cin error flags so it can read again
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 2. Clear the bad input from the buffer
                cin >> ct;                                           // 3. Try taking the input again
                cout << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Target Temprature in Kelvin : ";
            cin >> tt;
            cout << endl;
            while (cin.fail() || cin.peek() == '.')
            {
                cout << "Invalid input! Please enter a pure whole integer (if in float like 288.90 write 300 [aproxmiate]): ";

                cin.clear();                                         // 1. Reset the cin error flags so it can read again
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 2. Clear the bad input from the buffer
                cin >> tt;                                           // 3. Try taking the input again
                cout << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!(ct <= 400 && tt <= 400 && ct >= 0 && tt >= 0))
                cout << "Maximum Temp of Thermistor is 400 (above from 400 not capible) Or Minimum must be 1 " << endl;
        } while (!(ct <= 400 && tt <= 400 && ct >= 0 && tt >= 0));
        currentTemp = ct;
        targetTemp = tt;
        cout << "---Temprature set---" << endl;
        cout << "Current Temprature : " << currentTemp << endl;
        cout << "Target Temprature : " << targetTemp << endl;
    }

    void changeMode()
    {
        string m;
        do
        {
            do
            {
                cout << "Enter Mode U Want To Change (heat/cool/auto) : ";
                cin >> m;
                cout << endl;
                if (!isPureString(m))
                {
                    cout << "Invalid Input (Must Be In Text)" << endl;
                }
            } while (!isPureString(m));
            transform(m.begin(), m.end(), m.begin(), ::tolower);
            if (!(m == "heat" || m == "cool" || m == "auto"))
            {
                cout << "Invalid Input Mode Must Be in (heat/cool/auto)" << endl;
            }
        } while (!(m == "heat" || m == "cool" || m == "auto"));
        mode = m;
        cout << "Mode Set To | " << mode << " | " << endl;
    }

    void schedule()
    {
        int a, b, c;
        do
        {
            cout << "---Schedule Things---";
            cout << "Enter Day : ";
            cin >> a;
            while (cin.fail() || cin.peek() == '.')
            {
                cout << "Invalid input! Please enter a Number : ";

                cin.clear();                                         // 1. Reset the cin error flags so it can read again
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 2. Clear the bad input from the buffer
                cin >> a;                                            // 3. Try taking the input again
                cout << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            cout << "Enter Month : ";
            cin >> b;
            cout << endl;
            while (cin.fail() || cin.peek() == '.')
            {
                cout << "Invalid input! Please enter a Number : ";

                cin.clear();                                         // 1. Reset the cin error flags so it can read again
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 2. Clear the bad input from the buffer
                cin >> b;                                            // 3. Try taking the input again
                cout << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Year : ";
            cin >> c;
            cout << endl;
            while (cin.fail() || cin.peek() == '.')
            {
                cout << "Invalid input! Please enter a Number : ";

                cin.clear();                                         // 1. Reset the cin error flags so it can read again
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 2. Clear the bad input from the buffer
                cin >> c;                                            // 3. Try taking the input again
                cout << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!(a <= 30 && a >= 1 && b <= 12 && b >= 1 && c >= 2026 && c <= 3000))
                cout << "Invalid Input 1" << endl;
        } while (!(a <= 30 && a >= 1 && b <= 12 && b >= 1 && c >= 2026 && c <= 3000));
        d=a;m=b;y=c;
        cout<<"---Schedule Set---"<<endl;
        cout<<"Date: ( "<<d<<" / "<<m<<" / "<<y<<" ) "<<endl;
    }
    void toggle()override
    {
        if (isOn)
        {
            isOn = false;
            cout << "Thermostat | Name:" << name << " | is now Off." << endl;
        }
        else
        {
            isOn = true;
            cout << "Thermostat | Name:" << name << " | is now On." << endl;
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
            cout << "[STATUS] Power cut. Device is offline." << endl;
            Sleep(3000);
            isOn = true;
            cout << "[STATUS] Device booted back online." << endl;
            cout << "[STATUS] Current Temprature is Restoring  : " << currentTemp << " K ." << endl;
        }else{
            cout<<"[STATUS] Device is currently Offline..."<<endl;
            cout<<"...."<<endl;
            cout<<"...."<<endl;
            Sleep(3000);
            isOn=true;
            cout <<"[STATUS] Device booted back online." << endl;
        }
    }
    void getReport()override
    {
        cout << "-----ThermoStat------" << endl;
        cout << "Id : " << deviceid << endl;
        cout << "Name : " << name << endl;
        cout << "Location : " << location << endl;
        cout << "IsOn : " << (isOn ? "Yes" : "No") << endl;
        cout << "FirWirmVersion : " << firmWareVersion << endl;
        cout << "Current Temprature : " << currentTemp << endl;
        cout << "Target Temprature : " << targetTemp << endl;
    }

    void AddInfo(string a)override{
        deviceid=a;
        cout<<endl;
        
        cout<<"Enter Name of ThermoStat : ";
        cin>>name;
        cout<<endl;

        cout<<"Enter Location of ThermoStat : ";
        cin>>location;
        cout<<endl;

        cout<<"Enter FirmWare Version of ThermoStat : ";
        cin>>firmWareVersion;
        cout<<endl;

        int ct,tt;
          do
        {
            cout << "Enter Current Temprature in Kelvin : ";
            cin >> ct;
            cout << endl;
            while (cin.fail() || cin.peek() == '.')
            {
                cout << "Invalid input! Please enter a pure whole integer (if in float like 288.90 write 300 [aproxmiate]): ";

                cin.clear();                                         
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cin >> ct;                                           
                cout << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Target Temprature in Kelvin : ";
            cin >> tt;
            cout << endl;
            while (cin.fail() || cin.peek() == '.')
            {
                cout << "Invalid input! Please enter a pure whole integer (if in float like 288.90 write 300 [aproxmiate]): ";

                cin.clear();                                         // 1. Reset the cin error flags so it can read again
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 2. Clear the bad input from the buffer
                cin >> tt;                                           // 3. Try taking the input again
                cout << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!(ct <= 400 && tt <= 400 && ct >= 0 && tt >= 0))
                cout << "Maximum Temp of Thermistor is 400 (above from 400 not capible) Or Minimum must be 1 " << endl;
        } while (!(ct <= 400 && tt <= 400 && ct >= 0 && tt >= 0));
        currentTemp=ct;
        targetTemp=tt;
    }
     void cancelschedule(){
        char a;
        do{
        cout<<"Are U Sure U Want to Cancel Schedule : (Y/N): ";
        cin>>a;
        }while(!(a=='y'|| a=='Y' || a=='n'||a=='N'));
        if(a=='y'||a=='Y'){
            cout<<"Schedule is Canceled of Date : ( "<<d<<"/"<<m<<"/"<<y<<" )"<<endl;
        }else{
            cout<<"Schedule is Reseverd of Date : ( "<<d<<"/"<<m<<"/"<<y<<" )  [not canceled] "<<endl;

        }
     }
    ~Thermostat() override {}
};
#endif