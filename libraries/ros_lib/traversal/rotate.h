#ifndef _ROS_SERVICE_rotate_h
#define _ROS_SERVICE_rotate_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace traversal
{

static const char ROTATE[] = "traversal/rotate";

  class rotateRequest : public ros::Msg
  {
    public:
      typedef float _angle_type;
      _angle_type angle;

    rotateRequest():
      angle(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->angle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->angle));
     return offset;
    }

    virtual const char * getType() override { return ROTATE; };
    virtual const char * getMD5() override { return "4edb55038e2b888976a0c0c56935341c"; };

  };

  class rotateResponse : public ros::Msg
  {
    public:
      typedef const char* _result_type;
      _result_type result;

    rotateResponse():
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

    virtual const char * getType() override { return ROTATE; };
    virtual const char * getMD5() override { return "c22f2a1ed8654a0b365f1bb3f7ff2c0f"; };

  };

  class rotate {
    public:
    typedef rotateRequest Request;
    typedef rotateResponse Response;
  };

}
#endif
