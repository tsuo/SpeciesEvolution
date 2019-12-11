#include <stdlib.h>
#include "random.h"

double randf(double a, double b)
{
	double r = (double)rand()/RAND_MAX;
	
	return a + (b-a) * r; 
}

int randi(int max)
{
	return rand()/(RAND_MAX/max + 1);
}
