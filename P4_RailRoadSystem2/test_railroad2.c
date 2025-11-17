#include <stdio.h>

void railroad2_init();
void railroad2_step(int approach_w, int approach_e,
                    int *state_w, int *state_e,
                    int *grant_w, int *grant_e);

int main() {
    railroad2_init();

    int inputs[][2] = {
        {0,0},
        {1,0},
        {0,1},
        {1,1},
        {0,0},
        {0,1},
        {1,0},
        {0,0}
    };
    int n = sizeof(inputs)/sizeof(inputs[0]);

    printf("tick | app_w app_e | st_w st_e | g_w g_e\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < n; ++i) {
        int sw, se, gw, ge;
        railroad2_step(inputs[i][0], inputs[i][1], &sw, &se, &gw, &ge);
        printf("%4d |   %d     %d   |   %d    %d  |  %d   %d\n",
               i, inputs[i][0], inputs[i][1], sw, se, gw, ge);
    }
    return 0;
}
