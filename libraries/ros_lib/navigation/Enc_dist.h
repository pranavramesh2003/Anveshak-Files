#ifndef _ROS_navigation_Enc_dist_h
#define _ROS_navigation_Enc_dist_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace navigation
{

  class Enc_dist : public ros::Msg
  {
    public:
      typedef float _dist_type;
      _dist_type dist;

    Enc_dist():
      dist(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->dist);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->dist));
     return offset;
    }

    virtual const char * getType() override { return "navigation/Enc_dist"; };
    virtual const char * getMD5() override { return "3f4fece6412db25720b2bab9f80b3473"; };

  };

}
#endif
