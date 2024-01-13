#ifndef _ROS_detection_detection_h
#define _ROS_detection_detection_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace detection
{

  class detection : public ros::Msg
  {
    public:
      typedef uint16_t _xmin_type;
      _xmin_type xmin;
      typedef uint16_t _ymin_type;
      _ymin_type ymin;
      typedef uint16_t _xmax_type;
      _xmax_type xmax;
      typedef uint16_t _ymax_type;
      _ymax_type ymax;
      typedef float _score_type;
      _score_type score;
      typedef uint8_t _category_type;
      _category_type category;

    detection():
      xmin(0),
      ymin(0),
      xmax(0),
      ymax(0),
      score(0),
      category(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->xmin >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->xmin >> (8 * 1)) & 0xFF;
      offset += sizeof(this->xmin);
      *(outbuffer + offset + 0) = (this->ymin >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->ymin >> (8 * 1)) & 0xFF;
      offset += sizeof(this->ymin);
      *(outbuffer + offset + 0) = (this->xmax >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->xmax >> (8 * 1)) & 0xFF;
      offset += sizeof(this->xmax);
      *(outbuffer + offset + 0) = (this->ymax >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->ymax >> (8 * 1)) & 0xFF;
      offset += sizeof(this->ymax);
      union {
        float real;
        uint32_t base;
      } u_score;
      u_score.real = this->score;
      *(outbuffer + offset + 0) = (u_score.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_score.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_score.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_score.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->score);
      *(outbuffer + offset + 0) = (this->category >> (8 * 0)) & 0xFF;
      offset += sizeof(this->category);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      this->xmin =  ((uint16_t) (*(inbuffer + offset)));
      this->xmin |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->xmin);
      this->ymin =  ((uint16_t) (*(inbuffer + offset)));
      this->ymin |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->ymin);
      this->xmax =  ((uint16_t) (*(inbuffer + offset)));
      this->xmax |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->xmax);
      this->ymax =  ((uint16_t) (*(inbuffer + offset)));
      this->ymax |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->ymax);
      union {
        float real;
        uint32_t base;
      } u_score;
      u_score.base = 0;
      u_score.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_score.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_score.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_score.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->score = u_score.real;
      offset += sizeof(this->score);
      this->category =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->category);
     return offset;
    }

    virtual const char * getType() override { return "detection/detection"; };
    virtual const char * getMD5() override { return "749131da678d2cc04e6f077d4ec426e4"; };

  };

}
#endif
