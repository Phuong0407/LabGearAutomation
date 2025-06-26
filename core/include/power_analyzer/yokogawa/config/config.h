#ifndef include_power_analyzer_yokogawa_config_config_h
#define include_power_analyzer_yokogawa_config_config_h

#ifdef wt500
#define __wt500_harmonic_measurement
#define __wt500_delta_computation
#define __wt500_usbtmc
#define __wt500_gpib
#define __wt500_vxi11
#endif

#endif // core_config_yokogawa_h