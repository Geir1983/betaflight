/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define GYRO_I_MAX 256                      // Gyro I limiter

typedef enum {
    PIDROLL,
    PIDPITCH,
    PIDYAW,
    PIDALT,
    PIDPOS,
    PIDPOSR,
    PIDNAVR,
    PIDLEVEL,
    PIDMAG,
    PIDVEL,
    PID_ITEM_COUNT
} pidIndex_e;

typedef enum {
    PID_CONTROLLER_REWRITE = 1,
    PID_CONTROLLER_LUX_FLOAT,
	PID_COUNT
} pidControllerType_e;

#define IS_PID_CONTROLLER_FP_BASED(pidController) (pidController == 2)

typedef struct pidProfile_s {
    uint8_t pidController;                  // 1 = rewrite, 2 = luxfloat

    uint8_t P8[PID_ITEM_COUNT];
    uint8_t I8[PID_ITEM_COUNT];
    uint8_t D8[PID_ITEM_COUNT];

    float P_f[3];                           // float p i and d factors for lux float pid controller
    float I_f[3];
    float D_f[3];
    float A_level;
    float H_level;
    uint8_t H_sensitivity;

    uint8_t dterm_cut_hz;                   // (default 17Hz, Range 1-50Hz) Used for PT1 element in PID1, PID2 and PID5
    uint8_t yaw_pterm_cut_hz;              // Yaw P low pass filter for pterm. very usefull on noisy setups

#ifdef GTUNE
    uint8_t  gtune_lolimP[3];               // [0..200] Lower limit of P during G tune
    uint8_t  gtune_hilimP[3];               // [0..200] Higher limit of P during G tune. 0 Disables tuning for that axis.
    uint8_t  gtune_pwr;                     // [0..10] Strength of adjustment
    uint16_t gtune_settle_time;             // [200..1000] Settle time in ms
    uint8_t  gtune_average_cycles;          // [8..128] Number of looptime cycles used for gyro average calculation
#endif
} pidProfile_t;

extern int16_t axisPID[XYZ_AXIS_COUNT];
extern int32_t axisPID_P[3], axisPID_I[3], axisPID_D[3];

void pidSetController(pidControllerType_e type);
void pidResetErrorAngle(void);
void pidResetErrorGyro(void);

