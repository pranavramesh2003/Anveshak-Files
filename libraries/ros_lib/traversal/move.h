#ifndef _ROS_SERVICE_move_h
#define _ROS_SERVICE_move_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace traversal
{

static const char MOVE[] = "traversal/move";

  class moveRequest : public ros::Msg
  {
    public:
      typedef float _distance_type;
      _distance_type distance;

    moveRequest():
      distance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->distance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->distance));
     return offset;
    }

    virtual const char * getType() override { return MOVE; };
    virtual const char * getMD5() override { return "acff7fda0c683c872875f5c4b069f124"; };

  };

  class moveResponse : public ros::Msg
  {
    public:
      typedef const char* _result_type;
      _result_type result;

    moveResponse():
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

    virtual const char * getType() override { return MOVE; };
    virtual const char * getMD5() override { return "c22f2a1ed8654a0b365f1bb3f7ff2c0f"; };

  };

  class move {
    public:
    typedef moveRequest Request;
    typedef moveResponse Response;
  };

}
#endif
