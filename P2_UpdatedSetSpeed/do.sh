#!/bin/bash

# Detect which problem folder we are in
FOLDER=$(basename "$PWD")

# Initialize variables based on the folder
case "$FOLDER" in

"P1_SetSpeed")
    TEST_SRC="test_setspeed.c"
    TEST_BIN="test_setspeed"
    SIM_SRC="main_sim.c"
    SIM_BIN="sim_p1"
    INSERT_SCRIPT="insert_output_to_postgres.py"
    INPUT_FILE="input.csv"
    OUTPUT_FILE="output.csv"
    TABLE_NAME="speed_log_p1"
    C_FOLDER="setspeedc/setspeed_c"
    WRAPPER="setspeed_wrapper.c"
    MAIN_SRC="main_sim.c"
    ;;

"P2_UpdatedSetSpeed")
    TEST_SRC="test_updated_setspeed.c"
    TEST_BIN="test_p2"
    SIM_SRC="main_sim_p2.c"
    SIM_BIN="sim_p2"
    INSERT_SCRIPT="insert_p2_to_postgres.py"
    INPUT_FILE="input_p2.csv"
    OUTPUT_FILE="output_p2.csv"
    TABLE_NAME="speed_log_p2"
    C_FOLDER="updated_setspeedc/updated_setspeed_c"
    WRAPPER="updated_setspeed_wrapper.c"
    MAIN_SRC="main_sim_p2.c"
    ;;

"P3_RailRoadSystem1")
    TEST_SRC="test_railroad1.c"
    TEST_BIN="test_p3"
    SIM_SRC="main_sim_p3.c"
    SIM_BIN="sim_p3"
    INSERT_SCRIPT="insert_p3_to_postgres.py"
    INPUT_FILE="input_p3.csv"
    OUTPUT_FILE="output_p3.csv"
    TABLE_NAME="railroad_log_p3"
    C_FOLDER="railroad1c"
    WRAPPER="railroad1_wrapper.c"
    MAIN_SRC="main_sim_p3.c"
    ;;

"P4_RailRoadSystem2")
    TEST_SRC="test_railroad2.c"
    TEST_BIN="test_p4"
    SIM_SRC="main_sim_p4.c"
    SIM_BIN="sim_p4"
    INSERT_SCRIPT="insert_p4_to_postgres.py"
    INPUT_FILE="input_p4.csv"
    OUTPUT_FILE="output_p4.csv"
    TABLE_NAME="railroad_log_p4"
    C_FOLDER="railroad2c/railroad2_c"
    WRAPPER="railroad2_wrapper.c"
    MAIN_SRC="main_sim_p4.c"
    ;;

*)
    echo "Unknown project folder: $FOLDER"
    exit 1
    ;;
esac

# Common GCC include path
HEPT_INC="/usr/local/lib/heptagon/c"

# Run commands based on keyword
case "$1" in

build)
    echo "Compiling test program..."
    gcc -I "$HEPT_INC" -I "$C_FOLDER" -o "$TEST_BIN" \
        "$TEST_SRC" "$WRAPPER" "$C_FOLDER"/*.c
    echo "Compiling simulation program..."
    gcc -I "$HEPT_INC" -I "$C_FOLDER" -o "$SIM_BIN" \
        "$MAIN_SRC" "$WRAPPER" "$C_FOLDER"/*.c
    echo "Build complete."
    ;;

test)
    if [[ ! -f "$TEST_BIN" ]]; then
        echo "Test binary not found, building..."
        ./do.sh build
    fi
    echo "Running test:"
    echo "-------------------------------------"
    ./"$TEST_BIN"
    ;;

sim)
    if [[ ! -f "$SIM_BIN" ]]; then
        echo "Simulation binary not found, building..."
        ./do.sh build
    fi

    echo "Running simulation: $SIM_BIN $INPUT_FILE → $OUTPUT_FILE"
    ./"$SIM_BIN" "$INPUT_FILE" "$OUTPUT_FILE"

    echo "Clearing old rows from table: $TABLE_NAME"
    PGPASSWORD="aman123" psql -h 172.23.144.52 -U amank -d mydb -c "DELETE FROM $TABLE_NAME;"

    echo "Inserting new rows using: $INSERT_SCRIPT"
    python3 "$INSERT_SCRIPT" "$OUTPUT_FILE"

    echo "Simulation + DB update complete."
    ;;


clean)
    echo "Deleting binaries and CSV outputs..."
    rm -f "$TEST_BIN" "$SIM_BIN" "$OUTPUT_FILE"
    ;;

*)
    echo "Usage: ./do.sh {build|test|sim|clean}"
    ;;
esac
