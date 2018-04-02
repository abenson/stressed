#ifndef MODULES_H
#define MODULES_C

typedef struct {
	const char *name;
	int (*init)(char**, FILE*);
	int (*help)(FILE*);
	int (*run)(FILE*);
} Module;

extern Module Modules[];

int module_byname(const char *);

void module_help_all(FILE *);
void module_help(FILE *, const char *);

#endif