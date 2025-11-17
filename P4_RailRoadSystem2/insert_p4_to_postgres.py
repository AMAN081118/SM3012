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
