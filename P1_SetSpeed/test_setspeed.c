#include <stdio.h>

// Wrapper function prototypes
void setspeed_init();
int setspeed_step(int cmd, int accel, int decel);

int main() {

    setspeed_init();

    // Test sequence: cmd, accel, decel
    int inputs[][3] = {
        {0, 5, 5},
        {20, 5, 5},
        {20, 5, 5},
        {50, 10, 10},
        {50, 10, 10},
        {10, 5, 5},
        {0, 5, 5}
    };

    int n = sizeof(inputs) / sizeof(inputs[0]);

    printf("Tick | cmd | accel | decel | speed\n");
    printf("------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int speed = setspeed_step(inputs[i][0], inputs[i][1], inputs[i][2]);
        printf("%4d | %3d | %5d | %5d | %5d\n",
               i,
               inputs[i][0], inputs[i][1], inputs[i][2],
               speed);
    }

    return 0;
}
