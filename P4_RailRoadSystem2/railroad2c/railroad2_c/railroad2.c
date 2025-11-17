/* --- Generated the 16/11/2025 at 12:57 --- */
/* --- heptagon compiler, version 1.05.00 (compiled sat. nov. 1 5:25:8 CET 2025) --- */
/* --- Command line: /usr/local/bin/heptc railroad2.ept -target c -targetpath ./railroad2c --- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "railroad2.h"

void Railroad2__train_node_reset(Railroad2__train_node_mem* self) {
  self->v_1 = true;
  self->pnr = false;
  self->ck = Railroad2__St_Away;
}

void Railroad2__train_node_step(int approach, int grant_in,
                                Railroad2__train_node_out* _out,
                                Railroad2__train_node_mem* self) {
  
  int v_3;
  int v_2;
  int v;
  int nr_St_Bridge;
  Railroad2__st ns_St_Bridge;
  int tcount_St_Bridge;
  int on_bridge_St_Bridge;
  int req_St_Bridge;
  int st_St_Bridge;
  int nr_St_Wait;
  Railroad2__st ns_St_Wait;
  int tcount_St_Wait;
  int on_bridge_St_Wait;
  int req_St_Wait;
  int st_St_Wait;
  int nr_St_Away;
  Railroad2__st ns_St_Away;
  int tcount_St_Away;
  int on_bridge_St_Away;
  int req_St_Away;
  int st_St_Away;
  Railroad2__st ns;
  int r;
  int nr;
  int tcount;
  r = self->pnr;
  switch (self->ck) {
    case Railroad2__St_Away:
      tcount_St_Away = 0;
      on_bridge_St_Away = false;
      req_St_Away = false;
      st_St_Away = 0;
      if (approach) {
        nr_St_Away = true;
        ns_St_Away = Railroad2__St_Wait;
      } else {
        nr_St_Away = false;
        ns_St_Away = Railroad2__St_Away;
      };
      _out->st = st_St_Away;
      _out->req = req_St_Away;
      _out->on_bridge = on_bridge_St_Away;
      tcount = tcount_St_Away;
      ns = ns_St_Away;
      nr = nr_St_Away;
      break;
    case Railroad2__St_Wait:
      tcount_St_Wait = 0;
      on_bridge_St_Wait = false;
      req_St_Wait = true;
      st_St_Wait = 1;
      if (grant_in) {
        nr_St_Wait = true;
        ns_St_Wait = Railroad2__St_Bridge;
      } else {
        nr_St_Wait = false;
        ns_St_Wait = Railroad2__St_Wait;
      };
      _out->st = st_St_Wait;
      _out->req = req_St_Wait;
      _out->on_bridge = on_bridge_St_Wait;
      tcount = tcount_St_Wait;
      ns = ns_St_Wait;
      nr = nr_St_Wait;
      break;
    case Railroad2__St_Bridge:
      v_2 = (self->v_1||r);
      if (v_2) {
        tcount_St_Bridge = 0;
      } else {
        tcount_St_Bridge = self->v_4;
      };
      on_bridge_St_Bridge = true;
      req_St_Bridge = false;
      st_St_Bridge = 2;
      _out->st = st_St_Bridge;
      _out->req = req_St_Bridge;
      _out->on_bridge = on_bridge_St_Bridge;
      tcount = tcount_St_Bridge;
      v_3 = (tcount+1);
      v = (tcount>=3);
      if (v) {
        nr_St_Bridge = true;
        ns_St_Bridge = Railroad2__St_Away;
      } else {
        nr_St_Bridge = false;
        ns_St_Bridge = Railroad2__St_Bridge;
      };
      ns = ns_St_Bridge;
      nr = nr_St_Bridge;
      self->v_4 = v_3;
      self->v_1 = false;
      break;
    default:
      break;
  };
  self->pnr = nr;
  self->ck = ns;;
}

void Railroad2__controller2_reset(Railroad2__controller2_mem* self) {
  self->v_6 = true;
  self->v = true;
}

void Railroad2__controller2_step(int req_w, int req_e, int onw, int one,
                                 Railroad2__controller2_out* _out,
                                 Railroad2__controller2_mem* self) {
  
  int v_21;
  int v_20;
  int v_19;
  int v_18;
  int v_17;
  int v_16;
  int v_15;
  int v_14;
  int v_13;
  int v_12;
  int v_11;
  int v_10;
  int v_9;
  int v_8;
  int prev_cur;
  int cur;
  int prev_last_side;
  int last_side;
  if (req_e) {
    v_15 = 2;
  } else {
    v_15 = 0;
  };
  if (req_w) {
    v_16 = 1;
  } else {
    v_16 = v_15;
  };
  v_12 = (req_w&&req_e);
  if (self->v_6) {
    prev_last_side = 0;
  } else {
    prev_last_side = self->v_7;
  };
  v_13 = (prev_last_side==1);
  if (v_13) {
    v_14 = 2;
  } else {
    v_14 = 1;
  };
  if (v_12) {
    v_17 = v_14;
  } else {
    v_17 = v_16;
  };
  if (self->v) {
    prev_cur = 0;
  } else {
    prev_cur = self->v_5;
  };
  v_10 = (prev_cur==2);
  v_11 = (one&&v_10);
  if (v_11) {
    v_18 = 2;
  } else {
    v_18 = v_17;
  };
  v_8 = (prev_cur==1);
  v_9 = (onw&&v_8);
  if (v_9) {
    cur = 1;
  } else {
    cur = v_18;
  };
  _out->grant_e = (cur==2);
  _out->grant_w = (cur==1);
  v_20 = (cur==2);
  if (v_20) {
    v_21 = 2;
  } else {
    v_21 = prev_last_side;
  };
  v_19 = (cur==1);
  if (v_19) {
    last_side = 1;
  } else {
    last_side = v_21;
  };
  self->v_7 = last_side;
  self->v_6 = false;
  self->v_5 = cur;
  self->v = false;;
}

void Railroad2__railroad2_reset(Railroad2__railroad2_mem* self) {
  Railroad2__train_node_reset(&self->train_node_1);
  Railroad2__train_node_reset(&self->train_node);
  Railroad2__controller2_reset(&self->controller2);
  self->v_23 = true;
  self->v = true;
}

void Railroad2__railroad2_step(int approach_w, int approach_e,
                               Railroad2__railroad2_out* _out,
                               Railroad2__railroad2_mem* self) {
  Railroad2__train_node_out Railroad2__train_node_out_st;
  Railroad2__controller2_out Railroad2__controller2_out_st;
  
  int req_w;
  int req_e;
  int onw;
  int one;
  int grant_w_d;
  int grant_e_d;
  if (self->v_23) {
    grant_e_d = false;
  } else {
    grant_e_d = self->v_24;
  };
  Railroad2__train_node_step(approach_e, grant_e_d,
                             &Railroad2__train_node_out_st,
                             &self->train_node_1);
  _out->st_e = Railroad2__train_node_out_st.st;
  req_e = Railroad2__train_node_out_st.req;
  one = Railroad2__train_node_out_st.on_bridge;
  if (self->v) {
    grant_w_d = false;
  } else {
    grant_w_d = self->v_22;
  };
  Railroad2__train_node_step(approach_w, grant_w_d,
                             &Railroad2__train_node_out_st, &self->train_node);
  _out->st_w = Railroad2__train_node_out_st.st;
  req_w = Railroad2__train_node_out_st.req;
  onw = Railroad2__train_node_out_st.on_bridge;
  Railroad2__controller2_step(req_w, req_e, onw, one,
                              &Railroad2__controller2_out_st,
                              &self->controller2);
  _out->grant_w = Railroad2__controller2_out_st.grant_w;
  _out->grant_e = Railroad2__controller2_out_st.grant_e;
  self->v_24 = _out->grant_e;
  self->v_23 = false;
  self->v_22 = _out->grant_w;
  self->v = false;;
}

void Railroad2__main_reset(Railroad2__main_mem* self) {
  Railroad2__railroad2_reset(&self->railroad2);
}

void Railroad2__main_step(int approach_w_in, int approach_e_in,
                          Railroad2__main_out* _out,
                          Railroad2__main_mem* self) {
  Railroad2__railroad2_out Railroad2__railroad2_out_st;
  Railroad2__railroad2_step(approach_w_in, approach_e_in,
                            &Railroad2__railroad2_out_st, &self->railroad2);
  _out->st_w_out = Railroad2__railroad2_out_st.st_w;
  _out->st_e_out = Railroad2__railroad2_out_st.st_e;
  _out->gw_out = Railroad2__railroad2_out_st.grant_w;
  _out->ge_out = Railroad2__railroad2_out_st.grant_e;
}

