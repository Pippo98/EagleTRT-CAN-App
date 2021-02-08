#include "Parser.h"

#include <QString>


// timestamp             channel       id#payload
// (1608055823.792621)   can0         0D0#1502FF02FF00006B
vector<int> Parser::splitMessage(double *timestamp, int *id, string message){
  vector<int> payload;

  // removing unnecessary chars
  boost::range::remove_erase_if(message, boost::is_any_of("()"));

  vector<string> sTimestamp;
  vector<string> sIdPaload;
  boost::split(sTimestamp, message, boost::is_any_of(" "));

  if(sTimestamp.size() < 3)
    return payload;

  // assing the payload that has to be split again by #
  sIdPaload.push_back(sTimestamp.at(2));

  // converting first string (timestamp) to double
  //*timestamp = stod(sTimestamp[0].c_str(), nullptr);
  QString* m = new QString(sTimestamp[0].c_str());
  *timestamp = m->toDouble();

  boost::split(sIdPaload, sIdPaload[0], boost::is_any_of("#"));

  if(sIdPaload.size() <= 0)
    return payload;

  boost::algorithm::to_lower(sIdPaload[0]);
  *id = std::stoi(sIdPaload[0], nullptr, 16);

  for(uint8_t i = 0; i < sIdPaload[1].size()-2; i+=2){
    string bff = sIdPaload[1].substr(i, 2);
    boost::algorithm::to_lower(bff);
    if(bff.size() <= 1)
      continue;
    payload.push_back(std::stoi(bff, nullptr, 16));
  }

  return payload;
}

void Parser::getTimestamp(double* timestamp, string message){
    // removing unnecessary chars
    boost::range::remove_erase_if(message, boost::is_any_of("()"));

    vector<string> sTimestamp;
    boost::split(sTimestamp, message, boost::is_any_of(" "));

    // converting first string (timestamp) to double
    //*timestamp = stod(sTimestamp[0].c_str(), nullptr);
    QString* m = new QString(sTimestamp[0].c_str());
    *timestamp = m->toDouble();
}

