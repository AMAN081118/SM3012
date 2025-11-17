/* --- Generated the 16/11/2025 at 12:19 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. nov. 1 5:25:8 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc railroad1.ept -target c -targetpath ./railroad1c --- */

#ifndef RAILROAD1_H
#define RAILROAD1_H

#include "railroad1_types.h"
typedef struct Railroad1__train_node_mem {
  Railroad1__st ck;
  int v_1;
  int v;
  int pnr;
} Railroad1__train_node_mem;

typedef struct Railroad1__train_node_out {
  int st;
  int req;
  int on_bridge;
} Railroad1__train_node_out;

void Railroad1__train_node_reset(Railroad1__train_node_mem* self);

void Railroad1__train_node_step(int approach, int grant_in,
                                Railroad1__train_node_out* _out,
                                Railroad1__train_node_mem* self);

typedef struct Railroad1__controller1_mem {
  int v_3;
  int v;
} Railroad1__controller1_mem;

typedef struct Railroad1__controller1_out {
  int gw;
  int ge;
} Railroad1__controller1_out;

void Railroad1__controller1_reset(Railroad1__controller1_mem* self);

void Railroad1__controller1_step(int req_w, int req_e, int onw, int one,
                                 Railroad1__controller1_out* _out,
                                 Railroad1__controller1_mem* self);

typedef struct Railroad1__railroad1_mem {
  int v_17;
  int v_16;
  int v_15;
  int v;
  Railroad1__controller1_mem controller1;
  Railroad1__train_node_mem train_node;
  Railroad1__train_node_mem train_node_1;
} Railroad1__railroad1_mem;

typedef struct Railroad1__railroad1_out {
  int sw;
  int se;
  int gw;
  int ge;
} Railroad1__railroad1_out;

void Railroad1__railroad1_reset(Railroad1__railroad1_mem* self);

void Railroad1__railroad1_step(int aw, int ae,
                               Railroad1__railroad1_out* _out,
                               Railroad1__railroad1_mem* self);

typedef struct Railroad1__main_mem {
  Railroad1__railroad1_mem railroad1;
} Railroad1__main_mem;

typedef struct Railroad1__main_out {
  int sw;
  int se;
  int gw;
  int ge;
} Railroad1__main_out;

void Railroad1__main_reset(Railroad1__main_mem* self);

void Railroad1__main_step(int aw, int ae, Railroad1__main_out* _out,
                          Railroad1__main_mem* self);

#endif // RAILROAD1_H
