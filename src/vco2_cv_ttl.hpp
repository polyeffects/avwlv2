#ifndef avw_lv__vco__cv_ttl_hpp
#define avw_lv__vco__cv_ttl_hpp


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

/* <http://avwlv2.sourceforge.net/plugins/avw/vco2_cv> */

static const char p_uri[] = "http://avwlv2.sourceforge.net/plugins/avw/vco2_cv";

enum p_port_enum {
  p_freq,
  p_expFM,
  p_linFM,
  p_pwPort,
  p_waveForm,
  p_octave,
  p_tune,
  p_semitone,
  p_pw0,
  p_pwGain,
  p_edge,
  p_phi0,
  p_expFMGain,
  p_linFMGain,
  p_out,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 0, 6, 0, 0, 0, 0 }, 
  { 0, 6, 3, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 12, 0, 0, 0, 0 }, 
  { 0.1, 0.9, 0.5, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 1, 10, 1, 0, 0, 0 }, 
  { 0, 6.283, 0, 0, 0, 0 }, 
  { 0, 10, 0, 0, 0, 0 }, 
  { 0, 10, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* avw_lv__vco__cv_ttl_hpp */
