#include <stdio.h>

void railroad1_init();
void railroad1_step(int aw, int ae,
                    int *sw, int *se,
                    int *gw, int *ge);

int main() {

    railroad1_init();

    int inputs[][2] = {
        {0,0}, {1,0}, {0,1}, {1,1}, {0,0},
        {0,1}, {1,0}, {1,1}, {0,0}, {0,0}
    };

    int count = sizeof(inputs)/sizeof(inputs[0]);

    printf("tick | aw ae | sw se | gw ge\n");
    printf("------------------------------\n");

    for(int i=0; i<count; i++) {
        int sw, se, gw, ge;
        railroad1_step(inputs[i][0], inputs[i][1], &sw, &se, &gw, &ge);

        printf("%4d | %d  %d | %d  %d | %d  %d\n",
               i, inputs[i][0], inputs[i][1], sw, se, gw, ge);
    }

    return 0;
}
