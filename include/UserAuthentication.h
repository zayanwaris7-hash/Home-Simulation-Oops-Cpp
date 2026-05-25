#ifndef USER_AUTHENTICATION_H
#define USER_AUTHENTICATION_H

#include <iostream>
#include <string>

using namespace std;

class UserAuthentication
{
protected:
    string username;
    string password;
    string role; // "owner", "guest", or "admin"
    bool isLoggedIn;

public:
    // Default Constructor
    UserAuthentication() 
        : username("admin"), password("admin123"), role("admin"), isLoggedIn(false) {}

    // Parameterized Constructor
    UserAuthentication(string user, string pass, string r) 
        : username(user), password(pass), role(r), isLoggedIn(false) {}

    // --- Core Authentication Methods ---

    // Validates credentials and establishes a secure session
    bool login(const string& inputUser, const string& inputPass) {
        if (isLoggedIn) {
            cout << "[AUTH] User '" << username << "' is already logged in." << endl;
            return true;
        }

        if (inputUser == username && inputPass == password) {
            isLoggedIn = true;
            cout << "[SUCCESS] Login verified. Welcome back, " << username << " (" << role << ")." << endl;
            return true;
        }

        cout << "[ERROR] Invalid username or password entry." << endl;
        return false;
    }

    // Terminates the active session state safely
    void logout() {
        if (!isLoggedIn) {
            cout << "[AUTH] No active session found to terminate." << endl;
            return;
        }
        cout << "[SUCCESS] User '" << username << "' signed out safely." << endl;
        isLoggedIn = false;
    }

    // Checks if the active user possesses the required clearance level
    bool verifyRole(const string& requiredRole) const {
        if (!isLoggedIn) {
            cout << "[ERROR] Access Denied: Please log in to verify access rights." << endl;
            return false;
        }

        if (role == requiredRole || role == "admin") {
            return true; // Admins bypass checking blocks by default
        }

        return false;
    }

    // Spawns clean, temporary credential keys for visitors
    void grantGuestAccess(string& structuralGuestUser, string& structuralGuestPass) {
        if (!isLoggedIn) {
            cout << "[ERROR] Unauthorized: You must be logged in to provision guest slots." << endl;
            return;
        }

        if (role != "owner" && role != "admin") {
            cout << "[ERROR] Security Breach: Only Owners or Admins can grant guest passes." << endl;
            return;
        }

        // Generate temporary profile credentials
        structuralGuestUser = "Guest_User";
        structuralGuestPass = "GuestPass2026"; 
        
        cout << "[PROVISIONED] Temporary Guest account created successfully." << endl;
        cout << " -> Username: " << structuralGuestUser << endl;
        cout << " -> Password: " << structuralGuestPass << endl;
    }

    // Getters and Setters
    string getUsername() const { return username; }
    string getRole() const { return role; }
    bool getIsLoggedIn() const { return isLoggedIn; }

    void updatePassword(const string& oldPass, const string& newPass) {
        if (oldPass == password) {
            password = newPass;
            cout << "[SUCCESS] Security account update accepted." << endl;
        } else {
            cout << "[ERROR] Master key mismatch. Aborting pass reset." << endl;
        }
    }

    ~UserAuthentication() {}
};

#endif