#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void railroad1_init();
void railroad1_step(int aw, int ae,
                    int *sw, int *se,
                    int *gw, int *ge);

int main(int argc, char **argv)
{
    const char *infile  = (argc >= 2) ? argv[1] : "input_p3.csv";
    const char *outfile = (argc >= 3) ? argv[2] : "output_p3.csv";

    FILE *fin = fopen(infile, "r");
    if(!fin) { perror("input_p3.csv"); return 1; }

    FILE *fout = fopen(outfile, "w");
    if(!fout) { perror("output_p3.csv"); fclose(fin); return 1; }

    fprintf(fout, "tick,aw,ae,sw,se,gw,ge\n");

    railroad1_init();

    char line[256];
    int tick = 0;

    while(fgets(line, sizeof(line), fin)) 
    {
        if(line[0]=='#' || strlen(line)<3) continue;

        int aw, ae;
        if(sscanf(line, "%d,%d", &aw, &ae)!=2) continue;

        int sw,se,gw,ge;
        railroad1_step(aw, ae, &sw, &se, &gw, &ge);

        fprintf(fout, "%d,%d,%d,%d,%d,%d,%d\n",
                tick, aw, ae, sw, se, gw, ge);

        tick++;
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
