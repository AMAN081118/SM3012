#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void updated_setspeed_init();
void updated_setspeed_step(int cmd, int accel, int decel, int pause,
                           int *speed, int *effective_delta);

int main(int argc, char **argv) {

    const char *infile = (argc >= 2) ? argv[1] : "input_p2.csv";
    const char *outfile = (argc >= 3) ? argv[2] : "output_p2.csv";

    FILE *fin = fopen(infile, "r");
    if (!fin) {
        perror("Error opening input_p2.csv");
        return 1;
    }

    FILE *fout = fopen(outfile, "w");
    if (!fout) {
        perror("Error opening output_p2.csv");
        fclose(fin);
        return 1;
    }

    fprintf(fout, "tick,cmd,accel,decel,pause,speed,effective_delta\n");

    updated_setspeed_init();

    int tick = 0;
    char line[256];

    while (fgets(line, sizeof(line), fin)) {
        if (line[0] == '#' || strlen(line) < 3)
            continue;

        int cmd, accel, decel, pause;
        if (sscanf(line, "%d,%d,%d,%d", &cmd, &accel, &decel, &pause) != 4)
            continue;

        int speed, delta;
        updated_setspeed_step(cmd, accel, decel, pause, &speed, &delta);

        fprintf(fout, "%d,%d,%d,%d,%d,%d,%d\n",
                tick, cmd, accel, decel, pause, speed, delta);

        tick++;
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
