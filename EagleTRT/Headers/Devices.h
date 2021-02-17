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

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
using namespace boost::serialization;
using namespace boost::archive;

using namespace std;

enum SerializationType{
    Text,
    XML,
    Bin
};

class IMU
{
public:
  IMU(){};
  IMU(string name, int id = 0){this->name = name;this->id = id;};

  int id;
  string name;

  float x;
  float y;
  float z;
  float scale;

  double timestamp;

  string getString(string separator);
  void getFullString(string* separator);

private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & BOOST_SERIALIZATION_NVP(name);
    ar & BOOST_SERIALIZATION_NVP(timestamp);
    ar & BOOST_SERIALIZATION_NVP(x);
    ar & BOOST_SERIALIZATION_NVP(y);
    ar & BOOST_SERIALIZATION_NVP(z);
    ar & BOOST_SERIALIZATION_NVP(scale);
  }
};

class ENCODER
{
public:
  ENCODER(){};
  ENCODER(string name, int id = 0){this->name = name;this->id = id;};

  int id;
  string name;

  float rads;   // speed in radinats / s
  float a0;     // angle 0
  float a1;     // angle 1
  float da;     // delta angle

  double timestamp;

  string getString(string separator);
  void getFullString(string* separator);
private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & BOOST_SERIALIZATION_NVP(name);
    ar & BOOST_SERIALIZATION_NVP(timestamp);
    ar & BOOST_SERIALIZATION_NVP(rads);
    ar & BOOST_SERIALIZATION_NVP(a0);
    ar & BOOST_SERIALIZATION_NVP(a1);
    ar & BOOST_SERIALIZATION_NVP(da);
  }
};

class STEER
{
public:
  STEER(){};
  STEER(string name, int id = 0){this->name = name;this->id = id;};

  int id;
  string name;

  float angle;

  double timestamp;

  string getString(string separator);
  void getFullString(string* separator);
private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & BOOST_SERIALIZATION_NVP(name);
    ar & BOOST_SERIALIZATION_NVP(timestamp);
    ar & BOOST_SERIALIZATION_NVP(angle);
  }
};

class PEDALS
{
public:
  PEDALS(){};
  PEDALS(string name, int id = 0){this->name = name;this->id = id;};

  int id;
  string name;

  float throttle1;
  float throttle2;

  float brakeRear;
  float brakeFront;
  int isBreaking;

  double timestamp;

  string getString(string separator);
  void getFullString(string* separator);
private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & BOOST_SERIALIZATION_NVP(name);
    ar & BOOST_SERIALIZATION_NVP(timestamp);
    ar & BOOST_SERIALIZATION_NVP(throttle1);
    ar & BOOST_SERIALIZATION_NVP(throttle2);
    ar & BOOST_SERIALIZATION_NVP(brakeRear);
    ar & BOOST_SERIALIZATION_NVP(brakeFront);
    ar & BOOST_SERIALIZATION_NVP(isBreaking);
  }
};

class ECU
{
public:
  ECU(){};
  ECU(string name, int id = 0){this->name = name;this->id = id;};

  int id;
  string name;

  int errors;
  int warnings;
  int map;
  int state;

  double timestamp;

  string getString(string separator);
  void getFullString(string* separator);

private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & BOOST_SERIALIZATION_NVP(name);
    ar & BOOST_SERIALIZATION_NVP(timestamp);
    ar & BOOST_SERIALIZATION_NVP(errors);
    ar & BOOST_SERIALIZATION_NVP(warnings);
    ar & BOOST_SERIALIZATION_NVP(map);
    ar & BOOST_SERIALIZATION_NVP(state);
  }
};

class INVERTER
{
public:
  INVERTER(){};
  INVERTER(string name, int id = 0){this->name = name;this->id = id;};

  int id;
  string name;

  float speed;
  float torque;
  float motorTemp;
  float IGBTTemp;

  int state;

  double timestamp;

  string getString(string separator);
  void getFullString(string* separator);
private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & BOOST_SERIALIZATION_NVP(name);
    ar & BOOST_SERIALIZATION_NVP(timestamp);
    ar & BOOST_SERIALIZATION_NVP(speed);
    ar & BOOST_SERIALIZATION_NVP(torque);
    ar & BOOST_SERIALIZATION_NVP(motorTemp);
    ar & BOOST_SERIALIZATION_NVP(IGBTTemp);
    ar & BOOST_SERIALIZATION_NVP(state);
  }
};

class BMS
{
public:
  BMS(){};
  BMS(string name, int id = 0){this->name = name;this->id = id;};

  int id;
  string name;

  float voltage;
  float current;
  float power;
  float temperature;

  double timestamp;

  string getString(string separator);
  void getFullString(string* separator);

private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & BOOST_SERIALIZATION_NVP(name);
    ar & BOOST_SERIALIZATION_NVP(timestamp);
    ar & BOOST_SERIALIZATION_NVP(voltage);
    ar & BOOST_SERIALIZATION_NVP(current);
    ar & BOOST_SERIALIZATION_NVP(power);
    ar & BOOST_SERIALIZATION_NVP(temperature);
  }
};

typedef string funcPointer(string* separator);

class Chimera{
public:
    Chimera(){};

    IMU* accel = new IMU("Accel IZZE",0);
    IMU* gyro = new IMU("Gyro IZZE", 1);

    INVERTER* invl = new INVERTER("Inverter Left", 2);
    INVERTER* invr = new INVERTER("Inverter Right", 3);

    BMS* BMSLV = new BMS("HV", 4);
    BMS* BMSHV = new BMS("LV", 5);

    PEDALS* pedals = new PEDALS("Pedals", 6);
    STEER* steer = new STEER("Steer", 7);

    ENCODER* encl = new ENCODER("Encoder Left", 8);
    ENCODER* encr = new ENCODER("Encoder Right", 9);

    ECU* ecu = new ECU("ECU", 10);

    // get the string of the right sensor basing on the id assigned to it
    // If a new sensor is added make sure to update this function
    string getFullStringOfID(int id, string separator);
    stringstream serialize(SerializationType);
    void unserialize(SerializationType, stringstream*);
    string getJSON();
};


// Store all devices of Fenice
typedef struct Fenice
{
    IMU* accel = new IMU("Acce lIZZE",0);
    IMU* gyro = new IMU("Gyro IZZE", 1);

    INVERTER* invl = new INVERTER("Inverter Left", 2);
    INVERTER* invr = new INVERTER("Inverter Right", 3);

    BMS* BMSLV = new BMS("HV", 4);
    BMS* BMSHV = new BMS("LV", 5);

    PEDALS* pedals = new PEDALS("Pedals", 6);
    STEER* steer = new STEER("Steer", 7);

    ENCODER* encl = new ENCODER("Encoder Left", 8);
    ENCODER* encr = new ENCODER("Encoder Right", 9);

    ECU* ecu = new ECU("ECU", 10);
} Fenice;

#endif
