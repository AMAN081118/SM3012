/* --- Generated the 16/11/2025 at 12:19 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. nov. 1 5:25:8 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc railroad1.ept -target c -targetpath ./railroad1c --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "railroad1.h"

void Railroad1__train_node_reset(Railroad1__train_node_mem* self) {
  self->pnr = false;
  self->ck = Railroad1__St_Away;
  self->v = true;
}

void Railroad1__train_node_step(int approach, int grant_in,
                                Railroad1__train_node_out* _out,
                                Railroad1__train_node_mem* self) {
  
  int v_2;
  int nr_St_Bridge;
  Railroad1__st ns_St_Bridge;
  int next_tcount_St_Bridge;
  int on_bridge_St_Bridge;
  int req_St_Bridge;
  int st_St_Bridge;
  int nr_St_Wait;
  Railroad1__st ns_St_Wait;
  int next_tcount_St_Wait;
  int on_bridge_St_Wait;
  int req_St_Wait;
  int st_St_Wait;
  int nr_St_Away;
  Railroad1__st ns_St_Away;
  int next_tcount_St_Away;
  int on_bridge_St_Away;
  int req_St_Away;
  int st_St_Away;
  Railroad1__st ns;
  int r;
  int nr;
  int tcount;
  int next_tcount;
  r = self->pnr;
  if (self->v) {
    tcount = 0;
  } else {
    tcount = self->v_1;
  };
  switch (self->ck) {
    case Railroad1__St_Away:
      next_tcount_St_Away = 0;
      on_bridge_St_Away = false;
      req_St_Away = false;
      st_St_Away = 0;
      if (approach) {
        nr_St_Away = true;
        ns_St_Away = Railroad1__St_Wait;
      } else {
        nr_St_Away = false;
        ns_St_Away = Railroad1__St_Away;
      };
      _out->st = st_St_Away;
      _out->req = req_St_Away;
      _out->on_bridge = on_bridge_St_Away;
      next_tcount = next_tcount_St_Away;
      ns = ns_St_Away;
      nr = nr_St_Away;
      break;
    case Railroad1__St_Wait:
      next_tcount_St_Wait = 0;
      on_bridge_St_Wait = false;
      req_St_Wait = true;
      st_St_Wait = 1;
      if (grant_in) {
        nr_St_Wait = true;
        ns_St_Wait = Railroad1__St_Bridge;
      } else {
        nr_St_Wait = false;
        ns_St_Wait = Railroad1__St_Wait;
      };
      _out->st = st_St_Wait;
      _out->req = req_St_Wait;
      _out->on_bridge = on_bridge_St_Wait;
      next_tcount = next_tcount_St_Wait;
      ns = ns_St_Wait;
      nr = nr_St_Wait;
      break;
    case Railroad1__St_Bridge:
      next_tcount_St_Bridge = (tcount+1);
      on_bridge_St_Bridge = true;
      req_St_Bridge = false;
      st_St_Bridge = 2;
      v_2 = (tcount>=2);
      if (v_2) {
        nr_St_Bridge = true;
        ns_St_Bridge = Railroad1__St_Away;
      } else {
        nr_St_Bridge = false;
        ns_St_Bridge = Railroad1__St_Bridge;
      };
      _out->st = st_St_Bridge;
      _out->req = req_St_Bridge;
      _out->on_bridge = on_bridge_St_Bridge;
      next_tcount = next_tcount_St_Bridge;
      ns = ns_St_Bridge;
      nr = nr_St_Bridge;
      break;
    default:
      break;
  };
  self->pnr = nr;
  self->ck = ns;
  self->v_1 = next_tcount;
  self->v = false;;
}

void Railroad1__controller1_reset(Railroad1__controller1_mem* self) {
  self->v = true;
}

void Railroad1__controller1_step(int req_w, int req_e, int onw, int one,
                                 Railroad1__controller1_out* _out,
                                 Railroad1__controller1_mem* self) {
  
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
  int cur;
  int next_cur;
  if (req_e) {
    v_12 = 2;
  } else {
    v_12 = 0;
  };
  if (req_w) {
    v_13 = 1;
  } else {
    v_13 = v_12;
  };
  if (one) {
    v_14 = 2;
  } else {
    v_14 = v_13;
  };
  if (onw) {
    next_cur = 1;
  } else {
    next_cur = v_14;
  };
  v_9 = !(req_w);
  if (self->v) {
    cur = 0;
  } else {
    cur = self->v_3;
  };
  v_8 = (cur==0);
  v_10 = (v_8&&v_9);
  v_11 = (v_10&&req_e);
  v_7 = (cur==2);
  _out->ge = (v_7||v_11);
  v_5 = (cur==0);
  v_6 = (v_5&&req_w);
  v_4 = (cur==1);
  _out->gw = (v_4||v_6);
  self->v_3 = next_cur;
  self->v = false;;
}

void Railroad1__railroad1_reset(Railroad1__railroad1_mem* self) {
  Railroad1__train_node_reset(&self->train_node_1);
  Railroad1__train_node_reset(&self->train_node);
  Railroad1__controller1_reset(&self->controller1);
  self->v_16 = true;
  self->v = true;
}

void Railroad1__railroad1_step(int aw, int ae,
                               Railroad1__railroad1_out* _out,
                               Railroad1__railroad1_mem* self) {
  Railroad1__train_node_out Railroad1__train_node_out_st;
  Railroad1__controller1_out Railroad1__controller1_out_st;
  
  int req_w;
  int req_e;
  int onw;
  int one;
  int gw_in;
  int ge_in;
  if (self->v_16) {
    ge_in = false;
  } else {
    ge_in = self->v_17;
  };
  Railroad1__train_node_step(ae, ge_in, &Railroad1__train_node_out_st,
                             &self->train_node_1);
  _out->se = Railroad1__train_node_out_st.st;
  req_e = Railroad1__train_node_out_st.req;
  one = Railroad1__train_node_out_st.on_bridge;
  if (self->v) {
    gw_in = false;
  } else {
    gw_in = self->v_15;
  };
  Railroad1__train_node_step(aw, gw_in, &Railroad1__train_node_out_st,
                             &self->train_node);
  _out->sw = Railroad1__train_node_out_st.st;
  req_w = Railroad1__train_node_out_st.req;
  onw = Railroad1__train_node_out_st.on_bridge;
  Railroad1__controller1_step(req_w, req_e, onw, one,
                              &Railroad1__controller1_out_st,
                              &self->controller1);
  _out->gw = Railroad1__controller1_out_st.gw;
  _out->ge = Railroad1__controller1_out_st.ge;
  self->v_17 = _out->ge;
  self->v_16 = false;
  self->v_15 = _out->gw;
  self->v = false;;
}

void Railroad1__main_reset(Railroad1__main_mem* self) {
  Railroad1__railroad1_reset(&self->railroad1);
}

void Railroad1__main_step(int aw, int ae, Railroad1__main_out* _out,
                          Railroad1__main_mem* self) {
  Railroad1__railroad1_out Railroad1__railroad1_out_st;
  Railroad1__railroad1_step(aw, ae, &Railroad1__railroad1_out_st,
                            &self->railroad1);
  _out->sw = Railroad1__railroad1_out_st.sw;
  _out->se = Railroad1__railroad1_out_st.se;
  _out->gw = Railroad1__railroad1_out_st.gw;
  _out->ge = Railroad1__railroad1_out_st.ge;
}

