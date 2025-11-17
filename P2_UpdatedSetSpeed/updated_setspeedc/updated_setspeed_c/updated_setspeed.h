/* --- Generated the 16/11/2025 at 9:35 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. nov. 1 5:25:8 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc updated_setspeed.ept -target c -targetpath ./updated_setspeedc --- */

#ifndef UPDATED_SETSPEED_H
#define UPDATED_SETSPEED_H

#include "updated_setspeed_types.h"
typedef struct Updated_setspeed__updated_setspeed_mem {
  int v_1;
  int v;
} Updated_setspeed__updated_setspeed_mem;

typedef struct Updated_setspeed__updated_setspeed_out {
  int speed;
  int effective_delta;
} Updated_setspeed__updated_setspeed_out;

void Updated_setspeed__updated_setspeed_reset(Updated_setspeed__updated_setspeed_mem* self);

void Updated_setspeed__updated_setspeed_step(int cmd, int accel, int decel,
                                             int pause,
                                             Updated_setspeed__updated_setspeed_out* _out,
                                             Updated_setspeed__updated_setspeed_mem* self);

typedef struct Updated_setspeed__main_mem {
  Updated_setspeed__updated_setspeed_mem updated_setspeed;
} Updated_setspeed__main_mem;

typedef struct Updated_setspeed__main_out {
  int speed_out;
  int delta_out;
} Updated_setspeed__main_out;

void Updated_setspeed__main_reset(Updated_setspeed__main_mem* self);

void Updated_setspeed__main_step(int cmd_in, int accel_in, int decel_in,
                                 int pause_in,
                                 Updated_setspeed__main_out* _out,
                                 Updated_setspeed__main_mem* self);

#endif // UPDATED_SETSPEED_H
