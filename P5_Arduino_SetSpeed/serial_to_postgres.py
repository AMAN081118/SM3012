#!/usr/bin/env python3
# serial_to_postgres.py
# Reads CSV lines from serial and inserts into PostgreSQL table for P1/P2.

import serial
import time
import csv
import psycopg2
import sys

SERIAL_PORT = sys.argv[1] if len(sys.argv) > 1 else '/dev/ttyUSB0'  # change as needed
BAUD = 115200
TABLE = sys.argv[2] if len(sys.argv) > 2 else 'speed_log_hw'      # target table

# DB config (edit or load from JSON)
DB = dict(dbname='mydb', user='amank', password='aman123', host='localhost', port=5432)

# open DB
conn = psycopg2.connect(**DB)
cur = conn.cursor()

# Create table with a flexible schema that handles both P1 and P2 logs
cur.execute(f"""
CREATE TABLE IF NOT EXISTS {TABLE} (
  tick INT,
  cmd INT,
  accel INT,
  decel INT,
  pause INT,
  speed INT,
  effective_delta INT,
  source TEXT,
  ts TIMESTAMP DEFAULT now()
);
""")
conn.commit()

ser = serial.Serial(SERIAL_PORT, BAUD, timeout=2)
time.sleep(2)  # wait for Arduino reset

print("Listening on", SERIAL_PORT)
header_received = False

while True:
    try:
        line = ser.readline().decode(errors='ignore').strip()
        if not line:
            continue
        # skip header line; if header, set flag
        if not header_received and "tick" in line.lower():
            header_received = True
            print("Header:", line)
            continue
        # parse CSV - handle 6 or 7 columns
        parts = [p.strip() for p in line.split(',')]
        if len(parts) < 6:
            print("Malformed:", line)
            continue

        # detection: if 6 columns -> P1; if 7 -> P2
        if len(parts) == 6:
            tick, cmd, accel, decel, pause, speed = parts
            effective_delta = None
        else:
            tick, cmd, accel, decel, pause, speed, effective_delta = parts

        # coerce to ints or null
        def toint(x):
            try: return int(x)
            except: return None

        vals = (toint(tick), toint(cmd), toint(accel), toint(decel), toint(pause), toint(speed),
                toint(effective_delta), 'arduino')
        cur.execute(f"INSERT INTO {TABLE} (tick,cmd,accel,decel,pause,speed,effective_delta,source) VALUES (%s,%s,%s,%s,%s,%s,%s,%s)", vals)
        conn.commit()
        print("Inserted tick", tick)
    except KeyboardInterrupt:
        print("Stopping")
        break
    except Exception as e:
        print("Error:", e)
        time.sleep(0.5)

ser.close()
cur.close()
conn.close()
