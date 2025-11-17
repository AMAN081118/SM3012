#!/usr/bin/env python3
import csv, sys
from collections import defaultdict

csvfile = sys.argv[1] if len(sys.argv) > 1 else "output_p4.csv"

states = set()
transitions = defaultdict(int)
prev_state = None
prev_tick = None

with open(csvfile) as f:
    dr = csv.DictReader(f)
    for row in dr:
        tick = int(row['tick'])
        sw = int(row['state_w'])
        se = int(row['state_e'])
        gw = int(row['grant_w'])
        ge = int(row['grant_e'])
        s = (sw, se, gw, ge)
        states.add(s)
        if prev_state is not None and prev_state != s:
            transitions[(prev_state, s)] += 1
        prev_state = s
        prev_tick = tick

print("Reachable composite states (count={}):".format(len(states)))
for st in sorted(states):
    print(st)
print("\nTransitions (unique):", len(transitions))
for (a,b),c in transitions.items():
    print(f"{a} -> {b}   occ: {c}")
