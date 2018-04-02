#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modules.h"

#include "modules/cpu.h"
#include "modules/mem.h"
#include "modules/proc.h"

/*
	const char *name;
	int (*init)(int,char**, FILE*);
	int (*help)(FILE*);
	int (*run)(FILE*);
*/

Module Modules[] = {
	{"cpu", cpu_init, cpu_help, cpu_run},
	{"mem", mem_init, mem_help, mem_run},
	{"proc", proc_init, proc_help, proc_run},
	{NULL, NULL, NULL, NULL}
};

int module_byname(const char *name)
{
	int i;
	for(i=0; Modules[i].name != NULL; i++) {
		if(strcmp(name, Modules[i].name) == 0) {
			return i;
		}
	}
	return -1;
}

void module_help_all(FILE *fp)
{
	int i;
	for(i=0; Modules[i].name != NULL; i++) {
		Modules[i].help(fp);
	}
}

void module_help(FILE * fp, const char *name)
{
	int i;
	for(i=0; Modules[i].name != NULL; i++) {
		if(strcmp(name, Modules[i].name) == 0) {
			Modules[i].help(fp);
			return;
		}
	}
}
