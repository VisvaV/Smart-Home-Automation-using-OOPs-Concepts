#include<iostream>
#include<fstream>
#include "device.cpp"

class Light : public Device {
private:
    int brightness;
    string color;
    string mode;
public:
    Light(const string& name, int brightness = 100, const string& color = "White", const string& mode = "Normal"): Device(name), brightness(brightness), color(color), mode(mode) {}

    void setBrightness(int newBrightness) {
        brightness = newBrightness;
    }

    void setColor(const string& newColor) {
        color = newColor;
    }

    void setMode(const string& newMode) {
        mode = newMode;
    }

    void turnOn() override {
        cout << "Turning on " << getName() << " light." << endl;
    }

    void turnOff() override {
        cout << "Turning off " << getName() << " light." << endl;
    }

    string getStatus() const override {
        return getName()+ " is "+(brightness>0?"on" : "off")+", Color: "+ color + ", Mode: " +mode;
    }

    void saveToFile(const string& filename) const override {
        ofstream file(filename);
        if (file.is_open()) {
            file << name << endl;
            file << brightness << endl;
            file << color << endl;
            file << mode << endl;
        }
        else {
            cerr << "Error: Unable to open file for writing: " << filename << endl;
        }
    }

    void loadFromFile(const string& filename) override {
        ifstream file(filename);
        if (file.is_open()) {
            getline(file, name);
            file >> brightness;
            file.ignore();
            getline(file, color);
            getline(file, mode);

            cout << "Loaded settings from file: " << filename << endl;
            cout << "Name: " << name << endl;
            cout << "Brightness: " << brightness << endl;
            cout << "Color: " << color << endl;
            cout << "Mode: " << mode << endl;

        }
        else {
            cerr << "Error: Unable to open file for reading: " << filename << endl;
        }
    }
};


