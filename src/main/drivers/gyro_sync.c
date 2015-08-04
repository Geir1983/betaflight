/*
 * gyro_sync.c
 *
 *  Created on: 3 aug. 2015
 *      Author: borisb
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"
#include "build_config.h"

#include "common/axis.h"
#include "common/maths.h"

#include "drivers/sensor.h"
#include "drivers/accgyro.h"
#include "drivers/gyro_sync.h"

#include "sensors/sensors.h"
#include "sensors/acceleration.h"

#include "config/runtime_config.h"
#include "config/config.h"

extern gyro_t gyro;

uint32_t targetLooptime;
static uint8_t mpuDividerDrops;

bool getMpuDataStatus(gyro_t *gyro)
{
    bool mpuDataStatus;

    gyro->intStatus(&mpuDataStatus);
    return mpuDataStatus;
}

bool gyroSyncCheckUpdate(void) {
    return getMpuDataStatus(&gyro);
}

void gyroUpdateSampleRate(uint32_t looptime, uint8_t lpf, uint8_t syncGyroToLoop, uint8_t syncGyroToLoopDenom) {
    int gyroSamplePeriod;

    if (syncGyroToLoop) {
        if (!lpf) {
            gyroSamplePeriod = 125;

        } else {
            gyroSamplePeriod = 1000;
        }

        mpuDividerDrops  = syncGyroToLoopDenom - 1;
        targetLooptime = (mpuDividerDrops + 1) * gyroSamplePeriod;
    } else {
    	mpuDividerDrops = 0;
    	targetLooptime = looptime;
    }
}

uint8_t gyroMPU6xxxGetDividerDrops(void) {
    return mpuDividerDrops;
}
