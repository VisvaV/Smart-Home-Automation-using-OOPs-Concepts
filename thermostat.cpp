#include<iostream>
#include<fstream>

using namespace std;

class Thermostat : public Device {
private:
    int temperature;
    string mode;
    int humidity;
public:
    Thermostat(const string& name, int temperature = 25, const string& mode = "Heat", int humidity = 50): Device(name), temperature(temperature), mode(mode), humidity(humidity) {}

    void setTemperature(int newTemperature) {
        temperature = newTemperature;
    }

    void setMode(const string& newMode) {
        mode = newMode;
    }

    void setHumidity(int newHumidity) {
        humidity = newHumidity;
    }

    void turnOn() override {
        cout << "Turning on " << getName() << " thermostat." << endl;
    }

    void turnOff() override {
        cout << "Turning off " << getName() << " thermostat." << endl;
    }

    string getStatus() const override {
        return getName() + " is set to " + to_string(temperature) + "C, Mode: " + mode + ", Humidity: " + to_string(humidity) + "%";
    }

    void saveToFile(const string& filename) const override {
        ofstream file(filename);
        if (file.is_open()) {
            file << name << endl;
            file << temperature << endl;
            file << mode << endl;
            file << humidity << endl;
        } else {
            cerr << "Error: Unable to open file for writing: " << filename << endl;
        }
    }

    void loadFromFile(const string& filename) override {
        ifstream file(filename);
        if (file.is_open()) {
            getline(file, name);
            file >> temperature;
            file.ignore();
            getline(file, mode);
            file >> humidity;

            cout << "Loaded settings from file: " << filename << endl;
            cout << "Name: " << name << endl;
            cout << "Temperature: " << temperature << "C" << endl;
            cout << "Mode: " << mode << endl;
            cout << "Humidity: " << humidity << "%" << endl;

        }
        else {
            cerr << "Error: Unable to open file for reading: " << filename << endl;
        }
    }
};
