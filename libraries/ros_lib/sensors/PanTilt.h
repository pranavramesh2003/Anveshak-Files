#ifndef _ROS_sensors_PanTilt_h
#define _ROS_sensors_PanTilt_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace sensors
{

  class PanTilt : public ros::Msg
  {
    public:
      typedef float _pan_type;
      _pan_type pan;
      typedef float _tilt_type;
      _tilt_type tilt;
      typedef bool _rel_type;
      _rel_type rel;

    PanTilt():
      pan(0),
      tilt(0),
      rel(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_pan;
      u_pan.real = this->pan;
      *(outbuffer + offset + 0) = (u_pan.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pan.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pan.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pan.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pan);
      union {
        float real;
        uint32_t base;
      } u_tilt;
      u_tilt.real = this->tilt;
      *(outbuffer + offset + 0) = (u_tilt.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_tilt.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_tilt.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_tilt.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->tilt);
      union {
        bool real;
        uint8_t base;
      } u_rel;
      u_rel.real = this->rel;
      *(outbuffer + offset + 0) = (u_rel.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->rel);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_pan;
      u_pan.base = 0;
      u_pan.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pan.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pan.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pan.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pan = u_pan.real;
      offset += sizeof(this->pan);
      union {
        float real;
        uint32_t base;
      } u_tilt;
      u_tilt.base = 0;
      u_tilt.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_tilt.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_tilt.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_tilt.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->tilt = u_tilt.real;
      offset += sizeof(this->tilt);
      union {
        bool real;
        uint8_t base;
      } u_rel;
      u_rel.base = 0;
      u_rel.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->rel = u_rel.real;
      offset += sizeof(this->rel);
     return offset;
    }

    virtual const char * getType() override { return "sensors/PanTilt"; };
    virtual const char * getMD5() override { return "c8ce171acfa745a5b6ceb9bc3cf0e1d0"; };

  };

}
#endif
