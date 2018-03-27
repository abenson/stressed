#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modules.h"

#include "modules/cpu.h"

/*
	const char *name;
	int (*init)(int,char**, FILE*);
	int (*help)(FILE*);
	int (*run)(FILE*);
*/

Module Modules[] = {
	{"cpu", cpu_init, cpu_help, cpu_run},
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