/*Attributes: brightness, colorTemperature, hexColor.
Methods: setBrightness(), setColor(),
dimToSunset().
toggle(),
getStatus(), restart(), generateReport().
*/
#ifndef SMART_LIGTH_H
#define SMART_LIGTH_H
#include "SmartDevice.h"
#include <iostream>
#include <limits>

#include <windows.h>

using namespace std;

class SmartLigth : public SmartDevice
{
protected:
   int brigthness;
   int colorTemperature;
   string hexColor;

public:
   SmartLigth(string a, string b, string c, bool d, string e, int f, int g, string h)
       : SmartDevice(a, b, c, d, e), brigthness(f), colorTemperature(g), hexColor(h) {}
   SmartLigth() {}
   void setBrigthness(int a)
   {
      brigthness = a;
      cout << "Brigthness is now " << a << " % ." << endl;
   }
   void setColor(int a)
   {
      colorTemperature = a;
      cout << "Color Temprature is now " << a << "  Kelvin ." << endl;
   }
   void dimToSunset()
   {
      brigthness = 50;
      cout << "Due to SunSet brigthness is Dim and now it is " << brigthness << " % .";
   }
   void toggle() override
   {
      if (isOn)
      {
         isOn = false;
         cout << "Smart Ligth | Name:" << name << " | is now Off." << endl;
      }
      else
      {
         isOn = true;
         cout << "Smart Ligth | Name:" << name << " | is now On." << endl;
      }
   }
   string getStatus() override
   {
      return isOn ? "Device is ON" : "Device is OFF";
   }
   void restart() override
   {
      if (isOn)
      {
         cout << "Restarting device: " << name << " (ID: " << deviceid << ")..." << endl;
         isOn = false;
         cout << "[STATUS] Power cut. Device is offline." << endl;
         Sleep(3000);
         isOn = true;
         cout << "[STATUS] Device booted back online." << endl;
         cout << "[STATUS] Brigthness is Restoring  : " << brigthness << " % ." << endl;
      }
      else
      {
         cout << "[STATUS] Device is currently Offline..." << endl;
         cout << "...." << endl;
         cout << "...." << endl;
         Sleep(3000);
         isOn = true;
         cout << "[STATUS] Device booted back online." << endl;
      }
   }
   void getReport() override
   {
      cout << "-----Smart Ligth------" << endl;
      cout << "Id : " << deviceid << endl;
      cout << "Name : " << name << endl;
      cout << "Location : " << location << endl;
      cout << "IsOn : " << (isOn ? "Yes" : "No") << endl;
      cout << "FirWirmVersion : " << firmWareVersion << endl;
      cout << "BrigthNess : " << brigthness << " % " << endl;
      cout << "Color Temprature : " << colorTemperature << " Kelvin " << endl;
      cout << "Hex Color value : " << hexColor << endl;
   }
   void AddInfo(string a) override
   {
      deviceid=a;
      cout << "Enter Name of Smart Light: ";
      cin >> name;
      cout << "Enter Location of Smart Light: ";
      cin >> location;
      cout << "Enter Firmware Version: ";
      cin >> firmWareVersion;
      int bInput;
      while (true)
      {
         cout << "Set Initial Brightness (0-100%): ";
         cin >> bInput;
         if (cin.fail() || bInput < 0 || bInput > 100)
         {
            cout << "Invalid entry. Please use a whole integer number between 0 and 100." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
         }
         else
         {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
         }
      }
      brigthness = bInput;

      // Color temperature processing loop
      int tempInput;
      while (true)
      {
         cout << "Set Color Temperature in Kelvin (1000K - 10000K): ";
         cin >> tempInput;
         if (cin.fail() || tempInput < 1000 || tempInput > 10000)
         {
            cout << "Invalid range selection. Normal operational scope limits run between 1000K and 10000K." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
         }
         else
         {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
         }
      }
      colorTemperature = tempInput;

      cout << "Enter Hex Color Value (e.g., #FF5733): ";
      cin >> hexColor;
      cout << "[SUCCESS] Lighting configuration parameters logged cleanly." << endl;
   }
   ~SmartLigth() override {}
};
#endif