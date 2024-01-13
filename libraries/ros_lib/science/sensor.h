#ifndef _ROS_science_sensor_h
#define _ROS_science_sensor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace science
{

  class sensor : public ros::Msg
  {
    public:
      typedef float _tsl_full_type;
      _tsl_full_type tsl_full;
      typedef float _lps_temp_type;
      _lps_temp_type lps_temp;
      typedef float _lps_pressure_type;
      _lps_pressure_type lps_pressure;
      typedef float _sht_humidity_type;
      _sht_humidity_type sht_humidity;
      typedef float _sht_temp_type;
      _sht_temp_type sht_temp;

    sensor():
      tsl_full(0),
      lps_temp(0),
      lps_pressure(0),
      sht_humidity(0),
      sht_temp(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_tsl_full;
      u_tsl_full.real = this->tsl_full;
      *(outbuffer + offset + 0) = (u_tsl_full.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_tsl_full.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_tsl_full.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_tsl_full.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->tsl_full);
      union {
        float real;
        uint32_t base;
      } u_lps_temp;
      u_lps_temp.real = this->lps_temp;
      *(outbuffer + offset + 0) = (u_lps_temp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lps_temp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_lps_temp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_lps_temp.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lps_temp);
      union {
        float real;
        uint32_t base;
      } u_lps_pressure;
      u_lps_pressure.real = this->lps_pressure;
      *(outbuffer + offset + 0) = (u_lps_pressure.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lps_pressure.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_lps_pressure.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_lps_pressure.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lps_pressure);
      union {
        float real;
        uint32_t base;
      } u_sht_humidity;
      u_sht_humidity.real = this->sht_humidity;
      *(outbuffer + offset + 0) = (u_sht_humidity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sht_humidity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sht_humidity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sht_humidity.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sht_humidity);
      union {
        float real;
        uint32_t base;
      } u_sht_temp;
      u_sht_temp.real = this->sht_temp;
      *(outbuffer + offset + 0) = (u_sht_temp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sht_temp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sht_temp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sht_temp.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sht_temp);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_tsl_full;
      u_tsl_full.base = 0;
      u_tsl_full.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_tsl_full.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_tsl_full.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_tsl_full.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->tsl_full = u_tsl_full.real;
      offset += sizeof(this->tsl_full);
      union {
        float real;
        uint32_t base;
      } u_lps_temp;
      u_lps_temp.base = 0;
      u_lps_temp.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lps_temp.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_lps_temp.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_lps_temp.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->lps_temp = u_lps_temp.real;
      offset += sizeof(this->lps_temp);
      union {
        float real;
        uint32_t base;
      } u_lps_pressure;
      u_lps_pressure.base = 0;
      u_lps_pressure.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_lps_pressure.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_lps_pressure.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_lps_pressure.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->lps_pressure = u_lps_pressure.real;
      offset += sizeof(this->lps_pressure);
      union {
        float real;
        uint32_t base;
      } u_sht_humidity;
      u_sht_humidity.base = 0;
      u_sht_humidity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sht_humidity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sht_humidity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sht_humidity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->sht_humidity = u_sht_humidity.real;
      offset += sizeof(this->sht_humidity);
      union {
        float real;
        uint32_t base;
      } u_sht_temp;
      u_sht_temp.base = 0;
      u_sht_temp.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sht_temp.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sht_temp.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sht_temp.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->sht_temp = u_sht_temp.real;
      offset += sizeof(this->sht_temp);
     return offset;
    }

    virtual const char * getType() override { return "science/sensor"; };
    virtual const char * getMD5() override { return "f03c616c12fbcd715e685d60bb04a3dc"; };

  };

}
#endif
