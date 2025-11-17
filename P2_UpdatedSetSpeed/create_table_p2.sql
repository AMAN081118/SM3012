CREATE TABLE IF NOT EXISTS speed_log_p2 (
    tick INT,
    cmd INT,
    accel INT,
    decel INT,
    pause INT,
    speed INT,
    effective_delta INT,
    state_label TEXT
);
