import csv

with open("output_p3.csv") as f:
    dr = csv.DictReader(f)
    states = set()
    transitions = []

    last = None
    for row in dr:
        s = (row['sw'], row['se'], row['gw'], row['ge'])

        if last is not None and s != last:
            transitions.append((last, s))

        states.add(s)
        last = s

print("Reachable States:")
for s in states:
    print(s)

print("\nTransitions:")
for t in transitions:
    print(f"{t[0]} -> {t[1]}")
