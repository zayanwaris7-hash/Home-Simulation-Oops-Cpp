/*9. Automation Composition (links devices to rules)
Attributes: ruleID, triggerCondition, triggerTime, actionList. 
Methods: activate(), deactivate(), editRule(), evaluateTrigger(). 
*/

#ifndef AUTOMATION_H
#define AUTOMATION_H

#include "SmartDevice.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct AutomationAction {
    SmartDevice* targetDevice;
    string command;
};

class Automation
{
protected:
    string ruleID;
    string triggerCondition; 
    string triggerTime;      
    bool isActive;           
    vector<AutomationAction> actionList;

public:
    
    Automation() : ruleID("RULE000"), triggerCondition("None"), triggerTime("ANY"), isActive(false) {}

    
    Automation(string id, string condition, string time) 
    : ruleID(id), triggerCondition(condition), triggerTime(time), isActive(isActive) {}

    void activate() {
        isActive = true;
        cout << "[RULE ACTIVATED] Automation Rule '" << ruleID << "' is now actively monitoring." << endl;
    }

    void deactivate() {
        isActive = false;
        cout << "[RULE DEACTIVATED] Automation Rule '" << ruleID << "' has been suspended." << endl;
    }

    
    void addAction(SmartDevice* device, const string& cmd) {
        if (device == NULL) return;
        AutomationAction newAction;
        newAction.targetDevice = device;
        newAction.command = cmd;
        actionList.push_back(newAction);
    }

    
    void editRule() {
        cout << "\n========================================" << endl;
        cout << "       EDIT AUTOMATION RULE: " << ruleID << endl;
        cout << "========================================" << endl;
        
        cout << "Enter New Trigger Condition Phrase (e.g., Motion Detected): ";
        getline(cin, triggerCondition);
        
        cout << "Enter New Trigger Execution Time (e.g., 18:00 / ANY): ";
        cin >> triggerTime;
        cin.ignore(10000, '\n');

        cout << "[SUCCESS] Automation settings updated cleanly." << endl;
    }

    void evaluateTrigger(const string& currentEvent, const string& currentTime) {
        if (!isActive) return;

       if ((currentEvent == triggerCondition) && (triggerTime == "ANY" || currentTime == triggerTime)) {
            cout << "\n[ALERT] Automation Rule '" << ruleID << "' triggered by event: " << currentEvent << endl;
            
            for (size_t i = 0; i < actionList.size(); ++i) {
                SmartDevice* device = actionList[i].targetDevice;
                string cmd = actionList[i].command;

                if (device != NULL) {
                    cout << " -> Executing action on item: " << device->getName() << endl;
                    
                    if (cmd == "TURN_ON") {
                        if (device->getStatus() == "Device is OFF") device->toggle();
                    }
                    else if (cmd == "TURN_OFF") {
                        if (device->getStatus() != "Device is OFF") device->toggle();
                    }
                    else if (cmd == "RESTART") {
                        device->restart();
                    }
                    else {
                        cout << "    [WARNING] Command string syntax '" << cmd << "' not supported globally must be from :[TURN_ON|TURN_OFF|RESTART]." << endl;
                    }
                }
            }
        }
    }


    void displayRuleDetails() const {
        cout << "\n----------------------------------------" << endl;
        cout << "Automation Rule Profile ID: " << ruleID << endl;
        cout << "Status           : " << (isActive ? "ACTIVE" : "INACTIVE") << endl;
        cout << "Trigger Event    : " << triggerCondition << endl;
        cout << "Target Schedule  : " << triggerTime << endl;
        cout << "Linked Actions   : " << actionList.size() << " target device node mappings." << endl;
        cout << "----------------------------------------" << endl;
    }
    
    string getRuleID() const { return ruleID; }
    string getTriggerCondition() const { return triggerCondition; }
    string getTriggerTime() const { return triggerTime; }
    bool getIsActive() const { return isActive; }

    ~Automation() {
        actionList.clear(); // Clears relational vector links cleanly
    }
};

#endif