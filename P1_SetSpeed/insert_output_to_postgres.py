import psycopg2
import csv
import sys

csvfile = sys.argv[1] if len(sys.argv) > 1 else "output.csv"
table = "speed_log_p1"

conn = psycopg2.connect(
    dbname="mydb",
    user="amank",
    password="aman123",
    host="localhost",
    port=5432
)

cur = conn.cursor()

create_sql = """
CREATE TABLE IF NOT EXISTS speed_log_p1(
    tick INT,
    cmd INT,
    accel INT,
    decel INT,
    speed INT
);
"""

cur.execute(create_sql)
conn.commit()

with open(csvfile) as f:
    dr = csv.DictReader(f)
    for row in dr:
        cur.execute(
            "INSERT INTO speed_log_p1 (tick, cmd, accel, decel, speed) VALUES (%s,%s,%s,%s,%s)",
            (row['tick'], row['cmd'], row['accel'], row['decel'], row['speed'])
        )

conn.commit()
cur.close()
conn.close()

print("Inserted rows from", csvfile)
