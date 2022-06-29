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
#define GENERATIONS 500
#define SELECTION_TYPE 0		// 0 - fixed rank, 1 - tournament
#define CROSSOVER_TYPE 1		// 0 - PM, 1 - INJ
#define MUTATION_TYPE 0
#define V 15
#define INT_MAX 99999

struct Individual{
	char route[V];
	int fitness;
};

struct Population{
	Individual pop[POP_SIZE];
};
int map[V][V] = {
{INT_MAX, 141, 134, 152, 173, 289, 326, 329, 285, 401, 388, 366, 343, 305, 276}, 
{141, INT_MAX, 152, 150, 153, 312, 354, 313, 249, 324, 300, 272, 247, 201, 176}, 
{134, 152, INT_MAX, 24, 48, 168, 210, 197, 153, 280, 272, 257, 237, 210, 181}, 
{152, 150, 24, INT_MAX, 24, 163, 206, 182, 133, 257, 248, 233, 214, 187, 158}, 
{173, 153, 48, 24, INT_MAX, 160, 203, 167, 114, 234, 225, 210, 190, 165, 137}, 
{289, 312, 168, 163, 160, INT_MAX, 43, 90, 124, 250, 264, 270, 264, 267, 249}, 
{326, 354, 210, 206, 203, 43, INT_MAX, 108, 157, 271, 290, 299, 295, 303, 287}, 
{329, 313, 197, 182, 167, 90, 108, INT_MAX, 70, 164, 183, 195, 194, 210, 201}, 
{285, 249, 153, 133, 114, 124, 157, 70, INT_MAX, 141, 147, 148, 140, 147, 134}, 
{401, 324, 280, 257, 234, 250, 271, 164, 141, INT_MAX, 36, 67, 88, 134, 150}, 
{388, 300, 272, 248, 225, 264, 290, 183, 147, 36, INT_MAX, 33, 57, 104, 124}, 
{366, 272, 257, 233, 210, 270, 299, 195, 148, 67, 33, INT_MAX, 26, 73, 96}, 
{343, 247, 237, 214, 190, 264, 295, 194, 140, 88, 57, 26, INT_MAX, 48, 71}, 
{305, 201, 210, 187, 165, 267, 303, 210, 147, 134, 104, 73, 48, INT_MAX, 30}, 
{276, 176, 181, 158, 137, 249, 287, 201, 134, 150, 124, 96, 71, 30, INT_MAX}
};
//define the city names, so we can create the gnomes
char CITIES []= "ABCDEFGHIJKLMNO";


#endif