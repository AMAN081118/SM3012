# P4 — RailRoadSystem2

## Objective
The objective of this problem is to simulate RailRoadSystem₂ using Controller₂, which implements fair alternation between West and East trains. The system is executed for at least 100 ticks, logged to PostgreSQL, and analyzed to compare its behavior with RailRoadSystem₁, highlighting fairness and state differences.

## Heptagon model
- included file: railroad2.ept
```heptagon
-- ============================================================
-- P4: RailRoadSystem2  = controller2 || trainw || traine
-- ============================================================

-- ============================================================
-- TRAIN NODE (corrected tcount handling)
-- ============================================================

node train_node(approach: bool; grant_in: bool)
returns (st: int; req: bool; on_bridge: bool)
var
  tcount: int;
let
  automaton

    state Away
      do
        st = 0;
        req = false;
        on_bridge = false;
        tcount = 0;
      until approach then Wait

    state Wait
      do
        st = 1;
        req = true;
        on_bridge = false;
        tcount = 0;
      until grant_in then Bridge

    state Bridge
      do
        st = 2;
        req = false;
        on_bridge = true;
        tcount = 0 -> pre (tcount + 1);
      until (tcount >= 3) then Away

  end
tel

-- ============================================================
-- CONTROLLER2: fair alternation
-- ============================================================

node controller2(req_w: bool; req_e: bool; onw: bool; one: bool)
returns (grant_w: bool; grant_e: bool)
var
  prev_cur: int;
  cur: int;
  prev_last_side: int;
  last_side: int;
let
  prev_cur = 0 -> pre cur;
  prev_last_side = 0 -> pre last_side;

  cur =
    if onw and prev_cur = 1 then 1
    else if one and prev_cur = 2 then 2
    else
      if req_w and req_e then
        (if prev_last_side = 1 then 2 else 1)
      else if req_w then 1
      else if req_e then 2
      else 0;

  last_side =
    if cur = 1 then 1
    else if cur = 2 then 2
    else prev_last_side;

  grant_w = (cur = 1);
  grant_e = (cur = 2);
tel

-- ============================================================
-- SYSTEM COMPOSITION (CAUSALITY-FIXED VERSION)
-- ============================================================

node railroad2(approach_w: bool; approach_e: bool)
returns (st_w: int; st_e: int; grant_w: bool; grant_e: bool)
var
  req_w: bool;
  req_e: bool;
  onw: bool;
  one: bool;

  grant_w_d: bool;   -- delayed version for train inputs
  grant_e_d: bool;
let
  -- the delayed grants break the causality loop
  grant_w_d = false -> pre grant_w;
  grant_e_d = false -> pre grant_e;

  -- trains use DELAYED grants
  (st_w, req_w, onw) = train_node(approach_w, grant_w_d);
  (st_e, req_e, one) = train_node(approach_e, grant_e_d);

  -- controller sees current requests & bridge occupancy
  (grant_w, grant_e) = controller2(req_w, req_e, onw, one);
tel


-- ============================================================
-- MAIN ENTRYPOINT
-- ============================================================

node main(approach_w_in: bool; approach_e_in: bool)
returns (st_w_out: int; st_e_out: int; gw_out: bool; ge_out: bool)
let
  (st_w_out, st_e_out, gw_out, ge_out) =
    railroad2(approach_w_in, approach_e_in);
tel

```

## Compilation
- heptc railroad2.ept -target c -targetpath ./railroad2c

## Wrapper and Simulation
- wrapper: railroad2_wrapper.c
```c
#include "railroad2_types.h"
#include "railroad2.h"

/* Global memory for the railroad2 node */
static Railroad2__railroad2_mem rr2_mem;

/* init */
void railroad2_init() {
    Railroad2__railroad2_reset(&rr2_mem);
}

/* step: approach_w, approach_e as ints (0/1) */
/* returns state_w, state_e, grant_w, grant_e via pointers */
void railroad2_step(int approach_w, int approach_e,
                    int *state_w, int *state_e,
                    int *grant_w, int *grant_e) {
    Railroad2__railroad2_out out;
    Railroad2__railroad2_step(approach_w, approach_e, &out, &rr2_mem);
    *state_w = out.st_w;
    *state_e = out.st_e;
    *grant_w = out.grant_w;
    *grant_e = out.grant_e;
}

```
- simulator: main_sim_p4.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void railroad2_init();
void railroad2_step(int approach_w, int approach_e,
                    int *state_w, int *state_e,
                    int *grant_w, int *grant_e);

