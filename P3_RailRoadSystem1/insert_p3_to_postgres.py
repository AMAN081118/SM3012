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