int Parser::parseChimeraMessage(double timestamp, int id, vector<int> msg, Chimera* chimera){

  int type = -1;

  switch (id){
    case 0xB0:
    // throttle
    // brake
    if(msg[0] == 0x01){
      chimera->pedals->throttle1 = msg[1];
      chimera->pedals->throttle2 = msg[2];
      chimera->pedals->timestamp = timestamp;
    }else
    if(msg[0] == 0x02){
      chimera->pedals->isBreaking = msg[1];
      chimera->pedals->brakeFront = (msg[2] * 256 + msg[4]) / 500;
      chimera->pedals->brakeRear = (msg[5] * 256 + msg[7]) / 500;
      chimera->pedals->timestamp = timestamp;
    }
    type = chimera->pedals->id;
    break;

    case 0xC0:
    // old IMU
    // steer
    if(msg[0] == 0x02){
      chimera->steer->angle = (msg[1] * 256 + msg[2])/100;
      chimera->steer->timestamp = timestamp;
      type = chimera->steer->id;
    }
    break;
    case 0xD0:
      if(msg[0] == 0x07){
        chimera->encr->rads = ((msg[1] << 16) + (msg[2] << 8) + msg[3]) / 10000;

        if (msg[7] == 0x01)
          chimera->encr->rads *= -1;

        chimera->encr->timestamp = timestamp;
        type = chimera->encr->id;
      }else
      if(msg[0] == 0x15){
        chimera->encr->a0 = (msg[1] * 256 + msg[2]) / 100;
        chimera->encr->a1 = (msg[3] * 256 + msg[4]) / 100;
        chimera->encr->da = (msg[5] * 256 + msg[6]) / 100;

        chimera->encr->timestamp = timestamp;
        type = chimera->encr->id;
      }
    break;
    case 0x55:
      // ECU State
      if(id == 0x55)
        if(msg[0] == 0x01){
          chimera->ecu->state = msg[4];
          chimera->ecu->timestamp = timestamp;
          type = chimera->ecu->id;
        }
    break;
    case 0xA0:break;

    // BMS HV
    case 0xAA:
      if(msg[0] == 0x01){
        chimera->BMSHV->voltage = ((msg[1] << 16) + (msg[2] << 8))/10000;
        chimera->BMSHV->timestamp = timestamp;
      }else
      if(msg[0] == 0x05){
        chimera->BMSHV->current = (msg[1] * 256 + msg[2])/10;
        chimera->BMSHV->power = (msg[3]*256 + msg[4]);
        chimera->BMSHV->timestamp = timestamp;
      }else
      if(msg[0] == 0xA0){
        chimera->BMSHV->temperature = (msg[1] * 256 + msg[2]) / 10;
        chimera->BMSHV->timestamp = timestamp;
      }
      type = chimera->BMSHV->id;
    break;

    // BMS LV
    case 0xFF:
          chimera->BMSLV->voltage = msg[0]/10;
          chimera->BMSLV->temperature = msg[2]/5;
          chimera->BMSLV->timestamp = timestamp;
          type = chimera->BMSLV->id;
    break;

    // from inverters
    case 0x181:
      // INVERTER LEFT
      if(msg[0] == 0xA0){
        chimera->invl->torque = (msg[2] * 256 + msg[1]);

        if(chimera->invl->torque > 32768)
          chimera->invl->torque -= 65536;

        chimera->invl->timestamp = timestamp;
      }else
      if(msg[0] == 0x4A){
        chimera->invl->IGBTTemp = (msg[2] * 256 + msg[1] - 15797) / 112.1182;
        chimera->invl->timestamp = timestamp;
      }else
      if(msg[0] == 0x49){
        chimera->invl->motorTemp = (msg[2] * 256 + msg[1] - 9393.9) / 55.1;
        chimera->invl->timestamp = timestamp;
      }else
      if(msg[0] == 0xA8){
        chimera->invl->speed = (msg[2] * 256 + msg[1]);
        if(chimera->invl->speed > 32768)
          chimera->invl->speed -= 65536;
        chimera->invl->timestamp = timestamp;
      }
      type = chimera->invl->id;

    break;
    case 0x182:
      if(msg[0] == 0xA0){
        chimera->invr->torque = (msg[2] * 256 + msg[1]);

        if(chimera->invr->torque > 32768)
          chimera->invr->torque -= 65536;

        chimera->invr->timestamp = timestamp;
      }else
      if(msg[0] == 0x4A){
        chimera->invr->IGBTTemp = (msg[2] * 256 + msg[1] - 15797) / 112.1182;
        chimera->invr->timestamp = timestamp;
      }else
      if(msg[0] == 0x49){
        chimera->invr->motorTemp = (msg[2] * 256 + msg[1] - 9393.9) / 55.1;
        chimera->invr->timestamp = timestamp;
      }else
      if(msg[0] == 0xA8){
        chimera->invr->speed = (msg[2] * 256 + msg[1]);
        if(chimera->invr->speed > 32768)
          chimera->invr->speed -= 65536;
        chimera->invr->timestamp = timestamp;
      }
      type = chimera->invr->id;
    break;

    //requestes to INVERTER
    case 0x201:break;
    case 0x202:break;

    // IZZE IMU
    case 0x4ED:
    {
      chimera->accel->scale = 8;
      float x = (msg[0] * 256 + msg[1]);
      float y = (msg[2] * 256 + msg[3]);
      float z = (msg[4] * 256 + msg[5]);

      if(x > 32768)
        x -= 65536;
      if(y > 32768)
        y -= 65536;
      if(z > 32768)
        z -= 65536;

      x /= 100;
      y /= 100;
      z /= 100;

      chimera->accel->x = x;
      chimera->accel->y = y;
      chimera->accel->z = z;
      chimera->accel->timestamp = timestamp;

      type = chimera->accel->id;
    }
    break;
    case 0x4EC:
    {
      chimera->gyro->scale = 256;
      float x = (msg[0] * 256 + msg[1]);
      float y = (msg[2] * 256 + msg[3]);
      float z = (msg[4] * 256 + msg[5]);

      if(x > 32768)
        x -= 65536;
      if(y > 32768)
        y -= 65536;
      if(z > 32768)
        z -= 65536;

      x /= 100;
      y /= 100;
      z /= 100;

      chimera->gyro->x = x;
      chimera->gyro->y = y;
      chimera->gyro->z = z;
      chimera->gyro->timestamp = timestamp;

      type = chimera->gyro->id;
    }
    break;


    default:
    return 0;
    break;
  }

  return type;
}
