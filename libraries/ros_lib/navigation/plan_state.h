#ifndef _ROS_SERVICE_plan_state_h
#define _ROS_SERVICE_plan_state_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace navigation
{

static const char PLAN_STATE[] = "navigation/plan_state";

  class plan_stateRequest : public ros::Msg
  {
    public:
      typedef int8_t _pause_type;
      _pause_type pause;
      typedef int8_t _contin_type;
      _contin_type contin;
      typedef int8_t _rst_type;
      _rst_type rst;

    plan_stateRequest():
      pause(0),
      contin(0),
      rst(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_pause;
      u_pause.real = this->pause;
      *(outbuffer + offset + 0) = (u_pause.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pause);
      union {
        int8_t real;
        uint8_t base;
      } u_contin;
      u_contin.real = this->contin;
      *(outbuffer + offset + 0) = (u_contin.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->contin);
      union {
        int8_t real;
        uint8_t base;
      } u_rst;
      u_rst.real = this->rst;
      *(outbuffer + offset + 0) = (u_rst.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->rst);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_pause;
      u_pause.base = 0;
      u_pause.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pause = u_pause.real;
      offset += sizeof(this->pause);
      union {
        int8_t real;
        uint8_t base;
      } u_contin;
      u_contin.base = 0;
      u_contin.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->contin = u_contin.real;
      offset += sizeof(this->contin);
      union {
        int8_t real;
        uint8_t base;
      } u_rst;
      u_rst.base = 0;
      u_rst.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->rst = u_rst.real;
      offset += sizeof(this->rst);
     return offset;
    }

    virtual const char * getType() override { return PLAN_STATE; };
    virtual const char * getMD5() override { return "3784a326caf7609ed9090b60e51420a0"; };

  };

  class plan_stateResponse : public ros::Msg
  {
    public:
      typedef const char* _state_type;
      _state_type state;

    plan_stateResponse():
      state("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_state = strlen(this->state);
      varToArr(outbuffer + offset, length_state);
      offset += 4;
      memcpy(outbuffer + offset, this->state, length_state);
      offset += length_state;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_state;
      arrToVar(length_state, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_state; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_state-1]=0;
      this->state = (char *)(inbuffer + offset-1);
      offset += length_state;
     return offset;
    }

    virtual const char * getType() override { return PLAN_STATE; };
    virtual const char * getMD5() override { return "af6d3a99f0fbeb66d3248fa4b3e675fb"; };

  };

  class plan_state {
    public:
    typedef plan_stateRequest Request;
    typedef plan_stateResponse Response;
  };

}
#endif
