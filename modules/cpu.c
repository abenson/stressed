#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"

int cpu_init(char** argv, FILE*fp)
{
	int i;

	fprintf(fp, "cpu: init\n");
	for(i=0; argv[i] != NULL; i++) {
		fprintf(fp, " %s\n", argv[i]);
	}
	return 0;
}

int cpu_help(FILE* fp)
{
	fprintf(fp, "cpu: help\n");
	return 0;
}

int cpu_run(FILE* fp)
{
	fprintf(fp, "cpu: run\n");
	return 0;
}
