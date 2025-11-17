/* --- Generated the 16/11/2025 at 6:59 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. nov. 1 5:25:8 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc setspeed.ept -target c -targetpath ./setspeedc --- */

#ifndef SETSPEED_H
#define SETSPEED_H

#include "setspeed_types.h"
typedef struct Setspeed__setspeed_mem {
  int v_1;
  int v;
} Setspeed__setspeed_mem;

typedef struct Setspeed__setspeed_out {
  int speed;
} Setspeed__setspeed_out;

void Setspeed__setspeed_reset(Setspeed__setspeed_mem* self);

void Setspeed__setspeed_step(int cmd, int accel, int decel,
                             Setspeed__setspeed_out* _out,
                             Setspeed__setspeed_mem* self);

typedef struct Setspeed__main_mem {
  Setspeed__setspeed_mem setspeed;
} Setspeed__main_mem;

typedef struct Setspeed__main_out {
  int speed_out;
} Setspeed__main_out;

void Setspeed__main_reset(Setspeed__main_mem* self);

void Setspeed__main_step(int cmd_in, int accel_in, int decel_in,
                         Setspeed__main_out* _out, Setspeed__main_mem* self);

#endif // SETSPEED_H
