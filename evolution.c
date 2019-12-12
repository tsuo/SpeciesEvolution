/*
* DAN TRAN
* INTRO COMPUTATIONAL SCIENCE 
* The Evolution of Species Project
*
* not implemented: world-to-eps[ch]  //17.9
*
* Basic simulation works but there are still some seg fault bugs
*/


#include <stdio.h>

#include "evolution.h"

#include "xmalloc.h"
#include "array.h"
#include "random.h"
#include "read.h"
#include "write.h"
#include "linkedlist.h"
#include "fetch-line.h"

#define MAX(a,b)  ((a) > (b) ? (a) : (b))

typedef struct{
	int i;
	int j;
}point;

static void free_herd(conscell *herd)
{	
	conscell *p;
	for(p = herd; p != NULL; p = p->next)
		free(p->data);
	ll_free(herd);
}

static int dead_or_alive(const void *aa)
{
	// custom implementation
	if(aa == NULL)
		return 0;
	animal *ani = (animal*)aa;
	return (ani->e <= 0) ? 1 : 0;
}

static conscell *remove_the_dead(conscell *herd)
{	
	conscell *p  = herd;
	while(p!=NULL)
	{
		animal *ani = (animal *)p->data;
		p = p->next;
	}
	conscell *dead = NULL;
	herd = ll_filter(herd, dead_or_alive, &dead);
	free_herd(dead);
	return herd;
}

int phi(int x, int L)
{
	int d = abs(x);
	if (d > L/2)
		d = L - d;
	return d;
}

static int nearer_the_eden(const void *aa, const void *bb, void *params)
{
	animal *a = (animal*)aa;
	animal *b = (animal*)bb;
	point *p = (point*)params;

	int d1 = MAX(abs(a->i - p->i), abs(a->j - p->j));
	int d2 = MAX(abs(b->i - p->i), abs(b->j - p->j));

	if(d1 < d2) 	return -1;
	if(d1 == d2) 	return 0;
	if(d1 > d2) 	return 1;
}

static void initialize_plants(world *world)
{
	if(world != NULL)
	{
		make_matrix(world->plants, world->world_h, world->world_w);
		
	}
}

static void add_plants(world *world)
{
	int i = randi(world->world_h);
	int j = randi(world->world_w);
	world->plants[i][j]++;
	
	// put additional plant in eden
	if(world->eden_h > 0 && world->eden_w > 0)
	{
		i = randi(world->eden_h) + (world->eden_h - 1)/2;
		j = randi(world->eden_w) + (world->eden_w - 1)/2;
		world->plants[i][j]++;
	}
}

static int gene_to_activate(int genes[8])
{
	int L = 0; //sum of genes values
	int r; //random gene to activate
	int i;	
	
	for(i = 0; i < 8; i++)
	{
		L += genes[i];
	}

	r = randi(L);
	for(i = 0; i < 8; i++)
	{
		r -= genes[i];
		if (r < 0)
			break;
	}

	return i;
}

static void turn(animal *animal)
{
	if(animal != NULL)
	{
		int k = gene_to_activate(animal->genes);
		animal->d = (animal->d + k) % 8;
	}
}

static void move(world *world, animal *animal)
{
	struct{
		int i;
		int j;
	} motion_vectors[] = {
		{  1, 0 },
		{  1, 1 },
		{  0, 1 },
		{ -1, 1 },
		{ -1, 0 },
		{ -1, -1 },
		{  0, -1 },
		{  1, -1 }};
	
	int y = animal->i + motion_vectors[animal->d].i;
	int x = animal->j + motion_vectors[animal->d].j;
	
	if(y<0)
		y += world->world_h;
	else if (y >= world->world_h)
		y -= world->world_h;
	if(x<0)
		x += world->world_w;
	else if (x >= world->world_w)
		x -= world->world_w;

	animal->i = y;
	animal->j = x;
}

