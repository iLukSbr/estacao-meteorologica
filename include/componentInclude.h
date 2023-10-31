#pragma once

/* Comment the header to disable or uncomment to enable the component */
// #include "Demultiplexer.h"
// #include "Encoder.h"
// #include "GY511.h"
// #include "GYNEO6MV2.h"
// #include "HMC5883L.h"
// #include "KY015.h"
// #include "KY021.h"
// #include "MHRTC2.h"
// #include "MPL3115A2.h"
#include "SolarTracker.h"
// #include "TEMT6000.h"
// #include "UV.h"

#define READING_DELAY 3000// (ms) Delay between readings

#include <Vector.h>

#ifndef _DEMULTIPLEXER_
   #define _DEMULTIPLEXER_ 0
#ifndef _ENCODER_
   #define _ENCODER_ 0
#endif
#ifndef _GY511_
   #define _GY511_ 0
#endif
#ifndef _GYNEO6MV2_
   #define _GYNEO6MV2_ 0
#endif
#ifndef _HMC5883L_
   #define _HMC5883L_ 0
#endif
#ifndef _KY015_
   #define _KY015_ 0
#endif
#ifndef _KY021_
   #define _KY021_ 0
#endif
#ifndef _MHRTC2_
   #define _MHRTC2_ 0
#endif
#ifndef _MPL3115A2_
   #define _MPL3115A2_ 0
#endif
#ifndef _SOLAR_TRACKER_
   #define _SOLAR_TRACKER_ 0
#endif
#ifndef _TEMT6000_
   #define _TEMT6000_ 0
#endif
#ifndef _UV_
   #define _UV_ 0
#endif

#define QUANTITY_OF_COMPONENTS (_DEMULTIPLEXER_ + _ENCODER_ + _GY511_ + _GYNEO6MV2_ + _HMC5883L_ + _KY015_ + _KY021_ + _MHRTC2_ + _MPL3115A2_ + _SOLAR_TRACKER_ + _TEMT6000_ + _UV_)