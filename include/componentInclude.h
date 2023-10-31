#pragma once

/* Comment the header to disable or uncomment to enable the component */
// #include "CD74HC4067.h"
// #include "Encoder.h"
// #include "GYNEO6MV2.h"
// #include "KY015.h"
// #include "KY021.h"
// #include "KY026.h"
// #include "MHRTC2.h"
// #include "MPL3115A2.h"
// #include "Relay.h"
// #include "SDReaderWriter.h"
#include "SolarTracker.h"
// #include "TEMT6000.h"
// #include "UV.h"

#define READING_DELAY 3000// (ms) Delay between readings

#include <Vector.h>

#ifndef _CD74HC4067_
   #define _CD74HC4067_ 0
#endif
#ifndef _ENCODER_
   #define _ENCODER_ 0
#endif
#ifndef _GYNEO6MV2_
   #define _GYNEO6MV2_ 0
#endif
#ifndef _KY015_
   #define _KY015_ 0
#endif
#ifndef _KY021_
   #define _KY021_ 0
#endif
#ifndef _KY036_
   #define _KY036_ 0
#endif
#ifndef _MHRTC2_
   #define _MHRTC2_ 0
#endif
#ifndef _MICRO_SD_READER_WRITER_
   #define _MICRO_SD_READER_WRITER_ 0
#endif
#ifndef _MPL3115A2_
   #define _MPL3115A2_ 0
#endif
#ifndef _RELAY_
   #define _RELAY_ 0
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

#define QUANTITY_OF_COMPONENTS (_CD74HC4067_ + _ENCODER_ + _GYNEO6MV2_ + _KY015_ + _KY021_ + _KY036_ + _MHRTC2_ + _MICRO_SD_READER_WRITER_ + _MPL3115A2_ + _RELAY_ + _SOLAR_TRACKER_ + _TEMT6000_ + _UV_)