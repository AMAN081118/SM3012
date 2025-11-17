import psycopg2
import csv
import sys

csvfile = sys.argv[1] if len(sys.argv) > 1 else "output_p2.csv"

def compute_state(row):
    if int(row['pause']) == 1:
        return "PAUSE"
    d = int(row['effective_delta'])
    if d > 0:
        return "ACCEL"
    if d < 0:
        return "DECEL"
    return "HOLD"

conn = psycopg2.connect(
    dbname="mydb",
    user="amank",
    password="aman123",
    host="localhost",
    port=5432
)

cur = conn.cursor()

cur.execute("""
CREATE TABLE IF NOT EXISTS speed_log_p2(
    tick INT,
    cmd INT,
    accel INT,
    decel INT,
    pause INT,
    speed INT,
    effective_delta INT,
    state_label TEXT
);
""")
conn.commit()

with open(csvfile) as f:
    dr = csv.DictReader(f)
    for row in dr:
        state = compute_state(row)
        cur.execute(
            """INSERT INTO speed_log_p2
            (tick, cmd, accel, decel, pause, speed, effective_delta, state_label)
            VALUES (%s,%s,%s,%s,%s,%s,%s,%s)""",
            (
                row['tick'], row['cmd'], row['accel'], row['decel'],
                row['pause'], row['speed'], row['effective_delta'],
                state
            )
        )

conn.commit()
cur.close()
conn.close()

print("Inserted P2 data successfully.")
