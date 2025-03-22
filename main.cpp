#include <iostream>
#include <vector>
#include "light.cpp"
#include "thermostat.cpp"
#include "doorlock.cpp"
#include "securitycamera.cpp"
#include "smartspeaker.cpp"
#define password "admin@123"
#define acscode "access@123"

using namespace std;

void displayMenu(vector<Device*> &devices) {
    cout << "\n--- Smart Home Automation Menu ---" << endl;
    for (int i=0; i<devices.size(); i++) {
        cout << i+1 << ". " << devices[i]->getName() << endl;
    }
    cout << devices.size()+1 << ". Display Device Contents" << endl;
    cout << devices.size()+2 << ". Exit" << endl;
}

void displayDeviceContents(Device* device) {
    try {
        ifstream file(device->getName() + ".txt");
        if (file.is_open()) {
            string line;
            cout << "\n--- Contents of " << device->getName() << " ---" << endl;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
        else {
            throw runtime_error("Unable to open file for " + device->getName());
        }
    }
    catch (exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
}

void display(const vector<Device*>& devices) {
    try {
        cout << "\n--- List of Devices ---" << endl;
        for (int i=0; i<devices.size(); i++) {
            cout << i + 1 << ". " << devices[i]->getName() << endl;
        }

        int choice;
        cout << "\nEnter the number of the device to display its contents: ";
        if (!(cin >> choice) || choice < 1 || choice > devices.size()) {
            throw runtime_error("Invalid choice. Please enter a valid number");
        }
        displayDeviceContents(devices[choice - 1]);
    }
    catch (exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
}

int main() {
    Light light("Living Room Light", 80, "White", "Normal");
    Thermostat thermostat("Living Room Thermostat", 22, "Heat", 60);
    DoorLock doorLock("Front Door Lock", false, "1234", true);
    SecurityCamera securityCamera("Living Room Camera", true, "4K", 120);
    SmartSpeaker smartSpeaker("Living Room Speaker", 70, "Bass Boost", true);

    vector<Device*> devices = {&light, &thermostat, &doorLock, &securityCamera, &smartSpeaker};

    for (const auto& device : devices) {
        device->saveToFile(device->getName()+".txt");
    }

    bool exitProgram=false;

    string pwd;
    cout << "-----HOME AUTOMATION-----" << endl;
    cout << "Enter HOME ACCESS CODE: ";
    cin >> pwd;
    if (pwd != password){
        cout << "INVALID ACCESS CODE" << endl << "Exiting now..." << endl;
        exit(0);
    }
    while (!exitProgram) {
        displayMenu(devices);
        try {
            int choice;
            cout << "\nEnter your choice: ";
            if (!(cin >> choice)) {
                throw runtime_error("Invalid input. Exiting...");
            }

            if (choice >= 1 && choice <= devices.size()) {
                Device* selectedDevice = devices[choice-1];

                cout << "\nSelected device: " << selectedDevice->getName() << endl;

                selectedDevice->turnOn();

                if (Light* light=dynamic_cast<Light*>(selectedDevice)) {
                    int brightness;
                    bool validInput=false;
                    while (!validInput) {
                        cout << "Enter brightness level (1-100): ";
                        if (!(cin >> brightness)) {
                            throw runtime_error("Invalid input. Exiting...");
                        }
                        else if (brightness<1 || brightness>100) {
                            cerr << "\nInvalid input. Brightness level must be between 1 and 100." << endl;
                        }
                        else {
                            light->setBrightness(brightness);
                            validInput = true;
                        }
                    }

                    string color;
                    cout << "Enter color: ";
                    cin >> color;

                    string mode;
                    cout << "Enter mode (STATIC/AMBIENT/BLINKING/WAVE): ";
                    cin >> mode;
                    light->setMode(mode);
                    selectedDevice->saveToFile(selectedDevice->getName() + ".txt");
                }

                if (Thermostat* thermostat = dynamic_cast<Thermostat*>(selectedDevice)) {
                    int temperature;
                    cout << "Enter temperature: ";
                    if (!(cin >> temperature)) {
                        throw runtime_error("Invalid input. Exiting...");
                    }

                    thermostat->setTemperature(temperature);

                    string mode;
                    cout << "Enter mode: ";
                    cin >> mode;
                    thermostat->setMode(mode);

                    int humidity;
                    cout << "Enter humidity: ";
                    if (!(cin >> humidity)) {
                        throw runtime_error("Invalid input. Exiting...");
                    }

                    thermostat->setHumidity(humidity);
                    selectedDevice->saveToFile(selectedDevice->getName()+".txt");
                }

                if (DoorLock* doorLock = dynamic_cast<DoorLock*>(selectedDevice)) {
                    int ch;
                    cout << "Do you want to change access code (1.YES/2.NO): ";
                    cin >> ch;
                    string accessCode;
                    if (ch == 1) {
                        cout << "Enter access code: ";
                        cin >> accessCode;
                        if (accessCode == acscode){
                            cout << "INVALID ACCESS CODE" << endl << "Exiting now..." << endl;
                            exit(0);
                            doorLock->setAccessCode(accessCode);
                        }
                    }

                    string lockAction;
                    cout << "Enter 'lock' or 'unlock': ";
                    if (!(cin >> lockAction)) {
                        throw runtime_error("Invalid input. Exiting...");
                    }

                    if (lockAction == "lock") {
                        doorLock->lock();
                    }
                    else if (lockAction == "unlock") {
                        doorLock->unlock();
                    }
                    else {
                        cerr << "\nInvalid action. Exiting..." << endl;
                        break;
                    }
                    selectedDevice->saveToFile(selectedDevice->getName() + ".txt");
                }

                if (SecurityCamera* securityCamera = dynamic_cast<SecurityCamera*>(selectedDevice)) {
                    string resolution;
                    cout << "Enter resolution: ";
                    cin >> resolution;
                    securityCamera->setResolution(resolution);

                    int angle;
                    cout << "Enter angle: ";
                    if (!(cin >> angle)) {
                        throw runtime_error("Invalid input. Exiting...");
                    }

                    securityCamera->setAngle(angle);

                    string recordingAction;
                    cout << "Enter 'start' or 'stop' recording: ";
                    if (!(cin >> recordingAction)) {
                        throw runtime_error("Invalid input. Exiting...");
                    }

                    if (recordingAction == "start") {
                        securityCamera->startRecording();
                    }
                    else if (recordingAction == "stop") {
                        securityCamera->stopRecording();
                    }
                    else {
                        throw runtime_error("Invalid input. Exiting...");
                    }
                    selectedDevice->saveToFile(selectedDevice->getName() + ".txt");
                }

                if (SmartSpeaker* smartSpeaker = dynamic_cast<SmartSpeaker*>(selectedDevice)) {
                    int volume;
                    cout << "Enter volume level: ";
                    if (!(cin >> volume)) {
                        throw runtime_error("Invalid input. Exiting...");
                    }

                    smartSpeaker->setVolume(volume);

                    string equalizer;
                    cout << "Enter equalizer setting (GRAPHIC/DYNAMIC): ";
                    cin >> equalizer;
                    smartSpeaker->setEqualizer(equalizer);
                    string bassBoostAction;
                    cout << "Enter 'enable' or 'disable' bass boost: ";
                    if (!(cin >> bassBoostAction)) {
                        throw runtime_error("Invalid input. Exiting...");
                    }

                    if (bassBoostAction == "enable") {
                        smartSpeaker->toggleBassBoost();
                    }
                    else if (bassBoostAction == "disable") {
                        smartSpeaker->toggleBassBoost();
                    }
                    else {
                        throw runtime_error("Invalid input. Exiting...");
                    }
                    selectedDevice->saveToFile(selectedDevice->getName() + ".txt");
                }

            }
            else if (choice == devices.size() + 2) {
                for (auto& device : devices) {
                    device->loadFromFile(device->getName() + ".txt");
                }
                exitProgram = true;
            }
            else if(choice == devices.size() +1) {
                display(devices);
            }
            else {
                cerr << "\nInvalid choice. Please enter a number between 1 and " << devices.size() + 1 << endl;
            }
        }
        catch (exception& e) {
            cerr << "Exception caught: " << e.what() << endl;
        }
    }

    return 0;
}
