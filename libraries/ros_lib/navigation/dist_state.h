#ifndef _ROS_SERVICE_dist_state_h
#define _ROS_SERVICE_dist_state_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace navigation
{

static const char DIST_STATE[] = "navigation/dist_state";

  class dist_stateRequest : public ros::Msg
  {
    public:

    dist_stateRequest()
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

    virtual const char * getType() override { return DIST_STATE; };
    virtual const char * getMD5() override { return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class dist_stateResponse : public ros::Msg
  {
    public:
      typedef const char* _state_type;
      _state_type state;

    dist_stateResponse():
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

    virtual const char * getType() override { return DIST_STATE; };
    virtual const char * getMD5() override { return "af6d3a99f0fbeb66d3248fa4b3e675fb"; };

  };

  class dist_state {
    public:
    typedef dist_stateRequest Request;
    typedef dist_stateResponse Response;
  };

}
#endif
