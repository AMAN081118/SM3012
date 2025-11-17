#!/bin/bash

SERVICE_POSTGRES="postgresql"
SERVICE_GRAFANA="grafana-server"

start_services() {
    echo "Starting PostgreSQL..."
    sudo service $SERVICE_POSTGRES start

    echo "Starting Grafana..."
    sudo service $SERVICE_GRAFANA start
}

stop_services() {
    echo "Stopping Grafana..."
    sudo service $SERVICE_GRAFANA stop

    echo "Stopping PostgreSQL..."
    sudo service $SERVICE_POSTGRES stop
}

run_test() {
    echo "===== TEST: $1 ====="
    cd "$1" || exit
    ./do.sh test
    cd ..
}

run_sim() {
    echo "===== SIM: $1 ====="
    cd "$1" || exit
    ./do.sh sim
    cd ..
}

case "$1" in

start)
    start_services
    ;;

stop)
    stop_services
    ;;

run_all_test)
    run_test P1_SetSpeed
    run_test P2_UpdatedSetSpeed
    run_test P3_RailRoadSystem1
    run_test P4_RailRoadSystem2
    ;;

run_all_sim)
    run_sim P1_SetSpeed
    run_sim P2_UpdatedSetSpeed
    run_sim P3_RailRoadSystem1
    run_sim P4_RailRoadSystem2
    ;;

*)
    echo "Usage: ./sm3012.sh {start|stop|run_all_test|run_all_sim}"
    ;;
esac
