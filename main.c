#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgen.h>

#include "modules.h"

static void print_overall_help(char *arg0, FILE *fp)
{
	int i;
	fprintf(fp, "%s: [options] <module> [module options]\n", arg0);
	fprintf(fp, "Options:\n");
	fprintf(fp, " -o file               File to write module log to (default: stdout)\n\n");
	fprintf(fp, " -h                    Show help for all available modules\n\n");
	fprintf(fp, "available modules: ");
	for(i=0; Modules[i].name != NULL; i++) {
		fprintf(fp, "%s ", Modules[i].name);
	}
	fprintf(fp, "\n");
}

int main(int argc, char *argv[])
{
	FILE *log;
	int i, modIndex, status;

	if(argc < 2) {
		print_overall_help(basename(argv[0]), stdout);
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
		} else if(strcmp(argv[i], "-h") == 0) {
			module_help_all(stdout);
			return 0;
		}
		i++;
	}

	modIndex = module_byname(argv[i]);
	if(modIndex < 0) {
		fprintf(stdout, "Can't find module by the name of '%s'!\n", argv[i]);
		return 1;
	}

	status = Modules[modIndex].init(argv+i+1, stdout);

	if(status != 0) {
		fprintf(stdout, "%s returned error %d.\n", Modules[modIndex].name, status);
		return 1;
	}

	Modules[modIndex].run(stdout);

	return 0;
}
