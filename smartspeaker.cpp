#include<iostream>
#include<fstream>

using namespace std;

class SmartSpeaker : public Device {
private:
    int volume;
    string equalizer;
    bool bassBoost;
public:
    SmartSpeaker(const string &name, int volume = 50, const string& equalizer = "Normal", bool bassBoost = false): Device(name), volume(volume), equalizer(equalizer), bassBoost(bassBoost) {}

    void setVolume(int newVolume) {
        if (newVolume >= 0 && newVolume <= 100) {
            volume = newVolume;
            cout << getName() << " volume set to " << volume << endl;
        }
        else {
            cerr << "Invalid volume level "<< endl << "Please enter a value between 0 and 100" << endl;
        }
    }

    void setEqualizer(const string& newEqualizer) {
        equalizer = newEqualizer;
    }

    void toggleBassBoost() {
        cout << getName() << " bass boost is " << (bassBoost?"enabled":"disabled") << endl;
    }

    void turnOn() override {
        cout << "Turning on " << getName() << " Smart Speaker" << endl;
    }

    void turnOff() override {
        cout << "Turning off " << getName() << " Smart Speaker" << endl;
    }

    string getStatus() const override {
        return getName() + " is at volume level: " + to_string(volume) + ", Equalizer: " + equalizer + ", Bass Boost: " + (bassBoost?"Enabled":"Disabled");
    }

    void saveToFile(const string& filename) const override {
        ofstream file(filename);
        if (file.is_open()) {
            file << name << endl;
            file << volume << endl;
            file << equalizer << endl;
            file << (bassBoost?"1":"0") << endl;
        }
        else {
            cerr << "Error: Unable to open file for writing: " << filename << endl;
        }
    }

    void loadFromFile(const string& filename) override {
        ifstream file(filename);
        if (file.is_open()) {
            getline(file, name);
            file >> volume;
            file.ignore();
            getline(file, equalizer);
            string bassBoostStr;
            getline(file, bassBoostStr);
            bassBoost = (bassBoostStr == "1");

            cout << "Loaded settings from file: " << filename << endl;
            cout << "Name: " << name << endl;
            cout << "Volume: " << volume << endl;
            cout << "Equalizer: " << equalizer << endl;
            cout << "Bass Boost: " << (bassBoost?"Enabled":"Disabled") << endl;

        }
        else {
            cerr << "Error: Unable to open file for reading: " << filename << endl;
        }
    }
};
