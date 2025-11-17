#include "setspeed_types.h"
#include "setspeed.h"

// Global memory for the setspeed node
static Setspeed__setspeed_mem ss_mem;

// Initialize the node
void setspeed_init() {
    Setspeed__setspeed_reset(&ss_mem);
}

// One computation step
int setspeed_step(int cmd, int accel, int decel) {
    Setspeed__setspeed_out out;
    Setspeed__setspeed_step(cmd, accel, decel, &out, &ss_mem);
    return out.speed;
}
