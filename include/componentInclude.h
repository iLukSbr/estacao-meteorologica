#pragma once

/* How many LDRs? */
#define QUANTITY_OF_LDR 1

/* Comment the header to disable or uncomment to enable the component */
#include "GY511.h"
#include "GYNEO6MV2.h"
#include "HMC5883L.h"
#include "I2CServoDriver.h"
#include "KY015.h"
#include "LDR.h"
#include "MHRD.h"
#include "MHRTC2.h"
#include "MPL3115A2.h"
#include "ITGMPU6050.h"
#include "Encoder.h"
#include "TEMT6000.h"
#include "UV.h"

#include <Vector.h>

#ifndef _GY511_
   #define _GY511_ 0
#endif
#ifndef _GYNEO6MV2_
   #define _GYNEO6MV2_ 0
#endif
#ifndef _HMC5883L_
   #define _HMC5883L_ 0
#endif
#ifndef _I2CSERVODRIVER_
   #define _I2CSERVODRIVER_ 0
#endif
#ifndef _LDR_
   #define _LDR_ 0
#endif
#ifndef _KY015_
   #define _KY015_ 0
#endif
#ifndef _MHRD_
   #define _MHRD_ 0
#endif
#ifndef _MHRTC2_
   #define _MHRTC2_ 0
#endif
#ifndef _MPL3115A2_
   #define _MPL3115A2_ 0
#endif
#ifndef _ITGMPU6050_
   #define _ITGMPU6050_ 0
#endif
#ifndef _ENCODER_
   #define _ENCODER_ 0
#endif
#ifndef _TEMT6000_
   #define _TEMT6000_ 0
#endif
#ifndef _UV_
   #define _UV_ 0
#endif

#define QUANTITY_OF_COMPONENTS (_GY511_ + _GYNEO6MV2_ + _HMC5883L_ + _I2CSERVODRIVER_ + QUANTITY_OF_LDR*_LDR_ + _KY015_ + _MHRD_ + _MHRTC2_ + _MPL3115A2_ + _ITGMPU6050_ + _ENCODER_ + _TEMT6000_ + _UV_)
#define READING_DELAY 3000// (ms) Delay between readings
