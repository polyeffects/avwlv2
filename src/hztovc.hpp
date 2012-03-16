#ifndef HZTOVC_H
#define HZTOVC_H

#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class HzToVc
: public Plugin<HzToVc>
{
    int octave;
    double m_rate;
    float m_eighth, m_log2inv;
    
  public:
    HzToVc(double rate);
    void run(uint32_t nframes);
};
  
#endif