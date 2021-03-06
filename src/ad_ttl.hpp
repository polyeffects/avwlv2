#ifndef avw_lv__ad_ttl_hpp
#define avw_lv__ad_ttl_hpp


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

/* <http://avwlv2.sourceforge.net/plugins/avw/ad> */

static const char p_uri[] = "http://avwlv2.sourceforge.net/plugins/avw/ad";

enum p_port_enum {
  p_cvin,
  p_detuneAmplitude,
  p_detuneModulation,
  p_detuneRate,
  p_driftAmplitude,
  p_driftModulation,
  p_driftRate,
  p_cvout0,
  p_cvout1,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -1, 1, 0, 0, 0, 0 }, 
  { 0, 0.084, 0.005, 0, 0, 0 }, 
  { 0.01, 1, 0.01, 0, 0, 0 }, 
  { 0.01, 10, 1, 0, 0, 0 }, 
  { 0, 0.084, 0.005, 0, 0, 0 }, 
  { 0.01, 1, 0.01, 0, 0, 0 }, 
  { 0.01, 10, 3, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* avw_lv__ad_ttl_hpp */
