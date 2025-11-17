#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void railroad2_init();
void railroad2_step(int approach_w, int approach_e,
                    int *state_w, int *state_e,
                    int *grant_w, int *grant_e);

int main(int argc, char **argv) {
    const char *infile = (argc >= 2) ? argv[1] : "input_p4.csv";
    const char *outfile = (argc >= 3) ? argv[2] : "output_p4.csv";

    FILE *fin = fopen(infile, "r");
    if (!fin) { perror("open input_p4.csv"); return 1; }
    FILE *fout = fopen(outfile, "w");
    if (!fout) { perror("open output_p4.csv"); fclose(fin); return 1; }

    fprintf(fout, "tick,approach_w,approach_e,state_w,state_e,grant_w,grant_e\n");

    railroad2_init();

    char line[256];
    int tick = 0;
    while (fgets(line, sizeof(line), fin)) {
        if (line[0] == '#' || strlen(line) < 3) continue;
        int aw, ae;
        if (sscanf(line, "%d,%d", &aw, &ae) != 2) continue;
        int sw, se, gw, ge;
        railroad2_step(aw, ae, &sw, &se, &gw, &ge);
        fprintf(fout, "%d,%d,%d,%d,%d,%d,%d\n", tick, aw, ae, sw, se, gw, ge);
        tick++;
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
