#include "Device.h"
#include <iostream>
using namespace std;


Device::Device(string id) : id(id) {}

string Device::getID() const {
    return id;
}
// When the value is greather than 100 and less than 0 it prints out the condition for starting power and it clamps up the power at 0 just in case
ElectronicDevice::ElectronicDevice(string id, float startingPower)
    : Device(id)
{
    if (startingPower < 0 || startingPower > 100) {
        cout << "Invalid starting power: " << startingPower
        << " (must be between 0 and 100)" << endl;
        powerPercent = 0;
        
        } else {
        powerPercent = startingPower;
    }
}

// When the value is greather than 100 and less than 0 it does nothing and it clamps up the power at 100 just in case
void ElectronicDevice::addPower(float value) {
    if (value < 0 || value > 100) {
           cout << "Invalid value: " << value
                << " (must be between 0 and 100)" << endl;
           return;
       }
       powerPercent += value;
       if (powerPercent > 100) powerPercent = 100;
}

float ElectronicDevice::getPowerPercent() const {
    return powerPercent;
}

float ElectronicDevice::work() {
    if (powerPercent > 0) {
        powerPercent -= 1; // decrease power when working
        if (powerPercent < 0) powerPercent = 0;
    }
    return powerPercent;
}

Speaker::Speaker(string id, string brand, int maxVolume)
    : ElectronicDevice(id, 100), brand(brand), maxVolume(maxVolume), currentVolume(0) {}

string Speaker::getDescription() const {
    return description;
}

void Speaker::setDescription(string desc) {
    description = desc;
}

int Speaker::getCurrentVolume() const {
    return currentVolume;
}

void Speaker::increaseVolume() {
    if (currentVolume < maxVolume)
        currentVolume++;
}

void Speaker::increaseVolume(int val) {
    currentVolume += val;
    if (currentVolume > maxVolume)
        currentVolume = maxVolume;
}

void Speaker::decreaseVolume() {
    if (currentVolume > 0)
        currentVolume--;
}

void Speaker::decreaseVolume(int val) {
    currentVolume -= val;
    if (currentVolume < 0) currentVolume = 0;
}

void Speaker::turnOff() {
    currentVolume = 0;
}

void Speaker::turnOn() {
    if (getPowerPercent() > 0) {
        if (currentVolume == 0) currentVolume = 1;
        
        work();
    }
}

float Speaker::work() {
    float p = ElectronicDevice::work(); 
    cout << "Speaker (" << brand << ") working. Power: " << p
         << "%, Volume: " << currentVolume << endl;
    return p;
}

class Lamp : public ElectronicDevice {
private:
    bool isOn;
public:
    Lamp(string id, float power) : ElectronicDevice(id, power), isOn(false) {}
    void turnOn() {
        if (getPowerPercent() > 0) {
            isOn = true; work(); } }
    void turnOff() {
        isOn = false; }
    bool getStatus() const {
        return isOn; } // getter
    virtual float work() {
        if (isOn) {
            float p = ElectronicDevice::work();
            cout << "Lamp is shining. Power left: " << p << "%" << endl;
            return p;
        }
        return getPowerPercent();
    }
};


int main() {
    const int MAX_DEVICES = 40;
    Device* devices[MAX_DEVICES]; // array of pointers
    int deviceCount = 0;
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Create ElectronicDevice\n";
        cout << "2. Create Speaker\n";
        cout << "3. Create Lamp\n";
        cout << "4. List Devices\n";
        cout << "5. Use work() on all devices\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            if (deviceCount >= MAX_DEVICES) {
                cout << "Device list is full!\n";
                continue;
            }
            string id;
            float startPower;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter starting power (0-100): ";
            cin >> startPower;
            devices[deviceCount] = new ElectronicDevice(id, startPower);
            deviceCount++;
            
            cout << "ElectronicDevice created!\n";
        } else if (choice == 2) {
            if (deviceCount >= MAX_DEVICES) {
                cout << "Device list is full!\n";
                continue;
            }
            string id, brand;
            int maxVol;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter brand: ";
            cin >> brand;
            cout << "Enter max volume: ";
            cin >> maxVol;
            devices[deviceCount] = new Speaker(id, brand, maxVol);
            deviceCount++;
            cout << "Speaker created!\n";
            Speaker* sp = (Speaker*) devices[deviceCount - 1];
            
            int spChoice;
            do {
                cout << "\nSpeaker Controls for ID=" << sp->getID() << ":\n";
                cout << " 1. turnOn()\n";
                cout << " 2. increaseVolume()\n";
                cout << " 3. decreaseVolume()\n";
                cout << " 0. Done\n";
                cout << "Enter choice: ";
                cin >> spChoice;
                
                if (spChoice == 1) {
                    sp->turnOn();
                } else if (spChoice == 2) {
                    sp->increaseVolume();
                    sp->work();
                } else if (spChoice == 3) {
                    sp->decreaseVolume();
                    sp->work();
                }
            } while (spChoice != 0);
            
        } else if (choice == 3) {
            if (deviceCount >= MAX_DEVICES) {
                cout << "Device list is full!\n";
                continue;
            }
            string id;
            cout << "Enter Lamp ID: ";
            cin >> id;
            
            devices[deviceCount] = new Lamp(id, 100);
            deviceCount++;
            
            cout << "Lamp created!\n";
            
        }else if (choice == 4) {
            cout << "\nDevices:\n";
            
            for (int i = 0; i < deviceCount; i++) {
                cout << i << ": ID=" << devices[i]->getID();
            }
            cout << '\n';
        }
        else if (choice == 5) {
            cout << "\nCalling work() on all devices:\n";
            for (int i = 0; i < deviceCount; ++i) {
                devices[i]->work();
            }
        }
        
    } while (choice != 6);
    cout << "Goodbye!\n";
    return 0;
    }

