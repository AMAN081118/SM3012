/* --- Generated the 16/11/2025 at 12:57 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. nov. 1 5:25:8 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc railroad2.ept -target c -targetpath ./railroad2c --- */

#ifndef RAILROAD2_H
#define RAILROAD2_H

#include "railroad2_types.h"
typedef struct Railroad2__train_node_mem {
  int v_4;
  int v_1;
  Railroad2__st ck;
  int pnr;
} Railroad2__train_node_mem;

typedef struct Railroad2__train_node_out {
  int st;
  int req;
  int on_bridge;
} Railroad2__train_node_out;

void Railroad2__train_node_reset(Railroad2__train_node_mem* self);

void Railroad2__train_node_step(int approach, int grant_in,
                                Railroad2__train_node_out* _out,
                                Railroad2__train_node_mem* self);

typedef struct Railroad2__controller2_mem {
  int v_7;
  int v_6;
  int v_5;
  int v;
} Railroad2__controller2_mem;

typedef struct Railroad2__controller2_out {
  int grant_w;
  int grant_e;
} Railroad2__controller2_out;

void Railroad2__controller2_reset(Railroad2__controller2_mem* self);

void Railroad2__controller2_step(int req_w, int req_e, int onw, int one,
                                 Railroad2__controller2_out* _out,
                                 Railroad2__controller2_mem* self);

typedef struct Railroad2__railroad2_mem {
  int v_24;
  int v_23;
  int v_22;
  int v;
  Railroad2__controller2_mem controller2;
  Railroad2__train_node_mem train_node;
  Railroad2__train_node_mem train_node_1;
} Railroad2__railroad2_mem;

typedef struct Railroad2__railroad2_out {
  int st_w;
  int st_e;
  int grant_w;
  int grant_e;
} Railroad2__railroad2_out;

void Railroad2__railroad2_reset(Railroad2__railroad2_mem* self);

void Railroad2__railroad2_step(int approach_w, int approach_e,
                               Railroad2__railroad2_out* _out,
                               Railroad2__railroad2_mem* self);

typedef struct Railroad2__main_mem {
  Railroad2__railroad2_mem railroad2;
} Railroad2__main_mem;

typedef struct Railroad2__main_out {
  int st_w_out;
  int st_e_out;
  int gw_out;
  int ge_out;
} Railroad2__main_out;

void Railroad2__main_reset(Railroad2__main_mem* self);

void Railroad2__main_step(int approach_w_in, int approach_e_in,
                          Railroad2__main_out* _out,
                          Railroad2__main_mem* self);

#endif // RAILROAD2_H
