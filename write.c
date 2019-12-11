#include <stdio.h>
#include "evolution.h"
#include "linkedlist.h"

#include "write.h"

static void print_animal(animal *animal)
{
	if(animal != NULL)
		printf(	"(%d %d) %d %d | %d %d %d %d %d %d %d %d |\n",
			animal->i, animal->j, animal->d, animal->e,
			animal->genes[0], animal->genes[1], animal->genes[2], animal->genes[3],
			animal->genes[4], animal->genes[5], animal->genes[6], animal->genes[7]);
}

static void print_herd(conscell *herd)
{
	conscell *p = herd;
	animal *tempa;
	while(p != NULL)
	{
		tempa = (animal *)(p->data);
		print_animal(tempa);
		p = p->next;
	}
}

void write_wdf(world *world)
{
	printf(	"World %d %d\t# h x w\n"
		"Eden %d %d\t# h x w\n"
		"Plant Energy %d\n"
		"Reproduction Threshold %d\n\n",
		world->world_h, world->world_w, 
		world->eden_h, world->eden_w,
		world->plant_energy, world->reproduction_threshold);

	printf(	"#  (i j) d e | g[0] g[1] g[2] g[3] g[4] g[5] g[6] g[7] |\n\n");
	print_herd(world->herd);
	printf(	"\n# animal count: %d\n", ll_length(world->herd));
	
}


