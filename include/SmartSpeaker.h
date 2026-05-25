/*Inherits from SmartAppliance Attributes: volume, activeSkill, connectedServices.
Methods: playMusic(), setVolume(), triggerSkill().*/
#ifndef SMARTSPEAKER_H
#define SMARTSPEAKER_H
#include "SmartAppliance.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

class SmartSpeaker : public SmartAppliance
{
protected:
    int volume;
    string activeSkill;
    string connectedService;

public:
    SmartSpeaker() : volume(0), activeSkill(""), connectedService("") {}
    SmartSpeaker(string id, string name, string location, bool isOn, string firmWareVersion,
                 float power, string runMode, int vol, string skill, string service)
        : SmartAppliance(id, name, location, isOn, firmWareVersion, power, runMode),
          volume(vol), activeSkill(skill), connectedService(service) {}

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
    void AddInfo(string id) override
    {
        SmartAppliance::AddInfo(id);
        do
        {
            cout << "Enter Preferred Connected Service (Spotify|AppleMusic|Mymusic|Youtube|Bluetooth): ";
            cin >> connectedService;
            transform(connectedService.begin(), connectedService.end(), connectedService.begin(), ::tolower);
            if (!isPureString(connectedService) || !(connectedService == "spotify" || connectedService == "applemusic" || connectedService == "mymusic" || connectedService == "youtube" || connectedService == "bluetooth"))
                cout << "Invalid Input (must be Text)" << endl;

        } while (!(connectedService == "spotify" || connectedService == "applemusic" || connectedService == "mymusic" || connectedService == "youtube" || connectedService == "bluetooth"));
        int vol;
        do
        {
            cout << "Initialize Master Volume Level (0-100): ";
            cin >> vol;
            while (cin.fail() || cin.peek() == '.')
            {
                cout << "Invalid input! Please type a whole integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> vol;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (vol < 0 || vol > 100)
            {
                cout << "Error: Initial volume out of bounds." << endl
                     << endl;
            }
        } while (vol < 0 || vol > 100);
        volume = vol;
        activeSkill = "None";
        cout << ".";
        Sleep(1500);
        cout << ".";
        Sleep(1500);
        cout << ".";
        Sleep(1500);
        cout << endl;
        cout << "[SUCCESS] Smart Speaker properties added cleanly to system map." << endl;
    }
    void playMusic()
    {
        if (!isOn)
        {
            cout << "[ERROR] Cannot play audio. Speaker '" << name << "' is powered OFF." << endl;
            return;
        }
        runMode = "start";
        cout << "[AUDIO] Now streaming audio via | " << connectedService
             << " | on '" << name << "' at Volume: " << volume << "%." << endl;
    }
    void setVolume()
    {
        if (!isOn)
        {
            cout << "[ERROR] Cannot adjust volume. Speaker '" << name << "' is powered OFF." << endl;
            return;
        }
        int vol;
        do
        {
            cout << "Enter Speaker Volume (0 to 100): ";
            cin >> vol;
            while (cin.fail() || cin.peek() == '.')
            {
                cout << "Invalid input! Please enter a whole number from 0 to 100: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> vol;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (vol < 0 || vol > 100)
            {
                cout << "Error: Volume parameter must be strictly between 0% and 100% bounds." << endl
                     << endl;
            }
        } while (vol < 0 || vol > 100);

        volume = vol;
        cout << "[SUCCESS] Volume updated to: " << volume << "%" << endl;
    }
    void triggerSkill()
    {
        if (!isOn)
        {
            cout << "[ERROR] Voice assistant unresponsive. Speaker '" << name << "' is powered OFF." << endl;
            return;
        }
        cout << "Speak your command or voice action item: ";
        if (cin.peek() == '\n')
            cin.ignore();
        getline(cin, activeSkill);
        cout << "[ASSISTANT] Processing voice request... *Beep*" << endl;
        Sleep(1500);
        cout << "[ASSISTANT] Successfully executed skill: \"" << activeSkill << "\"" << endl;
    }
    ~SmartSpeaker() override {}
};
#endif