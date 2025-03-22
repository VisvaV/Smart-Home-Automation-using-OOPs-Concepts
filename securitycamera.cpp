#include<iostream>
#include<fstream>

using namespace std;

class SecurityCamera : public Device {
private:
    bool recording;
    string resolution;
    int angle;
public:
    SecurityCamera(const string& name, bool recording = false, const string& resolution = "1080p", int angle = 0): Device(name), recording(recording), resolution(resolution), angle(angle) {}

    void startRecording() {
        recording = true;
        cout << getName() << " has started recording." << endl;
    }

    void stopRecording() {
        recording = false;
        cout << getName() << " has stopped recording." << endl;
    }

    void setResolution(const string& newResolution) {
        resolution = newResolution;
    }

    void setAngle(int newAngle) {
        angle = newAngle;
    }

    void turnOn() override {
        startRecording();
    }

    void turnOff() override {
        stopRecording();
    }

    string getStatus() const override {
        return getName() + (recording ? " is recording" : " is not recording") + ", Resolution: " + resolution + ", Angle: " + to_string(angle);
    }

    void saveToFile(const string& filename) const override {
        ofstream file(filename);
        if (file.is_open()) {
            file << name << endl;
            file << (recording?"1":"0") << endl;
            file << resolution << endl;
            file << angle << endl;
        }
        else {
            cerr << "Error: Unable to open file for writing: " << filename << endl;
        }
    }

    void loadFromFile(const string& filename) override {
        ifstream file(filename);
        if (file.is_open()) {
            getline(file, name);
            string recordingStr;
            getline(file, recordingStr);
            recording = (recordingStr == "1");
            getline(file, resolution);
            file >> angle;

            cout << "Loaded settings from file: " << filename << endl;
            cout << "Name: " << name << endl;
            cout << "Recording: " << (recording ? "Yes" : "No") << endl;
            cout << "Resolution: " << resolution << endl;
            cout << "Angle: " << angle << "°" << endl;

        }
        else {
            cerr << "Error: Unable to open file for reading: " << filename << endl;
        }
    }
};
