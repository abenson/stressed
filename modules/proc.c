#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "proc.h"

static int numProc = 1;
static int procLife = 1;

int proc_init(char** argv, FILE*fp)
{
	int i;

	for(i=0; argv[i] != NULL; i++) {
		if(strcmp(argv[i], "-t") == 0) {
			if(argv[++i] != NULL) {
				procLife = atoi(argv[i]);
				if(procLife <= 0) {
					fprintf(fp, "proc: init failed, minimum duration of proceses is 1s\n");
					return 2;
				}
				continue;
			} else {
				fprintf(fp, "proc: init failed, missing argument after -t\n");
				return 1;
			}
		} if(strcmp(argv[i], "-n") == 0) {
			if(argv[++i] != NULL) {
				numProc = atoi(argv[i]);
				if(numProc <= 0) {
					fprintf(fp, "proc: init failed, minimum number of processes is 1\n");
					return 2;
				}
				continue;
			} else {
				fprintf(fp, "proc: init failed, missing argument after -t\n");
				return 1;
			}
		} else {
			fprintf(fp, "proc: didn't recognize argument %s\n", argv[i]);
			return 1;
		}
	}
	fprintf(fp, "proc: init, %d processes, %d seconds each\n", numProc, procLife);
	return 0;
}

int proc_help(FILE* fp)
{
	fprintf(fp, "proc:\n");
	fprintf(fp, "  -t <NUM>      Number of seconds per process.\n");
	fprintf(fp, "  -n <NUM>      Number of processes.\n\n");
	return 0;
}

int proc_run(FILE* fp)
{
	int i, pid;
	fprintf(fp, "proc: running!\n");

	for(i=0; i<numProc; i++) {
		pid = fork();
		if(pid == 0) {
			while(sleep(procLife) == 0) {
				pid = fork();
				if(pid > 0) {
					exit(0);
				}
			}
		}
	}

	wait(NULL);

	return 0;
}
