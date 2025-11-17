/* --- Generated the 16/11/2025 at 6:59 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. nov. 1 5:25:8 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc setspeed.ept -target c -targetpath ./setspeedc --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "setspeed.h"

void Setspeed__setspeed_reset(Setspeed__setspeed_mem* self) {
  self->v = true;
}

void Setspeed__setspeed_step(int cmd, int accel, int decel,
                             Setspeed__setspeed_out* _out,
                             Setspeed__setspeed_mem* self) {
  
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
    delta = v_6;
  } else {
    delta = v_14;
  };
  _out->speed = (prev_speed+delta);
  self->v_1 = _out->speed;
  self->v = false;;
}

void Setspeed__main_reset(Setspeed__main_mem* self) {
  Setspeed__setspeed_reset(&self->setspeed);
}

void Setspeed__main_step(int cmd_in, int accel_in, int decel_in,
                         Setspeed__main_out* _out, Setspeed__main_mem* self) {
  Setspeed__setspeed_out Setspeed__setspeed_out_st;
  Setspeed__setspeed_step(cmd_in, accel_in, decel_in,
                          &Setspeed__setspeed_out_st, &self->setspeed);
  _out->speed_out = Setspeed__setspeed_out_st.speed;
}

