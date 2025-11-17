Start everything:
./sm3012.sh start

Run all tests (P1–P4):
./sm3012.sh run_all_test

Run all simulations (P1–P4) + overwrite DB:
./sm3012.sh run_all_sim

Stop everything:
./sm3012.sh stop

Inside any P folder:
Test:
./do.sh test

Simulation + DB insert:
./do.sh sim

---- for each folder
Inside P1_SetSpeed/:

✔ Test (shows output in terminal)
./do.sh test

✔ Simulate (generate output.csv → auto DB overwrite → insert fresh)
./do.sh sim

✔ Clean (remove binaries/output)
./do.sh clean

✔ Build only
./do.sh build