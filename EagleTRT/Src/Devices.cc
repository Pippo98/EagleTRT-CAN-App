#include "Devices.h"

string IMU::getString(string separator){
  string ret = "";
  ret += name + separator;
  ret += to_string(timestamp) + separator;
  ret += to_string(x) + separator;
  ret += to_string(y) + separator;
  ret += to_string(z) + separator;
  ret += to_string(scale) + separator;

  return ret;
};
string IMU::getFullString(string separator){
  string ret = "";
  ret += name + separator;
  ret += "Timestamp: " + to_string(timestamp) + separator;
  ret += "X: " + to_string(x) + separator;
  ret += "Y: " + to_string(y) + separator;
  ret += "Z: " + to_string(z) + separator;
  ret += "Scale: " + to_string(scale) + separator;

  return ret;
};

string ENCODER::getString(string separator){
  string ret = "";
  ret += name + separator;
  ret += to_string(timestamp) + separator;
  ret += to_string(rads) + separator;
  ret += to_string(a0) + separator;
  ret += to_string(a1) + separator;
  ret += to_string(da) + separator;

  return ret;
}
string ENCODER::getFullString(string separator){
  string ret = "";
  ret += name + separator;
  ret += "Timestamp: " + to_string(timestamp) + separator;
  ret += "Rad/s: " + to_string(rads) + separator;
  ret += "Alpha0: " + to_string(a0) + separator;
  ret += "Alpha1: " + to_string(a1) + separator;
  ret += "Delta A: " + to_string(da) + separator;

  return ret;
}

string STEER::getString(string separator){
  string ret = "";
  ret += name + separator;
  ret += to_string(timestamp) + separator;
  ret += to_string(angle) + separator;

  return ret;
}
string STEER::getFullString(string separator){
  string ret = "";
  ret += name + separator;
  ret += "Timestamp: " + to_string(timestamp) + separator;
  ret += "Angle: " + to_string(angle) + separator;

  return ret;
}

string PEDALS::getString(string separator){
  string ret = "";
  ret += name + separator;
  ret += to_string(timestamp) + separator;
  ret += to_string(throttle1) + separator;
  ret += to_string(throttle2) + separator;
  ret += to_string(brakeRear) + separator;
  ret += to_string(brakeFront) + separator;
  ret += to_string(isBreaking) + separator;

  return ret;
}
string PEDALS::getFullString(string separator){
  string ret = "";
  ret += name + separator;
  ret += "Timestamp: " + to_string(timestamp) + separator;
  ret += "Throttle1: " + to_string(throttle1) + separator;
  ret += "Throttle2: " + to_string(throttle2) + separator;
  ret += "BrakeRear: " + to_string(brakeRear) + separator;
  ret += "BrakeFront: " + to_string(brakeFront) + separator;
  ret += "Is Breaking: " + to_string(isBreaking) + separator;

  return ret;
}

string ECU::getString(string separator){
  string ret = "";
  ret += name + separator;
  ret += to_string(timestamp) + separator;
  ret += to_string(errors) + separator;
  ret += to_string(warnings) + separator;
  ret += to_string(map) + separator;
  ret += to_string(state) + separator;

  return ret;
}
string ECU::getFullString(string separator){
  string ret = "";
  ret += name + separator;
  ret += "Timestamp: " + to_string(timestamp) + separator;
  ret += "Errors: " + to_string(errors) + separator;
  ret += "Warnings: " + to_string(warnings) + separator;
  ret += "Map: " + to_string(map) + separator;
  ret += "State: " + to_string(state) + separator;

  return ret;
}

string INVERTER::getString(string separator){
  string ret = "";
  ret += name + separator;
  ret += to_string(timestamp) + separator;
  ret += to_string(speed) + separator;
  ret += to_string(torque) + separator;
  ret += to_string(motorTemp) + separator;
  ret += to_string(IGBTTemp) + separator;
  ret += to_string(state) + separator;

  return ret;
}
string INVERTER::getFullString(string separator){
  string ret = "";
  ret += name + separator;
  ret += "Timestamp: " + to_string(timestamp) + separator;
  ret += "Speed: " + to_string(speed) + separator;
  ret += "Torque: " + to_string(torque) + separator;
  ret += "Motor Temperature: " + to_string(motorTemp) + separator;
  ret += "IGBT Temperature: " + to_string(IGBTTemp) + separator;
  ret += "State: " + to_string(state) + separator;

  return ret;
}

string BMS::getString(string separator){
  string ret = "";
  ret += name + separator;
  ret += to_string(timestamp) + separator;
  ret += to_string(voltage) + separator;
  ret += to_string(current) + separator;
  ret += to_string(power) + separator;
  ret += to_string(temperature) + separator;

  return ret;
}
string BMS::getFullString(string separator){
  string ret = "";
  ret += name + separator;
  ret += "Timestamp: " + to_string(timestamp) + separator;
  ret += "Voltage: " + to_string(voltage) + separator;
  ret += "Current: " + to_string(current) + separator;
  ret += "Power: " + to_string(power) + separator;
  ret += "Temperature: " + to_string(temperature) + separator;

  return ret;
}
