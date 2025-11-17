## Objective

The objective of this problem is to design and simulate RailRoadSystem₁, consisting of Controller₁ and two trains (West and East). The system must model train approaches, waiting behavior, bridge occupancy, and West-priority access. The simulation should run for at least 100 ticks, with reachable states and transitions recorded, stored in PostgreSQL, and analyzed.

-----

## Heptagon Model (railroad1.ept)

```heptagon
-- ============================================================
--  P3: RailRoadSystem1 — CAUSALITY FIXED VERSION
-- ============================================================

node train_node(approach: bool; grant_in: bool)
returns (st: int; req: bool; on_bridge: bool)
var
  tcount: int;
  next_tcount: int;
let
  tcount = 0 -> pre next_tcount;

  automaton

    state Away
      do
        st = 0;
        req = false;
        on_bridge = false;
        next_tcount = 0;
      until approach then Wait

    state Wait
      do
        st = 1;
        req = true;
        on_bridge = false;
        next_tcount = 0;
      until grant_in then Bridge

    state Bridge
      do
        st = 2;
        req = false;
        on_bridge = true;
        next_tcount = tcount + 1;
      until (tcount >= 2) then Away

  end
tel


node controller1(req_w: bool; req_e: bool; onw: bool; one: bool)
returns (gw: bool; ge: bool)
var
  cur: int;
  next_cur: int;
let
  cur = 0 -> pre next_cur;

  gw = (cur = 1) or (cur = 0 and req_w);
  ge = (cur = 2) or (cur = 0 and (not req_w) and req_e);

  next_cur =
    if onw then 1
    else if one then 2
    else if req_w then 1
    else if req_e then 2
    else 0;
tel


-- ============================================================
-- CAUSAL COMPOSITION (cycle broken with delayed grants)
-- ============================================================

node railroad1(aw: bool; ae: bool)
returns (sw: int; se: int; gw: bool; ge: bool)
var
  req_w: bool;
  req_e: bool;
  onw: bool;
  one: bool;

  -- delayed (past-tick) grants fed into trains
  gw_in: bool;
  ge_in: bool;
let
  -- 1 tick delay on controller grants:
  gw_in = false -> pre gw;
  ge_in = false -> pre ge;

  -- trains use delayed grants
  (sw, req_w, onw) = train_node(aw, gw_in);
  (se, req_e, one) = train_node(ae, ge_in);

  -- controller computes grants for NEXT tick
  (gw, ge) = controller1(req_w, req_e, onw, one);
tel


node main(aw: bool; ae: bool)
returns (sw: int; se: int; gw: bool; ge: bool)
let
  (sw, se, gw, ge) = railroad1(aw, ae);
tel


```

-----

## Generated Code (railroad1.c, railroad1.h)

### railroad1.c

```c
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



```

### railroad1.h

```c
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


```

-----

## Wrapper File (railroad1\_wrapper.c)

```c
#include "railroad1_types.h"
#include "railroad1.h"

// global memory for the railroad1 node
static Railroad1__railroad1_mem rr_mem;

// initialize
void railroad1_init() {
    Railroad1__railroad1_reset(&rr_mem);
}

// step function wrapper
void railroad1_step(int aw, int ae,
                    int *sw, int *se,
                    int *gw, int *ge)
{
    Railroad1__railroad1_out out;

    Railroad1__railroad1_step(aw, ae, &out, &rr_mem);

    *sw = out.sw;
    *se = out.se;
    *gw = out.gw;
    *ge = out.ge;
}


```

-----

## Simulation Driver (main\_sim\_p3.c)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void railroad1_init();
void railroad1_step(int aw, int ae,
                    int *sw, int *se,
                    int *gw, int *ge);

int main(int argc, char **argv)
{
    const char *infile  = (argc >= 2) ? argv[1] : "input_p3.csv";
    const char *outfile = (argc >= 3) ? argv[2] : "output_p3.csv";

    FILE *fin = fopen(infile, "r");
    if(!fin) { perror("input_p3.csv"); return 1; }

    FILE *fout = fopen(outfile, "w");
    if(!fout) { perror("output_p3.csv"); fclose(fin); return 1; }

    fprintf(fout, "tick,aw,ae,sw,se,gw,ge\n");

    railroad1_init();

    char line[256];
    int tick = 0;

    while(fgets(line, sizeof(line), fin)) 
    {
        if(line[0]=='#' || strlen(line)<3) continue;

        int aw, ae;
        if(sscanf(line, "%d,%d", &aw, &ae)!=2) continue;

        int sw,se,gw,ge;
        railroad1_step(aw, ae, &sw, &se, &gw, &ge);

        fprintf(fout, "%d,%d,%d,%d,%d,%d,%d\n",
                tick, aw, ae, sw, se, gw, ge);

        tick++;
    }

    fclose(fin);
    fclose(fout);

    return 0;
}


```

-----

## Input File (input_p3.csv)

```csv
# approach_w,approach_e
0,0
1,0
0,1
1,1
0,0
0,1
0,0
1,0
0,0
0,0
1,1
0,0
0,1
1,0
0,0
0,0
1,0
0,1
0,0
0,0
1,0
0,1
1,1
0,0
0,1
0,0
1,0
0,0
0,0
1,1
0,0
0,1
1,0
0,0
0,0
1,0
0,1
0,0
0,0
1,0
0,1
1,1
0,0
0,1
0,0
1,0
0,0
0,0
1,1
0,0
0,1
1,0
0,0
0,0
1,0
0,1
0,0
0,0
1,0
0,1
1,1
0,0
0,1
0,0
1,0
0,0
0,0
1,1
0,0
0,1
1,0
0,0
0,0
1,0
0,1
0,0
0,0
1,0
0,1
1,1
0,0
0,1
0,0
1,0
0,0
0,0
1,1
0,0
0,1
1,0
0,0
0,0
1,0
0,1
0,0
0,0
1,0
0,1
1,1
0,0

