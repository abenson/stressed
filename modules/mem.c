#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "mem.h"

static int numMegs = 1;

int mem_init(char **argv, FILE *fp)
{
	int i;

	for(i=0; argv[i] != NULL; i++) {
		if(strcmp(argv[i], "-m") == 0) {
			if(argv[++i] != NULL) {
				numMegs = atoi(argv[i]);
				if(numMegs <= 0) {
					fprintf(fp, "mem: init failed, \n");
					return 2;
				}
			} else {
				fprintf(fp, "mem: init failed, missing argument after -m\n");
				return 1;
			}
		} else {
			fprintf(fp, "mem: didn't recognize argument %s\n", argv[i]);
			return 1;
		}
	}
	fprintf(fp, "mem: init, %d megabytes\n", numMegs);
	return 0;
}

int mem_help(FILE *fp)
{
	fprintf(fp, "mem:\n");
	fprintf(fp, "  -m <NUM>      Number of megabytes to grab/hold.\n\n");
	return 0;
}

int mem_run(FILE *fp)
{
	char *memories;

	memories = malloc(numMegs * 1024 * 1024);
	if(memories == NULL) {
		fprintf(fp, "mem: couldn't allocate %dMB!", numMegs);
		return 1;
	}

	fprintf(fp, "mem: running!\n");

	while(sleep(600) == 0) ;

	free(memories);
	return 0;
}