static void feed(world *world, animal *animal)
{
	if(world != NULL && animal != NULL)
	{
		if(world->plants[animal->i][animal->j] > 0)
		{
			animal->e += world->plant_energy;
			world->plants[animal->i][animal->j]--;	
		}
	}
}

static animal *clone(animal *old)
{
	if(old == NULL) return NULL;
	
	animal *new = xmalloc(sizeof *new);
	new->i = old->i;
	new->j = old->j;
	new->d = old->d;
	new->e = old->e;
	new->genes[0] = old->genes[0];
	new->genes[1] = old->genes[1];
	new->genes[2] = old->genes[2];
	new->genes[3] = old->genes[3];
	new->genes[4] = old->genes[4];
	new->genes[5] = old->genes[5];
	new->genes[6] = old->genes[6];
	new->genes[7] = old->genes[7];
	
	return new;
}

static void mutate(int genes[8])
{	
	int k = randi(8);
	int rand = randi(3)-1;
	genes[k] = MAX(genes[k] + rand, 1); //new value has a min bound of 1
}

static void reproduce(world *world, animal *ani)
{
	ani->e /= 2;
	animal *new = clone(ani);
	mutate(new->genes);
	world->herd = ll_push(world->herd, new);
}

static void update_world(world *world, int i)
{
	
	conscell *p;
	world->herd = remove_the_dead(world->herd);
	for(p = world->herd; p != NULL; p = p->next)
	{	
		animal *a = (animal *)p->data;
			
		turn(a);
		
		move(world, a);	
		feed(world, a);
		a->e--;
		if(a->e >= world->reproduction_threshold)
			reproduce(world, a);
	}
	add_plants(world);
	
}

static void evolve(world *world, unsigned int n)
{
	unsigned int interval = MAX((n/5), 2);
	unsigned int i;
	for(i = 0; i < n; i++)
	{
		update_world(world, i);
		if(i%interval == 0)
			fprintf(stderr, "Iteration [%d]: %d\n", i+1, ll_length(world->herd));
	}
}

// world_to_eps() not implemented
static void evolve_with_figs(world *world, unsigned int n)
{
	char buf[16];
	unsigned long int i;	
	for(i = 0; i < n; i++)
	{
		sprintf(buf, "fid%04lu.eps", i);
		//world_to_eps(world, buf);
		if(i < n-1)
			update_world(world, i);
	}
}

static void show_usage(char *progname)
{
	fprintf(stderr, 
		"Usage: %s n [s] <infile >outfile\n" 
		"n >= 0 : (required) number of updates\n"
		"s  > 0 : (optional) random seed\n"
		"Reads World Definition from infile, performs\n"
		"n updates, and writes result to outfile\n", progname);
}

int main(int argc, char **argv)
{
	unsigned long int n;		// number of updates
	unsigned long int f = 0;	// number of figures to generate
	unsigned long int s = 1;
	world World;
	world *world = &World;
	int exit_status = EXIT_FAILURE;
	world->herd = NULL;
	world->plants = NULL;

	if(argc < 2 || argc > 3)
	{
		show_usage(argv[0]);
		goto cleanup;
	}
	
	if(sscanf(argv[1], "%lu", &n) != 1)
	{
		show_usage(argv[0]);
		goto cleanup;
	}

	if(argc > 2 && sscanf(argv[2], "%lu", &s) != 1)
	{
		show_usage(argv[0]);
		goto cleanup;
	}
	
	if(!read_wdf(world))
		goto cleanup;
	
	if(s>1)
		srand(s);	

	initialize_plants(world);

	evolve(world, n);
	
	//if(f>0)
	//	evolve_with_figs(world, f);
		
	point eden_center;
	eden_center.i = (world->world_h - 1)/2;
	eden_center.j = (world->world_w - 1)/2;
	world->herd = ll_sort(world->herd, nearer_the_eden, &eden_center);
	exit_status = EXIT_SUCCESS;

	write_wdf(world);
	fprintf(stderr, "SEED: %lu\n", s);

cleanup:
	free_matrix(world->plants);
	free_herd(world->herd);
	return exit_status;
}
