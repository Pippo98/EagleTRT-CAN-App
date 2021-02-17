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
void IMU::getFullString(string* separator){
  string sep = *separator;
  *separator = "";
  *separator += name + sep;
  *separator += "Timestamp: " + to_string(timestamp) + sep;
  *separator += "X: " + to_string(x) + sep;
  *separator += "Y: " + to_string(y) + sep;
  *separator += "Z: " + to_string(z) + sep;
  *separator += "Scale: " + to_string(scale) + sep;
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
void ENCODER::getFullString(string* separator){
  string sep = *separator;
  *separator = "";
  *separator += name + sep;
  *separator += "Timestamp: " + to_string(timestamp) + sep;
  *separator += "Rad/s: " + to_string(rads) + sep;
  *separator += "Alpha0: " + to_string(a0) + sep;
  *separator += "Alpha1: " + to_string(a1) + sep;
  *separator += "Delta A: " + to_string(da) + sep;
}

string STEER::getString(string separator){
  string ret = "";
  ret += name + separator;
  ret += to_string(timestamp) + separator;
  ret += to_string(angle) + separator;

  return ret;
}
void STEER::getFullString(string* separator){
  string sep = *separator;
  *separator = "";
  *separator += name + sep;
  *separator += "Timestamp: " + to_string(timestamp) + sep;
  *separator += "Angle: " + to_string(angle) + sep;
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
void PEDALS::getFullString(string* separator){
  string sep = *separator;
  *separator = "";
  *separator += name + sep;
  *separator += "Timestamp: " + to_string(timestamp) + sep;
  *separator += "Throttle1: " + to_string(throttle1) + sep;
  *separator += "Throttle2: " + to_string(throttle2) + sep;
  *separator += "BrakeRear: " + to_string(brakeRear) + sep;
  *separator += "BrakeFront: " + to_string(brakeFront) + sep;
  *separator += "Is Breaking: " + to_string(isBreaking) + sep;
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
void ECU::getFullString(string* separator){
  string sep = *separator;
  *separator = "";
  *separator += name + sep;
  *separator += "Timestamp: " + to_string(timestamp) + sep;
  *separator += "Errors: " + to_string(errors) + sep;
  *separator += "Warnings: " + to_string(warnings) + sep;
  *separator += "Map: " + to_string(map) + sep;
  *separator += "State: " + to_string(state) + sep;
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
void INVERTER::getFullString(string* separator){
  string sep = *separator;
  *separator = "";
  *separator += name + sep;
  *separator += "Timestamp: " + to_string(timestamp) + sep;
  *separator += "Speed: " + to_string(speed) + sep;
  *separator += "Torque: " + to_string(torque) + sep;
  *separator += "Motor Temperature: " + to_string(motorTemp) + sep;
  *separator += "IGBT Temperature: " + to_string(IGBTTemp) + sep;
  *separator += "State: " + to_string(state) + sep;
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
void BMS::getFullString(string* separator){
  string sep = *separator;
  *separator = "";
  *separator += name + sep;
  *separator += "Timestamp: " + to_string(timestamp) + sep;
  *separator += "Voltage: " + to_string(voltage) + sep;
  *separator += "Current: " + to_string(current) + sep;
  *separator += "Power: " + to_string(power) + sep;
  *separator += "Temperature: " + to_string(temperature) + sep;
}


string Chimera::getFullStringOfID(int id, string separator){
    switch (id) {
    case 0:
        accel->getFullString(&separator);
        break;
    case 1:
        gyro->getFullString(&separator);
        break;
    case 2:
        invl->getFullString(&separator);
        break;
    case 3:
        invr->getFullString(&separator);
        break;
    case 4:
        BMSLV->getFullString(&separator);
        break;
    case 5:
        BMSHV->getFullString(&separator);
        break;
    case 6:
        pedals->getFullString(&separator);
        break;
    case 7:
        steer->getFullString(&separator);
        break;
    case 8:
        encl->getFullString(&separator);
        break;
    case 9:
        encr->getFullString(&separator);
        break;
    case 10:
        ecu->getFullString(&separator);
        break;
    default:
        return "Id not found";
        break;
    }
    return separator;
}

stringstream Chimera::serialize(SerializationType type){
    stringstream ss;

    if(type == Text){
        text_oarchive ar(ss, 1);
        ar & accel;
        ar & gyro;
        ar & invl;
        ar & invr;
        ar & BMSLV;
        ar & BMSHV;
        ar & pedals;
        ar & steer;
        ar & encl;
        ar & encr;
        ar & ecu;
    }
    else if(type == XML){
        xml_oarchive ar(ss);
        ar & BOOST_SERIALIZATION_NVP(accel);
        ar & BOOST_SERIALIZATION_NVP(gyro);
        ar & BOOST_SERIALIZATION_NVP(invl);
        ar & BOOST_SERIALIZATION_NVP(invr);
        ar & BOOST_SERIALIZATION_NVP(BMSLV);
        ar & BOOST_SERIALIZATION_NVP(BMSHV);
        ar & BOOST_SERIALIZATION_NVP(pedals);
        ar & BOOST_SERIALIZATION_NVP(steer);
        ar & BOOST_SERIALIZATION_NVP(encl);
        ar & BOOST_SERIALIZATION_NVP(encr);
        ar & BOOST_SERIALIZATION_NVP(ecu);
    }
    else if(type == Bin){
        binary_oarchive ar(ss, 1);
        ar & accel;
        ar & gyro;
        ar & invl;
        ar & invr;
        ar & BMSLV;
        ar & BMSHV;
        ar & pedals;
        ar & steer;
        ar & encl;
        ar & encr;
        ar & ecu;
    }

    return ss;
}

void Chimera::unserialize(SerializationType type, stringstream *data){

    if(type == Text){
        text_iarchive ar(*data, 1);
        ar & accel;
        ar & gyro;
        ar & invl;
        ar & invr;
        ar & BMSLV;
        ar & BMSHV;
        ar & pedals;
        ar & steer;
        ar & encl;
        ar & encr;
        ar & ecu;
    }
    else if(type == XML){
        xml_iarchive ar(*data);
        ar & BOOST_SERIALIZATION_NVP(accel);
        ar & BOOST_SERIALIZATION_NVP(gyro);
        ar & BOOST_SERIALIZATION_NVP(invl);
        ar & BOOST_SERIALIZATION_NVP(invr);
        ar & BOOST_SERIALIZATION_NVP(BMSLV);
        ar & BOOST_SERIALIZATION_NVP(BMSHV);
        ar & BOOST_SERIALIZATION_NVP(pedals);
        ar & BOOST_SERIALIZATION_NVP(steer);
        ar & BOOST_SERIALIZATION_NVP(encl);
        ar & BOOST_SERIALIZATION_NVP(encr);
        ar & BOOST_SERIALIZATION_NVP(ecu);
    }
    else if(type == Bin){
        binary_iarchive ar(*data, 1);
        ar & accel;
        ar & gyro;
        ar & invl;
        ar & invr;
        ar & BMSLV;
        ar & BMSHV;
        ar & pedals;
        ar & steer;
        ar & encl;
        ar & encr;
        ar & ecu;
    }
}

string Chimera::getJSON(){
    string s;

    return s;
}
