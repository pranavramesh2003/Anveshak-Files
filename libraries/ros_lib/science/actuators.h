#ifndef _ROS_science_actuators_h
#define _ROS_science_actuators_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace science
{

  class actuators : public ros::Msg
  {
    public:
      typedef int16_t _stepper_type;
      _stepper_type stepper;
      typedef int16_t _linac_type;
      _linac_type linac;
      typedef int16_t _micro_type;
      _micro_type micro;
      typedef int16_t _rhino_type;
      _rhino_type rhino;
      typedef int16_t _lid_type;
      _lid_type lid;
      typedef int16_t _sht_type;
      _sht_type sht;

    actuators():
      stepper(0),
      linac(0),
      micro(0),
      rhino(0),
      lid(0),
      sht(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_stepper;
      u_stepper.real = this->stepper;
      *(outbuffer + offset + 0) = (u_stepper.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_stepper.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->stepper);
      union {
        int16_t real;
        uint16_t base;
      } u_linac;
      u_linac.real = this->linac;
      *(outbuffer + offset + 0) = (u_linac.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_linac.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->linac);
      union {
        int16_t real;
        uint16_t base;
      } u_micro;
      u_micro.real = this->micro;
      *(outbuffer + offset + 0) = (u_micro.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_micro.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->micro);
      union {
        int16_t real;
        uint16_t base;
      } u_rhino;
      u_rhino.real = this->rhino;
      *(outbuffer + offset + 0) = (u_rhino.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rhino.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->rhino);
      union {
        int16_t real;
        uint16_t base;
      } u_lid;
      u_lid.real = this->lid;
      *(outbuffer + offset + 0) = (u_lid.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lid.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->lid);
      union {
        int16_t real;
        uint16_t base;
      } u_sht;
      u_sht.real = this->sht;
      *(outbuffer + offset + 0) = (u_sht.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sht.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->sht);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_stepper;
      u_stepper.base = 0;
      u_stepper.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_stepper.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->stepper = u_stepper.real;
      offset += sizeof(this->stepper);
      union {
        int16_t real;
        uint16_t base;
      } u_linac;
      u_linac.base = 0;
      u_linac.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_linac.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->linac = u_linac.real;
      offset += sizeof(this->linac);
      union {
        int16_t real;
        uint16_t base;
      } u_micro;
      u_micro.base = 0;
      u_micro.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_micro.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->micro = u_micro.real;
      offset += sizeof(this->micro);
      union {
        int16_t real;
        uint16_t base;
      } u_rhino;
      u_rhino.base = 0;
      u_rhino.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rhino.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->rhino = u_rhino.real;
      offset += sizeof(this->rhino);
      union {
        int16_t real;
        uint16_t base;
      } u_lid;
      u_lid.base = 0;
      u_lid.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lid.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->lid = u_lid.real;
      offset += sizeof(this->lid);
      union {
        int16_t real;
        uint16_t base;
      } u_sht;
      u_sht.base = 0;
      u_sht.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sht.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->sht = u_sht.real;
      offset += sizeof(this->sht);
     return offset;
    }

    virtual const char * getType() override { return "science/actuators"; };
    virtual const char * getMD5() override { return "25eb6d63d183ea00408e6fe0331e103a"; };

  };

}
#endif