int main(int argc, char **argv) {
    const char *infile = (argc >= 2) ? argv[1] : "input_p4.csv";
    const char *outfile = (argc >= 3) ? argv[2] : "output_p4.csv";

    FILE *fin = fopen(infile, "r");
    if (!fin) { perror("open input_p4.csv"); return 1; }
    FILE *fout = fopen(outfile, "w");
    if (!fout) { perror("open output_p4.csv"); fclose(fin); return 1; }

    fprintf(fout, "tick,approach_w,approach_e,state_w,state_e,grant_w,grant_e\n");

    railroad2_init();

    char line[256];
    int tick = 0;
    while (fgets(line, sizeof(line), fin)) {
        if (line[0] == '#' || strlen(line) < 3) continue;
        int aw, ae;
        if (sscanf(line, "%d,%d", &aw, &ae) != 2) continue;
        int sw, se, gw, ge;
        railroad2_step(aw, ae, &sw, &se, &gw, &ge);
        fprintf(fout, "%d,%d,%d,%d,%d,%d,%d\n", tick, aw, ae, sw, se, gw, ge);
        tick++;
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

```

## Input and Output
- input_p4.csv
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
- output_p4.csv
```csv
tick,approach_w,approach_e,state_w,state_e,grant_w,grant_e
0,0,0,0,0,0,0
1,1,0,0,0,0,0
2,0,1,1,0,1,0
3,1,1,1,1,0,1
4,0,0,2,1,0,1
5,0,1,2,2,0,1
6,0,0,2,2,0,1
7,1,0,2,2,0,1
8,0,0,0,2,0,1
9,0,0,0,0,0,0
10,1,1,0,0,0,0
11,0,0,1,1,1,0
12,0,1,1,1,0,1
13,1,0,2,1,0,1
14,0,0,2,2,0,1
15,0,0,2,2,0,1
16,1,0,2,2,0,1
17,0,1,0,2,0,1
18,0,0,0,0,0,0
19,0,0,0,0,0,0
20,1,0,0,0,0,0
21,0,1,1,0,1,0
22,1,1,1,1,0,1
23,0,0,2,1,0,1
24,0,1,2,2,0,1
25,0,0,2,2,0,1
26,1,0,2,2,0,1
27,0,0,0,2,0,1
28,0,0,0,0,0,0
29,1,1,0,0,0,0
30,0,0,1,1,1,0
31,0,1,1,1,0,1
32,1,0,2,1,0,1
33,0,0,2,2,0,1
34,0,0,2,2,0,1
35,1,0,2,2,0,1
36,0,1,0,2,0,1
37,0,0,0,0,0,0
38,0,0,0,0,0,0
39,1,0,0,0,0,0
40,0,1,1,0,1,0
41,1,1,1,1,0,1
42,0,0,2,1,0,1
43,0,1,2,2,0,1
44,0,0,2,2,0,1
45,1,0,2,2,0,1
46,0,0,0,2,0,1
47,0,0,0,0,0,0
48,1,1,0,0,0,0
49,0,0,1,1,1,0
50,0,1,1,1,0,1
51,1,0,2,1,0,1
52,0,0,2,2,0,1
53,0,0,2,2,0,1
54,1,0,2,2,0,1
55,0,1,0,2,0,1
56,0,0,0,0,0,0
57,0,0,0,0,0,0
58,1,0,0,0,0,0
59,0,1,1,0,1,0
60,1,1,1,1,0,1
61,0,0,2,1,0,1
62,0,1,2,2,0,1
63,0,0,2,2,0,1
64,1,0,2,2,0,1
65,0,0,0,2,0,1
66,0,0,0,0,0,0
67,1,1,0,0,0,0
68,0,0,1,1,1,0
69,0,1,1,1,0,1
70,1,0,2,1,0,1
71,0,0,2,2,0,1
72,0,0,2,2,0,1
73,1,0,2,2,0,1
74,0,1,0,2,0,1
75,0,0,0,0,0,0
76,0,0,0,0,0,0
77,1,0,0,0,0,0
78,0,1,1,0,1,0
79,1,1,1,1,0,1
80,0,0,2,1,0,1
81,0,1,2,2,0,1
82,0,0,2,2,0,1
83,1,0,2,2,0,1
84,0,0,0,2,0,1
85,0,0,0,0,0,0
86,1,1,0,0,0,0
87,0,0,1,1,1,0
88,0,1,1,1,0,1
89,1,0,2,1,0,1
90,0,0,2,2,0,1
91,0,0,2,2,0,1
92,1,0,2,2,0,1
93,0,1,0,2,0,1
94,0,0,0,0,0,0
95,0,0,0,0,0,0
96,1,0,0,0,0,0
97,0,1,1,0,1,0
98,1,1,1,1,0,1
99,0,0,2,1,0,1

```

## DB & Grafana
- create_table_p4.sql
```sql
CREATE TABLE IF NOT EXISTS railroad_log_p4 (
  tick INT,
  approach_w INT,
  approach_e INT,
  state_w INT,
  state_e INT,
  grant_w INT,
  grant_e INT,
  controller_last INT
);

```
- insert_p4_to_postgres.py
```python
#!/usr/bin/env python3
import psycopg2
import csv
import sys

csvfile = sys.argv[1] if len(sys.argv) > 1 else "output_p4.csv"

conn = psycopg2.connect(dbname="mydb", user="amank", password="aman123", host="localhost", port=5432)
cur = conn.cursor()

cur.execute("""
CREATE TABLE IF NOT EXISTS railroad_log_p4 (
  tick INT,
  approach_w INT,
  approach_e INT,
  state_w INT,
  state_e INT,
  grant_w INT,
  grant_e INT,
  controller_last INT
);
""")
conn.commit()

# Read CSV and collect rows
rows = []
with open(csvfile) as f:
    dr = csv.DictReader(f)
    for row in dr:
        rows.append({
            'tick': int(row['tick']),
            'approach_w': int(row['approach_w']),
            'approach_e': int(row['approach_e']),
            'state_w': int(row['state_w']),
            'state_e': int(row['state_e']),
            'grant_w': int(row['grant_w']),
            'grant_e': int(row['grant_e'])
        })

# Compute controller_last: which side was most recently granted (1=west,2=east,0=none)
last = 0
rows_with_last = []
for r in rows:
    if r['grant_w'] == 1 and r['grant_e'] == 0:
        last = 1
    elif r['grant_e'] == 1 and r['grant_w'] == 0:
        last = 2
    # if both zero, keep last as-is; if both 1 simultaneously shouldn't happen but if it does prefer last
    r['controller_last'] = last
    rows_with_last.append(r)

# Insert into DB
for r in rows_with_last:
    cur.execute("""INSERT INTO railroad_log_p4
                   (tick, approach_w, approach_e, state_w, state_e, grant_w, grant_e, controller_last)
                   VALUES (%s,%s,%s,%s,%s,%s,%s,%s)""",
                (r['tick'], r['approach_w'], r['approach_e'],
                 r['state_w'], r['state_e'], r['grant_w'], r['grant_e'],
                 r['controller_last']))
conn.commit()
cur.close()
conn.close()
print("Inserted", len(rows_with_last), "rows into railroad_log_p4")

```
- Grafana queries: (list)

## Reachability & Transitions
- p4_reach_trans.txt
```txt
Reachable composite states (count=7):
(0, 0, 0, 0)
(0, 2, 0, 1)
(1, 0, 1, 0)
(1, 1, 0, 1)
(1, 1, 1, 0)
(2, 1, 0, 1)
(2, 2, 0, 1)

Transitions (unique): 8
(0, 0, 0, 0) -> (1, 0, 1, 0)   occ: 6
(1, 0, 1, 0) -> (1, 1, 0, 1)   occ: 6
(1, 1, 0, 1) -> (2, 1, 0, 1)   occ: 11
(2, 1, 0, 1) -> (2, 2, 0, 1)   occ: 10
(2, 2, 0, 1) -> (0, 2, 0, 1)   occ: 10
(0, 2, 0, 1) -> (0, 0, 0, 0)   occ: 10
(0, 0, 0, 0) -> (1, 1, 1, 0)   occ: 5
(1, 1, 1, 0) -> (1, 1, 0, 1)   occ: 5

```
## Observations and comparison with P3
- (fill after running both)
