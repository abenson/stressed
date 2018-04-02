#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <sys/types.h>
#include <unistd.h>

#include "cpu.h"

int numProc = 1;

int cpu_init(char** argv, FILE*fp)
{
	int i;

	for(i=0; argv[i] != NULL; i++) {
		if(strcmp(argv[i], "-n") == 0) {
			if(argv[++i] != NULL) {
				numProc = atoi(argv[i]);
				if(numProc <= 0) {
					fprintf(fp, "cpu: init failed, minimum number of proceses is 1\n");
					return 2;
				}
			} else {
				fprintf(fp, "cpu: init failed, missing argument after -n\n");
				return 1;
			}
		} else {
			fprintf(fp, "cpu: didn't recognize argument %s\n", argv[i]);
			return 1;
		}
	}
	fprintf(fp, "cpu: init, %d processes\n", numProc);
	return 0;
}

int cpu_help(FILE* fp)
{
	fprintf(fp, "cpu:\n");
	fprintf(fp, "  -n <NUM>      Number of processes to spawn.\n\n");
	return 0;
}

int cpu_run(FILE* fp)
{
	int i, r, pid;
	fprintf(fp, "cpu: running!\n");

	srand(time(NULL));
	for(;;) {
		r = rand();
		sqrtl(r);
	}

	return 0;
}
