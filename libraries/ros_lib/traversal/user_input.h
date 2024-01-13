#ifndef _ROS_SERVICE_user_input_h
#define _ROS_SERVICE_user_input_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace traversal
{

static const char USER_INPUT[] = "traversal/user_input";

  class user_inputRequest : public ros::Msg
  {
    public:
      typedef int16_t _active_input_type;
      _active_input_type active_input;

    user_inputRequest():
      active_input(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_active_input;
      u_active_input.real = this->active_input;
      *(outbuffer + offset + 0) = (u_active_input.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_active_input.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->active_input);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_active_input;
      u_active_input.base = 0;
      u_active_input.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_active_input.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->active_input = u_active_input.real;
      offset += sizeof(this->active_input);
     return offset;
    }

    virtual const char * getType() override { return USER_INPUT; };
    virtual const char * getMD5() override { return "27b61c18d29c1ce9cab85d9dea52400f"; };

  };

  class user_inputResponse : public ros::Msg
  {
    public:
      typedef const char* _result_type;
      _result_type result;

    user_inputResponse():
      result("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_result = strlen(this->result);
      varToArr(outbuffer + offset, length_result);
      offset += 4;
      memcpy(outbuffer + offset, this->result, length_result);
      offset += length_result;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_result;
      arrToVar(length_result, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_result; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_result-1]=0;
      this->result = (char *)(inbuffer + offset-1);
      offset += length_result;
     return offset;
    }

    virtual const char * getType() override { return USER_INPUT; };
    virtual const char * getMD5() override { return "c22f2a1ed8654a0b365f1bb3f7ff2c0f"; };

  };

  class user_input {
    public:
    typedef user_inputRequest Request;
    typedef user_inputResponse Response;
  };

}
#endif
