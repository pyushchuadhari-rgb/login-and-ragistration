#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class UserSystem {
private:
    string username, password;

public:

    bool isValidPassword(string pass) {
        if (pass.length() < 6) return false;

        bool hasUpper = false, hasLower = false, hasDigit = false;

        for (char c : pass) {
            if (isupper(c)) hasUpper = true;
            if (islower(c)) hasLower = true;
            if (isdigit(c)) hasDigit = true;
        }

        return hasUpper && hasLower && hasDigit;
    }

    void registerUser() {
        cout << "\n===== REGISTRATION =====\n";

        cout << "Enter username: ";
        cin >> username;

        if (username.length() < 3) {
            cout << "Username must be at least 3 characters!\n";
            return;
        }

        cout << "Enter password (min 6 char, 1 Upper, 1 Lower, 1 Digit): ";
        cin >> password;

        if (!isValidPassword(password)) {
            cout << "Weak password! Try again.\n";
            return;
        }

        // check if user already exists
        ifstream checkFile("users.txt");
        string u, p;
        while (checkFile >> u >> p) {
            if (u == username) {
                cout << "Username already exists!\n";
                checkFile.close();
                return;
            }
        }
        checkFile.close();

        ofstream file("users.txt", ios::app);
        file << username << " " << password << endl;
        file.close();

        cout << "Registration Successful!\n";
    }

    void loginUser() {
        string u, p;
        int attempts = 0;
        bool success = false;

        cout << "\n===== LOGIN =====\n";

        while (attempts < 3) {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            ifstream file("users.txt");

            while (file >> u >> p) {
                if (u == username && p == password) {
                    success = true;
                    break;
                }
            }
            file.close();

            if (success) {
                cout << "Login Successful! Welcome " << username << endl;
                return;
            } else {
                attempts++;
                cout << "Wrong details! Attempts left: " << (3 - attempts) << endl;
            }
        }

        cout << "Too many failed attempts! Access blocked.\n";
    }

    void forgotPassword() {
        string u, p;
        bool found = false;

        cout << "\n===== FORGOT PASSWORD =====\n";
        cout << "Enter username: ";
        cin >> username;

        ifstream file("users.txt");

        while (file >> u >> p) {
            if (u == username) {
                cout << "Your password is: " << p << endl;
                found = true;
                break;
            }
        }
        file.close();

        if (!found)
            cout << "User not found!\n";
    }
};

int main() {
    UserSystem obj;
    int choice;

    do {
        cout << "\n=========================\n";
        cout << "   SECURE LOGIN SYSTEM\n";
        cout << "=========================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Forgot Password\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            obj.registerUser();
            break;
        case 2:
            obj.loginUser();
            break;
        case 3:
            obj.forgotPassword();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
