#ifndef DEVICES_H
#define DEVICES_H

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>

#include <QObject>

using namespace std;

class IMU
{
public:
  IMU(){};
  IMU(string name, int id = 0){this->name = name;this->id = id;};

  int id = 4;
  string name;

  float x;
  float y;
  float z;
  float scale;

  double timestamp;

  string getString(string separator);
  string getFullString(string separator);
};

class ENCODER
{
public:
  ENCODER(){};
  ENCODER(string name, int id = 0){this->name = name;this->id = id;};

  int id = 2;
  string name;

  float rads;   // speed in radinats / s
  float a0;     // angle 0
  float a1;     // angle 1
  float da;     // delta angle

  double timestamp;

  string getString(string separator);
  string getFullString(string separator);

};

class STEER
{
public:
  STEER(){};
  STEER(string name, int id = 0){this->name = name;this->id = id;};

  int id = 5;
  string name;

  float angle;

  double timestamp;

  string getString(string separator);
  string getFullString(string separator);
};

class PEDALS
{
public:
  PEDALS(){};
  PEDALS(string name, int id = 0){this->name = name;this->id = id;};

  int id = 3;
  string name;

  float throttle1;
  float throttle2;

  float brakeRear;
  float brakeFront;
  int isBreaking;

  double timestamp;

  string getString(string separator);
  string getFullString(string separator);
};

class ECU
{
public:
  ECU(){};
  ECU(string name, int id = 0){this->name = name;this->id = id;};
  int id = 0;
  string name;

  int errors;
  int warnings;
  int map;
  int state;

  double timestamp;

  string getString(string separator);
  string getFullString(string separator);
};

class INVERTER
{
public:
  int id = 1;
  INVERTER(){};
  INVERTER(string name, int id = 0){this->name = name;this->id = id;};
  string name;

  float speed;
  float torque;
  float motorTemp;
  float IGBTTemp;

  int state;

  double timestamp;

  string getString(string separator);
  string getFullString(string separator);
};

class BMS
{
public:
  BMS(){};
  BMS(string name, int id = 0){this->name = name;this->id = id;};

  int id = 6;
  string name;

  float voltage;
  float current;
  float power;
  float temperature;

  double timestamp;

  string getString(string separator);
  string getFullString(string separator);
};

// Store all devices of Chimera
typedef struct Chimera
{
    IMU* accel = new IMU("AccelIZZE",0);
    IMU* gyro = new IMU("GyroIZZE", 1);

    INVERTER* invl = new INVERTER("Inverter Left", 2);
    INVERTER* invr = new INVERTER("Inverter Right", 3);

    BMS* BMSLV = new BMS("HV", 4);
    BMS* BMSHV = new BMS("LV", 5);

    PEDALS* pedals = new PEDALS("PEDALS", 6);
    STEER* steer = new STEER("STEER", 7);

    ENCODER* encl = new ENCODER("Encoder Left", 8);
    ENCODER* encr = new ENCODER("Encoder Right", 9);

    ECU* ecu = new ECU("ECU", 10);

} Chimera;



// Store all devices of Fenice
typedef struct Fenice
{
    IMU* accel = new IMU("AccelIZZE",0);
    IMU* gyro = new IMU("GyroIZZE", 1);

    INVERTER* invl = new INVERTER("Inverter Left", 2);
    INVERTER* invr = new INVERTER("Inverter Right", 3);

    BMS* BMSLV = new BMS("HV", 4);
    BMS* BMSHV = new BMS("LV", 5);

    PEDALS* pedals = new PEDALS("PEDALS", 6);
    STEER* steer = new STEER("STEER", 7);

    ENCODER* encl = new ENCODER("Encoder Left", 8);
    ENCODER* encr = new ENCODER("Encoder Right", 9);

    ECU* ecu = new ECU("ECU", 10);
} Fenice;

#endif
