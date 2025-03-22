#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Device {
protected:
    string name;
public:
    Device(const string& name) : name(name) {}

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual string getStatus() const = 0;

    string getName() const {
        return name;
    }

    void setName(const string &newName) {
        name = newName;
    }

    virtual void saveToFile(const string &filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << name << endl;
        }
        else {
            cerr << "Error: Unable to open file for writing: " << filename << endl;
        }
    }

    virtual void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            getline(file, name);
        }
        else {
            cerr << "Error: Unable to open file for reading: " << filename << endl;
        }
    }
};

