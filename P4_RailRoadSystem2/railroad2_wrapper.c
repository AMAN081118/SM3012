#include "railroad2_types.h"
#include "railroad2.h"

/* Global memory for the railroad2 node */
static Railroad2__railroad2_mem rr2_mem;

/* init */
void railroad2_init() {
    Railroad2__railroad2_reset(&rr2_mem);
}

/* step: approach_w, approach_e as ints (0/1) */
/* returns state_w, state_e, grant_w, grant_e via pointers */
void railroad2_step(int approach_w, int approach_e,
                    int *state_w, int *state_e,
                    int *grant_w, int *grant_e) {
    Railroad2__railroad2_out out;
    Railroad2__railroad2_step(approach_w, approach_e, &out, &rr2_mem);
    *state_w = out.st_w;
    *state_e = out.st_e;
    *grant_w = out.grant_w;
    *grant_e = out.grant_e;
}
