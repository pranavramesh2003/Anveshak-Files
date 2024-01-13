#ifndef _ROS_navigation_Goal_h
#define _ROS_navigation_Goal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace navigation
{

  class Goal : public ros::Msg
  {
    public:
      typedef float _bearing_type;
      _bearing_type bearing;
      typedef float _distance_type;
      _distance_type distance;

    Goal():
      bearing(0),
      distance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->bearing);
      offset += serializeAvrFloat64(outbuffer + offset, this->distance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->bearing));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->distance));
     return offset;
    }

    virtual const char * getType() override { return "navigation/Goal"; };
    virtual const char * getMD5() override { return "e6b9899956f1eacd3991a6d711941249"; };

  };

}
#endif
