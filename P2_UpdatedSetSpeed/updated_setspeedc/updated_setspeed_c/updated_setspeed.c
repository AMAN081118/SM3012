/* --- Generated the 16/11/2025 at 9:35 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. nov. 1 5:25:8 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc updated_setspeed.ept -target c -targetpath ./updated_setspeedc --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "updated_setspeed.h"

void Updated_setspeed__updated_setspeed_reset(Updated_setspeed__updated_setspeed_mem* self) {
  self->v = true;
}

void Updated_setspeed__updated_setspeed_step(int cmd, int accel, int decel,
                                             int pause,
                                             Updated_setspeed__updated_setspeed_out* _out,
                                             Updated_setspeed__updated_setspeed_mem* self) {
  
  int v_15;
  int v_14;
  int v_13;
  int v_12;
  int v_11;
  int v_10;
  int v_9;
  int v_8;
  int v_7;
  int v_6;
  int v_5;
  int v_4;
  int v_3;
  int v_2;
  int prev_speed;
  int delta;
  v_12 = -(decel);
  if (self->v) {
    prev_speed = 0;
  } else {
    prev_speed = self->v_1;
  };
  v_10 = (prev_speed-cmd);
  v_11 = -(v_10);
  v_8 = (prev_speed-cmd);
  v_9 = (v_8<decel);
  if (v_9) {
    v_13 = v_11;
  } else {
    v_13 = v_12;
  };
  v_7 = (prev_speed>cmd);
  if (v_7) {
    v_14 = v_13;
  } else {
    v_14 = 0;
  };
  v_5 = (cmd-prev_speed);
  v_3 = (cmd-prev_speed);
  v_4 = (v_3<accel);
  if (v_4) {
    v_6 = v_5;
  } else {
    v_6 = accel;
  };
  v_2 = (prev_speed<cmd);
  if (v_2) {
    v_15 = v_6;
  } else {
    v_15 = v_14;
  };
  if (pause) {
    delta = 0;
  } else {
    delta = v_15;
  };
  _out->effective_delta = delta;
  _out->speed = (prev_speed+delta);
  self->v_1 = _out->speed;
  self->v = false;;
}

void Updated_setspeed__main_reset(Updated_setspeed__main_mem* self) {
  Updated_setspeed__updated_setspeed_reset(&self->updated_setspeed);
}

void Updated_setspeed__main_step(int cmd_in, int accel_in, int decel_in,
                                 int pause_in,
                                 Updated_setspeed__main_out* _out,
                                 Updated_setspeed__main_mem* self) {
  Updated_setspeed__updated_setspeed_out Updated_setspeed__updated_setspeed_out_st;
  Updated_setspeed__updated_setspeed_step(cmd_in, accel_in, decel_in,
                                          pause_in,
                                          &Updated_setspeed__updated_setspeed_out_st,
                                          &self->updated_setspeed);
  _out->speed_out = Updated_setspeed__updated_setspeed_out_st.speed;
  _out->delta_out = Updated_setspeed__updated_setspeed_out_st.effective_delta;
}

