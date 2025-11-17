#include "railroad1_types.h"
#include "railroad1.h"

// global memory for the railroad1 node
static Railroad1__railroad1_mem rr_mem;

// initialize
void railroad1_init() {
    Railroad1__railroad1_reset(&rr_mem);
}

// step function wrapper
void railroad1_step(int aw, int ae,
                    int *sw, int *se,
                    int *gw, int *ge)
{
    Railroad1__railroad1_out out;

    Railroad1__railroad1_step(aw, ae, &out, &rr_mem);

    *sw = out.sw;
    *se = out.se;
    *gw = out.gw;
    *ge = out.ge;
}
