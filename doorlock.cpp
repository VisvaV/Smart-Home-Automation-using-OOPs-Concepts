#include<iostream>
#include<fstream>

using namespace std;

class DoorLock : public Device {
private:
    bool locked;
    string accessCode;
    bool bolted;
public:
    DoorLock(const string& name, bool locked = true, const string& accessCode = "1234", bool bolted = false): Device(name), locked(locked), accessCode(accessCode), bolted(bolted) {}

    void lock() {
        if (!bolted) {
            locked = true;
            cout << getName() << " is locked." << endl;
        }
        else {
            cout << "Cannot lock " << getName() << ". The door is bolted." << endl;
        }
    }

    void unlock() {
        locked = false;
        cout << getName() << " is unlocked." << endl;
    }

    void setAccessCode(const string& newAccessCode) {
        accessCode = newAccessCode;
    }

    void boltDoor() {
        bolted = true;
        cout << getName() << " door is bolted." << endl;
    }

    void unboltDoor() {
        bolted = false;
        cout << getName() << " door is unbolted." << endl;
    }

    void turnOn() override {
        unlock();
    }

    void turnOff() override {
        lock();
    }

    string getStatus() const override {
        string status = getName();
        if (locked)
            status+=" is locked";
        else
            status+=" is unlocked";

        if (bolted)
            status += ", Door is bolted";

        return status;
    }


    void saveToFile(const string& filename) const override {
        ofstream file(filename);
        if (file.is_open()) {
            file << name << endl;
            file << (locked ? "1" : "0") << endl;
            file << accessCode << endl;
            file << (bolted ? "1" : "0") << endl;
        }
        else {
            cerr << "Error: Unable to open file for writing: " << filename << endl;
        }
    }

    void loadFromFile(const string& filename) override {
        ifstream file(filename);
        if (file.is_open()) {
            getline(file, name);
            string lockedStr;
            getline(file, lockedStr);
            locked = (lockedStr == "1");
            getline(file, accessCode);
            string boltedStr;
            getline(file, boltedStr);
            bolted = (boltedStr == "1");

            cout << "Loaded settings from file: " << filename << endl;
            cout << "Name: " << name << endl;
            cout << "Locked: " << (locked ? "Yes" : "No") << endl;
            cout << "Access Code: " << accessCode << endl;
            cout << "Bolted: " << (bolted ? "Yes" : "No") << endl;

        }
        else {
            cerr << "Error: Unable to open file for reading: " << filename << endl;
        }
    }
};

