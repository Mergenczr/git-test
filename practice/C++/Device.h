#include <iostream>
using namespace std;
#ifndef SKYLINE_252_DEVICE
#define SKYLINE_252_DEVICE
class Device
{
private:
string id;
public:
Device(string id);
string getID() const;
virtual float work() = 0; 
};
class ElectronicDevice : public Device {
private:
float powerPercent;
public:
ElectronicDevice(string id, float startingPower);
void addPower(float);


float getPowerPercent() const;
virtual float work();

};
class Speaker : public ElectronicDevice {
private:
int maxVolume, currentVolume;
string brand; 
string description;
public:
Speaker(string id, string brand, int maxVolume);
string getDescription() const;
void setDescription(string);
int getCurrentVolume() const;
void increaseVolume();

void increaseVolume(int);

void decreaseVolume();

void decreaseVolume(int);

void turnOff();

void turnOn();

virtual float work();
// call parent work function to decrease the power percentage
// prints out a status message with brand, new power percentage and volume
};
#endif
