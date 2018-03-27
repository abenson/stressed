#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modules.h"

#define PROGRAM_NAME "stress"

static void print_overall_help(char *arg0, FILE *fp)
{
	int i;
	fprintf(fp, "%s: [options] <module> [module options]\n", arg0);
	fprintf(fp, "Options:\n");
	fprintf(fp, " -o file               File to write module log to (default: stdout)\n\n");
	fprintf(fp, "available modules: ");
	for(i=0; Modules[i].name != NULL; i++) {
		fprintf(fp, "%s ", Modules[i].name);
	}
	fprintf(fp, "\n");
}

int main(int argc, char *argv[])
{
	FILE *log;
	int i, modIndex;
	if(argc < 2) {
		print_overall_help(PROGRAM_NAME, stdout);
		return 0;
	}


	i=1;
	while(strncmp(argv[i], "-", 1) == 0) {
		if(strcmp(argv[i], "-o") == 0) {
			log = fopen(argv[++i], "w");
			if(log == NULL) {
				fprintf(stderr, "couldn't open '%s' for writing\n", argv[i]);
				return 1;
			}
		}
		i++;
	}

	modIndex = module_byname(argv[i]);
	if(modIndex < 0) {
		fprintf(stdout, "Can't find module by the name of '%s'!\n", argv[i]);
		return 1;
	}

	Modules[modIndex].init(argv+i+1, stdout);

	Modules[modIndex].run(stdout);

	return 0;
}
