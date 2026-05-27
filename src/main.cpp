#include "Home.h"
#include "Automation.h"
#include "EnergyLog.h"
#include "UserAuthentication.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>



using namespace std;

void clearInputStream()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

bool isDuplicate(string rID, vector<Room *> r)
{
    for (size_t i = 0; i < r.size(); i++)
    {
        if (r[i]->getRoomID() == rID)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    UserAuthentication authSystem("admin", "password123", "owner");
    SmartHome myHome("H-2026", "User Hub", "Home_WiFi_Secure");

    Room *lounge = new Room("RM01", "Lounge", "1st Floor");
    Room *kitchen = new Room("RM02", "Kitchen", "Ground Floor");
    myHome.addRoom(lounge);
    myHome.addRoom(kitchen);

    cout << "=================================================" << endl;
    cout << "      WELCOME TO THE NEXUS SMART HOME HUB        " << endl;
    cout << "=================================================" << endl;

    string userIn, passIn;
    bool loggedIn = false;

    while (!loggedIn)
    {
        cout << "\n--- SECURITY VERIFICATION REQUIRED ---" << endl;
        cout << "Enter Username: ";
        cin >> userIn;
        cout << "Enter Password: ";
        cin >> passIn;

        if (authSystem.login(userIn, passIn))
        {
            loggedIn = true;
        }
        else
        {
            cout << "[REJECTED] Access denied. Try again." << endl;
        }
    }

    int mainChoice = 0;
    while (mainChoice != 7)
    {
        cout << "\n=========================================" << endl;
        cout << "               MAIN MENU                 " << endl;
        cout << "=========================================" << endl;
        cout << "1. Manage Rooms & Hardware Devices" << endl;
        cout << "2. Create and Register a New Room" << endl;
        cout << "3. Broadcast Command: Turn All Devices OFF" << endl;
        cout << "4. Open Central Energy Dashboard" << endl;
        cout << "5. Add Manual Energy Log Entry" << endl;
        cout << "6. Security: Provision Guest Access Keys" << endl;
        cout << "7. Shut Down System Hub & Exit" << endl;
        cout << "=========================================" << endl;
        cout << "Select Option (1-7): ";
        cin >> mainChoice;

        if (cin.fail() || mainChoice < 1 || mainChoice > 7)
        {
            cout << "[ERROR] Invalid selection string. Choose 1 to 7." << endl;
            clearInputStream();
            continue;
        }

        switch (mainChoice)
        {
        case 1:
        {
            int roomIdx = -1;
            vector<Room *> room = myHome.getrooms();
            cout << "\n--- CHOOSE A ROOM TO OPERATE ---" << endl;
            cout << "0. Cancel / Go Back" << endl;
            for (size_t i = 0; i < room.size(); i++)
            {
                cout << i + 1 << ". " << room[i]->getRoomName() << " [" << room[i]->getRoomID() << "] ." << endl;
            }
            cout << "Select Target Room Code: ";
            cin >> roomIdx;

            if (cin.fail() || roomIdx < 0 || roomIdx > static_cast<int>(room.size()))
            {
                cout << "[ERROR] Invalid room array bound scope." << endl;
                clearInputStream();
                break;
            }
            if (roomIdx == 0)
                break;
            Room *activeRoom = room[roomIdx - 1];

            int roomAction = 0;
            while (roomAction != 4)
            {
                cout << "\n--- MANAGING ROOM: " << activeRoom->getRoomName() << " ---" << endl;
                cout << "0. Select A Specific Device For Setting " << endl;
                cout << "1. Add a New Smart Device or Appliance Module" << endl;
                cout << "2. Remove a Device via Unique Track ID" << endl;
                cout << "3. Display Live Room Status Report Matrix" << endl;
                cout << "4. Back to Central Main Menu" << endl;
                cout << "Choice (0-4): ";
                cin >> roomAction;

                if (cin.fail() || roomAction < 0 || roomAction > 4)
                {
                    cout << "[ERROR] Please specify an action option from 0 to 4." << endl;
                    clearInputStream();
                    continue;
                }
                
                if (roomAction == 0)
                {
                    int choice = -1;
                    do
                    {
                        vector<SmartDevice *> D = activeRoom->getSmartDevice();
                        vector<SmartAppliance *> A = activeRoom->getSmartApp();
                        
                        cout << "\n--- SELECT DEVICE SUB-CATEGORY ---" << endl;
                        cout << "0. Go back" << endl;
                        cout << "1. Smart Devices" << endl;
                        cout << "2. Smart Appliances" << endl;
                        cout << "Select (0-2): ";
                        cin >> choice;
                        
                        if (cin.fail() || choice < 0 || choice > 2)
                        {
                            cout << "[ERROR] Invalid choice index scope." << endl;
                            clearInputStream();
                            continue;
                        }

                        if (choice == 1)
                        {
                            int idx = -1;
                            do
                            {
                                cout << "\n=======( Present Smart Devices In [ " << activeRoom->getRoomName() << " ] )=======" << endl;
                                if (D.empty())
                                {
                                    cout << "NO Devices Present Yet!" << endl;
                                    break;
                                }
                                cout << "0. Go Back." << endl;
                                for (size_t i = 0; i < D.size(); i++)
                                {
                                    cout << " " << i + 1 << ". " << D[i]->getName() << endl;
                                }
                                cout << "Select Device Index: ";
                                cin >> idx;
                                
                                if (cin.fail() || idx < 0 || idx > static_cast<int>(D.size()))
                                {
                                    cout << "[ERROR] Invalid device sequence bounding index." << endl;
                                    clearInputStream();
                                    continue;
                                }
                                if (idx == 0) break;

                                int c = -1;
                                do
                                {
                                    cout << "\n=======( " << D[idx - 1]->getName() << " )=======" << endl;
                                    cout << "1. Toggle\n2. Restart\n3. Get Status\n4. Get Report\n5. Go Back" << endl;
                                    cout << "Choice (1-5): ";
                                    cin >> c;
                                    
                                    if (cin.fail() || c < 1 || c > 5)
                                    {
                                        cout << "[ERROR] Range mismatch. Select 1 to 5." << endl;
                                        clearInputStream();
                                        continue;
                                    }

                                    if (c == 1) D[idx - 1]->toggle();
                                    else if (c == 2) D[idx - 1]->restart();
                                    else if (c == 3) D[idx - 1]->getStatus();
                                    else if (c == 4) D[idx - 1]->getReport();

                                } while (c != 5);

                            } while (idx != 0);
                        }

                        if (choice == 2)
                        {
                            int idx = -1;
                            do
                            {
                                cout << "\n=======( Present Smart Appliances In [ " << activeRoom->getRoomName() << " ] )=======" << endl;
                                if (A.empty())
                                {
                                    cout << "NO Appliances Present Yet!" << endl;
                                    break;
                                }
                                cout << "0. Go Back." << endl;
                                for (size_t i = 0; i < A.size(); i++)
                                {
                                    cout << " " << i + 1 << ". " << A[i]->getName() << endl;
                                }
                                cout << "Select Appliance Index: ";
                                cin >> idx;
                                
                                if (cin.fail() || idx < 0 || idx > static_cast<int>(A.size()))
                                {
                                    cout << "[ERROR] Invalid appliance bounding layout scope." << endl;
                                    clearInputStream();
                                    continue;
                                }
                                if (idx == 0) break;

                                int c = -1;
                                do
                                {
                                    cout << "\n=======( " << A[idx - 1]->getName() << " )=======" << endl;
                                    cout << "1. Toggle\n2. Restart\n3. Get Status\n4. Get Report\n5. Start Cycle\n6. Go Back" << endl;
                                    cout << "Choice (1-6): ";
                                    cin >> c;
                                    
                                    if (cin.fail() || c < 1 || c > 6)
                                    {
                                        cout << "[ERROR] Range mismatch. Select 1 to 6." << endl;
                                        clearInputStream();
                                        continue;
                                    }

                                    if (c == 1) A[idx - 1]->toggle();
                                    else if (c == 2) A[idx - 1]->restart();
                                    else if (c == 3) {
                                       string msg= A[idx - 1]->getStatus();
                                       cout<<"[STATUS] "<<msg<<endl;

                                    }
                                    else if (c == 4) A[idx - 1]->getReport();
                                    else if (c == 5) A[idx - 1]->startCycle();

                                } while (c != 6);

                            } while (idx != 0);
                        }

                    } while (choice != 0);
                }
                else if (roomAction == 1)
                {

                    activeRoom->Room::addDevice();
                    break; 
                }
                else if (roomAction == 2)
                {
                    string targetID;
                    cout << "Enter the exact tracking ID to strip out: ";
                    cin >> targetID;
                    activeRoom->removeDevice(targetID);
                    break; 
                }
                else if (roomAction == 3)
                {
                    activeRoom->getRoomStatus();
                    break; 
                }
            }
            break;
        }

        case 2:
        {
            string rID, rName, rFloor;
            do
            {
                cout << "\n--- REGISTER NEW ARCHITECTURAL ROOM NODE ---" << endl;
                cout << "Enter Room Unique ID (e.g., RM03): ";
                cin >> rID;
                if (isDuplicate(rID, myHome.getrooms()))
                    cout << "Room With This Id Already Exists! (Try Another One)" << endl;
            } while (isDuplicate(rID, myHome.getrooms()));
            
            clearInputStream(); 
            cout << "Enter Descriptive Name (e.g., Master Bedroom): ";
            getline(cin, rName);
            cout << "Enter Floor Plane Placement (e.g., 2nd Floor): ";
            getline(cin, rFloor);

            Room *userRoom = new Room(rID, rName, rFloor);
            myHome.addRoom(userRoom);
            cout << "[SUCCESS] Room successfully tied into memory management vectors." << endl;
            break;
        }

        case 3:
        {
            cout << "\n[BROADCAST] Pushing global safety override framework..." << endl;
            vector<Room *> rooms = myHome.getrooms();
            for (size_t i = 0; i < rooms.size(); i++)
            {
                if (rooms[i] != NULL)
                {
                    rooms[i]->turnAllOff();
                }
            }
            cout << "[SUCCESS] Broadcast command executed for all active rooms." << endl;
            break;
        }

        case 4:
        {
            string bPeriod;
            cout << "\nEnter target billing reference filter string (e.g., 2026-05): ";
            cin >> bPeriod;
            myHome.getEnergyDashboard(bPeriod);
            break;
        }

        case 5:
        {
            double kwhValue;
            string dateStamp;
            cout << "\n--- MANUAL METRIC TELEMETRY LOG INJECTION ---" << endl;
            cout << "Kilowatt Hours Consumed (double): ";
            cin >> kwhValue;
            cout << "Timestamp String Entry (YYYY-MM-DD): ";
            cin >> dateStamp;

            EnergyLog *customLog = new EnergyLog("LOG-MANUAL", NULL);
            customLog->recordUsage(kwhValue, dateStamp);
            myHome.associateEnergyLog(customLog);
            break;
        }

        case 6:
        {
            string gUser, gPass;
            cout << "\n[PRIVILEGE PROVISIONING] Calling User Authentication system..." << endl;
            authSystem.grantGuestAccess(gUser, gPass);
            break;
        }

        case 7:
        {
            cout << "\n[DE-INITIALIZATION] Logging user account out of active frame profile..." << endl;
            authSystem.logout();
            break;
        }
        }
    }

    cout << "\n=================================================" << endl;
    cout << "     HUB TERMINATED: MEMORY STRUCTS FLUSHED      " << endl;
    cout << "=================================================" << endl;
    return 0;
}