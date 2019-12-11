#include <stdio.h>

#include "xmalloc.h"
#include "fetch-line.h"
#include "linkedlist.h"
#include "evolution.h"

#include "read.h"

#define BUFLEN 1024

static int get_world_dimens(world *world, char *str, int lineno)
{
	if(sscanf(str, "World %d %d", &world->world_h, &world->world_w) == 2)
		return 1;
	else{
		fprintf(stderr, "stdin:line %d: invalid World dimensions\n", lineno);
		return 0;
	}
}

static int get_eden_dimens(world *world, char *str, int lineno)
{
	if(sscanf(str, "Eden %d %d", &world->eden_h, &world->eden_w) == 2)
		return 1;
	else{
		fprintf(stderr, "stdin:line %d: invalid Eden dimensions\n", lineno);
		return 0;
	}
}

static int get_plant_energy(world *world, char *str, int lineno)
{
	if(sscanf(str, "Plant Energy %d", &world->plant_energy) == 1)
		return 1;
	else{
		fprintf(stderr, "stdin:line %d: invalid Plant Energy\n", lineno);
		return 0;
	}
}


static int get_reproduction_threshold(world *world, char *str, int lineno)
{
	if(sscanf(str, "Reproduction Threshold %d", &world->reproduction_threshold) == 1)
		return 1;
	else{
		fprintf(stderr, "stdin:line %d: invalid Reproduction Threshold\n", lineno);
		return 0;
	}
}

static animal *get_animal_specs(char *str, int lineno)
{
	animal *animal;
	int i, j, d, e, genes[8], r;
	r = sscanf(str, "(%d %d) %d %d | %d %d %d %d %d %d %d %d |",
			&i, &j, &d, &e, 
			&genes[0], &genes[1], &genes[2], &genes[3],
			&genes[4], &genes[5], &genes[6], &genes[7]);

	if(r == 12)
	{
		animal = xmalloc(sizeof(*animal));
		animal->i = i;
		animal->j = j;
		animal->d = d;
		animal->e = e;
		int k;
		for(k = 0; k < 8; k++)
			animal->genes[k] = genes[k];
		return animal;
	} else{
		fprintf(stderr, "stdin:line %d: invalid Animal Specs\n", lineno);
		return NULL;
	}
}

static char *fetch_line_aux(char *buf, int buflen, FILE *stream, int *lineno)
{
	char *s = fetch_line(buf, buflen, stream, lineno);
	if(s == NULL)
		fprintf(stderr, "stdin:line %d: premature end of input\n", *lineno);
	return s;
}

int read_wdf(world *world)
{
	int animal_count = 0;
	char buf[BUFLEN];
	animal *ani;
	int lineno = 0;
	char *s;

	int result = 
		(s = fetch_line_aux(buf, BUFLEN, stdin, &lineno)) &&
		get_world_dimens(world, s, lineno)		  &&
		(s = fetch_line_aux(buf, BUFLEN, stdin, &lineno)) &&
		get_eden_dimens(world, s, lineno)		  &&
		(s = fetch_line_aux(buf, BUFLEN, stdin, &lineno)) &&
		get_plant_energy(world, s, lineno)		  &&
		(s = fetch_line_aux(buf, BUFLEN, stdin, &lineno)) &&
		get_reproduction_threshold(world, s, lineno);

	if(!result)
		return 0;
	
	world->herd = NULL;
	while((s = fetch_line(buf, BUFLEN, stdin, &lineno)) != NULL)
	{
		if((ani = get_animal_specs(s, lineno)) == NULL)
			return 0;
		else{
			//fprintf(stderr, "HERD HEAD: %p\n", world->herd);
			world->herd = ll_push(world->herd, ani);

			animal *tt = (animal *)world->herd;
			//fprintf(stderr, "NEW ANIMAL: %d %d %d %d\n", ani->i, ani->j, ani->d, ani->e);
		
			animal_count++;
		}
	}

	fprintf(stderr, "# %d animal%s read from the input\n",
		animal_count, animal_count == 1 ? "" : "s");

	return 1;
}
