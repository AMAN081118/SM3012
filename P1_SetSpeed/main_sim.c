#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setspeed_init();
int setspeed_step(int cmd, int accel, int decel);

int main(int argc, char **argv) {

    const char *infile = (argc >= 2) ? argv[1] : "input.csv";
    const char *outfile = (argc >= 3) ? argv[2] : "output.csv";

    FILE *fin = fopen(infile, "r");
    if (!fin) {
        perror("Error opening input.csv");
        return 1;
    }

    FILE *fout = fopen(outfile, "w");
    if (!fout) {
        perror("Error opening output.csv");
        fclose(fin);
        return 1;
    }

    fprintf(fout, "tick,cmd,accel,decel,speed\n");

    setspeed_init();

    int tick = 0;
    char line[256];

    while (fgets(line, sizeof(line), fin)) {
        if (line[0] == '#' || strlen(line) < 3)
            continue;

        int cmd, accel, decel;
        if (sscanf(line, "%d,%d,%d", &cmd, &accel, &decel) != 3)
            continue;

        int speed = setspeed_step(cmd, accel, decel);

        fprintf(fout, "%d,%d,%d,%d,%d\n",
                tick, cmd, accel, decel, speed);

        tick++;
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
