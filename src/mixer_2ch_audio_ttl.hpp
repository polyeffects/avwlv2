#ifndef avw_lv__mixer__ch_audio_ttl_hpp
#define avw_lv__mixer__ch_audio_ttl_hpp


#ifndef PEG_STRUCT
#define PEG_STRUCT
typedef struct {
  float min;
  float max;
  float default_value;
  char toggled;
  char integer;
  char logarithmic;
} peg_data_t;
#endif

/* <http://avwlv2.sourceforge.net/plugins/avw/mixer_2ch_audio> */

static const char p_uri[] = "http://avwlv2.sourceforge.net/plugins/avw/mixer_2ch_audio";

enum p_port_enum {
  p_in1,
  p_in2,
  p_gain,
  p_volume1,
  p_volume2,
  p_out,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { 0, 2, 1, 0, 0, 0 }, 
  { 0, 2, 1, 0, 0, 0 }, 
  { 0, 2, 1, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
};


#endif /* avw_lv__mixer__ch_audio_ttl_hpp */
