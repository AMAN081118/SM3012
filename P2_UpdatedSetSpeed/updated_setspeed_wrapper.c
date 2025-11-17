#include "updated_setspeed_types.h"
#include "updated_setspeed.h"

// Global memory
static Updated_setspeed__updated_setspeed_mem uss_mem;

// Initialize
void updated_setspeed_init() {
    Updated_setspeed__updated_setspeed_reset(&uss_mem);
}

// Step function
void updated_setspeed_step(int cmd, int accel, int decel, int pause,
                           int *speed, int *effective_delta) {

    Updated_setspeed__updated_setspeed_out out;

    // Correct order:
    // Updated_setspeed__updated_setspeed_step(cmd, accel, decel, pause, &out, &uss_mem);

    Updated_setspeed__updated_setspeed_step(cmd, accel, decel, pause,
                                            &out,
                                            &uss_mem);

    *speed = out.speed;
    *effective_delta = out.effective_delta;
}
