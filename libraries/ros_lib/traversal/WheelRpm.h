#ifndef _ROS_traversal_WheelRpm_h
#define _ROS_traversal_WheelRpm_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace traversal
{

  class WheelRpm : public ros::Msg
  {
    public:
      typedef int16_t _vel_type;
      _vel_type vel;
      typedef int16_t _omega_type;
      _omega_type omega;
      typedef bool _hb_type;
      _hb_type hb;

    WheelRpm():
      vel(0),
      omega(0),
      hb(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_vel;
      u_vel.real = this->vel;
      *(outbuffer + offset + 0) = (u_vel.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_vel.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->vel);
      union {
        int16_t real;
        uint16_t base;
      } u_omega;
      u_omega.real = this->omega;
      *(outbuffer + offset + 0) = (u_omega.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_omega.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->omega);
      union {
        bool real;
        uint8_t base;
      } u_hb;
      u_hb.real = this->hb;
      *(outbuffer + offset + 0) = (u_hb.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->hb);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_vel;
      u_vel.base = 0;
      u_vel.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_vel.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->vel = u_vel.real;
      offset += sizeof(this->vel);
      union {
        int16_t real;
        uint16_t base;
      } u_omega;
      u_omega.base = 0;
      u_omega.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_omega.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->omega = u_omega.real;
      offset += sizeof(this->omega);
      union {
        bool real;
        uint8_t base;
      } u_hb;
      u_hb.base = 0;
      u_hb.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->hb = u_hb.real;
      offset += sizeof(this->hb);
     return offset;
    }

    virtual const char * getType() override { return "traversal/WheelRpm"; };
    virtual const char * getMD5() override { return "524ce3b1091d34ce15083042edf1da49"; };

  };

}
#endif
