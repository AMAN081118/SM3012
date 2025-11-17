#include <stdio.h>

// Wrapper function prototypes
void updated_setspeed_init();
void updated_setspeed_step(int cmd, int accel, int decel, int pause,
                           int *speed, int *effective_delta);

int main() {

    updated_setspeed_init();

    // cmd, accel, decel, pause
    int inputs[][4] = {
        {0, 5, 5, 0},
        {20, 5, 5, 0},
        {20, 5, 5, 1},   // pause ON
        {20, 5, 5, 1},
        {20, 5, 5, 0},   // pause OFF
        {50, 10, 10, 0},
        {10, 5, 5, 0}
    };

    int n = sizeof(inputs) / sizeof(inputs[0]);

    printf("Tick | cmd | accel | decel | pause | speed | delta\n");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int speed, delta;
        updated_setspeed_step(
            inputs[i][0], inputs[i][1], inputs[i][2], inputs[i][3],
            &speed, &delta
        );

        printf("%4d | %3d | %5d | %5d | %5d | %5d | %5d\n",
               i,
               inputs[i][0], inputs[i][1], inputs[i][2], inputs[i][3],
               speed, delta
        );
    }

    return 0;
}
