#ifndef _ROS_SERVICE_reached_h
#define _ROS_SERVICE_reached_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace detection
{

static const char REACHED[] = "detection/reached";

  class reachedRequest : public ros::Msg
  {
    public:

    reachedRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
     return offset;
    }

    virtual const char * getType() override { return REACHED; };
    virtual const char * getMD5() override { return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class reachedResponse : public ros::Msg
  {
    public:
      typedef const char* _result_type;
      _result_type result;

    reachedResponse():
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

    virtual const char * getType() override { return REACHED; };
    virtual const char * getMD5() override { return "c22f2a1ed8654a0b365f1bb3f7ff2c0f"; };

  };

  class reached {
    public:
    typedef reachedRequest Request;
    typedef reachedResponse Response;
  };

}
#endif
