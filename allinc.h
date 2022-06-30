#ifndef ALLINC
#define ALLINC

#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define POP_SIZE 10
#define TOURN_N 10
#define MUTATE_POINTS 1
#define MUTATEW_POINTS 4
#define SORT_LIMIT 10
#define FIT_LIMIT 20
#define GENERATIONS 50
#define SELECTION_TYPE 0		// 0 - fixed rank, 1 - tournament
#define CROSSOVER_TYPE 1		// 0 - PM, 1 - INJ
#define MUTATION_TYPE 0
#define V 1024
#define INT_MAX 99999

struct Individual{
	char route[V];
	int fitness;
};

struct Population{
	Individual pop[POP_SIZE];
};

struct City
{
	int name;
	int x;
	int y;
};

// int map[V][V] = {
// {INT_MAX, 64, 378, 519, 434, 200},
// {64, INT_MAX, 318, 455, 375, 164},
// {378, 318, INT_MAX, 170, 265, 344},
// {519, 455, 170, INT_MAX, 223, 428},
// {434, 375, 265, 223, INT_MAX, 273},
// {200, 164, 344, 428, 273, INT_MAX},
// };

//define the city names, so we can create the gnomes
char CITIES []= "ABCDEF";


#endif