```

-----

## Output File (output_p3.csv)

```csv
tick,aw,ae,sw,se,gw,ge
0,0,0,0,0,0,0
1,1,0,0,0,0,0
2,0,1,1,0,1,0
3,1,1,1,1,1,0
4,0,0,2,1,1,0
5,0,1,2,1,1,0
6,0,0,2,1,1,0
7,1,0,0,1,1,0
8,0,0,1,1,0,1
9,0,0,2,1,1,0
10,1,1,2,2,1,0
11,0,0,2,2,1,0
12,0,1,0,2,1,0
13,1,0,0,0,0,1
14,0,0,1,0,1,0
15,0,0,1,0,1,0
16,1,0,2,0,1,0
17,0,1,2,0,1,0
18,0,0,2,1,1,0
19,0,0,0,1,1,0
20,1,0,0,1,0,1
21,0,1,1,1,0,1
22,1,1,1,2,1,0
23,0,0,1,2,0,1
24,0,1,2,2,0,1
25,0,0,2,0,1,0
26,1,0,2,0,1,0
27,0,0,0,0,1,0
28,0,0,0,0,0,0
29,1,1,0,0,0,0
30,0,0,1,1,1,0
31,0,1,1,1,1,0
32,1,0,2,1,1,0
33,0,0,2,1,1,0
34,0,0,2,1,1,0
35,1,0,0,1,1,0
36,0,1,1,1,0,1
37,0,0,2,1,1,0
38,0,0,2,2,1,0
39,1,0,2,2,1,0
40,0,1,0,2,1,0
41,1,1,0,0,0,1
42,0,0,1,1,1,0
43,0,1,1,2,1,0
44,0,0,2,2,0,1
45,1,0,2,2,1,0
46,0,0,2,0,1,0
47,0,0,0,0,1,0
48,1,1,0,0,0,0
49,0,0,1,1,1,0
50,0,1,1,1,1,0
51,1,0,2,1,1,0
52,0,0,2,1,1,0
53,0,0,2,1,1,0
54,1,0,0,1,1,0
55,0,1,1,1,0,1
56,0,0,2,1,1,0
57,0,0,2,2,1,0
58,1,0,2,2,1,0
59,0,1,0,2,1,0
60,1,1,0,0,0,1
61,0,0,1,1,1,0
62,0,1,1,2,1,0
63,0,0,2,2,0,1
64,1,0,2,2,1,0
65,0,0,2,0,1,0
66,0,0,0,0,1,0
67,1,1,0,0,0,0
68,0,0,1,1,1,0
69,0,1,1,1,1,0
70,1,0,2,1,1,0
71,0,0,2,1,1,0
72,0,0,2,1,1,0
73,1,0,0,1,1,0
74,0,1,1,1,0,1
75,0,0,2,1,1,0
76,0,0,2,2,1,0
77,1,0,2,2,1,0
78,0,1,0,2,1,0
79,1,1,0,0,0,1
80,0,0,1,1,1,0
81,0,1,1,2,1,0
82,0,0,2,2,0,1
83,1,0,2,2,1,0
84,0,0,2,0,1,0
85,0,0,0,0,1,0
86,1,1,0,0,0,0
87,0,0,1,1,1,0
88,0,1,1,1,1,0
89,1,0,2,1,1,0
90,0,0,2,1,1,0
91,0,0,2,1,1,0
92,1,0,0,1,1,0
93,0,1,1,1,0,1
94,0,0,2,1,1,0
95,0,0,2,2,1,0
96,1,0,2,2,1,0
97,0,1,0,2,1,0
98,1,1,0,0,0,1
99,0,0,1,1,1,0

```

-----

## PostgreSQL Table Schema

CREATE TABLE IF NOT EXISTS railroad_log_p3 (
    tick INT,
    aw INT,
    ae INT,
    sw INT,
    se INT,
    gw INT,
    ge INT,
    state_label TEXT
);


-----

## Python Insert Script (insert\_p3\_to\_postgres.py)

```python
import psycopg2, csv, sys

csvfile = sys.argv[1] if len(sys.argv)>1 else "output_p3.csv"

def label(sw, se, gw, ge):
    return f"W{sw}_E{se}_GW{gw}_GE{ge}"

conn = psycopg2.connect(
    dbname="mydb",
    user="amank",
    password="aman123",
    host="localhost",
    port=5432
)
cur = conn.cursor()

cur.execute("""
CREATE TABLE IF NOT EXISTS railroad_log_p3 (
    tick INT,
    aw INT,
    ae INT,
    sw INT,
    se INT,
    gw INT,
    ge INT,
    state_label TEXT
);
""")
conn.commit()

with open(csvfile) as f:
    dr = csv.DictReader(f)
    for r in dr:
        st = label(r['sw'], r['se'], r['gw'], r['ge'])
        cur.execute("""
            INSERT INTO railroad_log_p3
            (tick, aw, ae, sw, se, gw, ge, state_label)
            VALUES (%s,%s,%s,%s,%s,%s,%s,%s)
        """, (
            r['tick'], r['aw'], r['ae'],
            r['sw'], r['se'], r['gw'], r['ge'],
            st
        ))

conn.commit()
cur.close()
conn.close()
print("Inserted:", csvfile)


```

-----

## Grafana Screenshot

-----