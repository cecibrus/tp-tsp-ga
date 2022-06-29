#ifndef ALLINC
#define ALLINC

#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

//#define CITIES 512
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
#define V 13
#define INT_MAX 99999

struct Individual{
	char route[V];
	int fitness;
};

struct Population{
	Individual pop[POP_SIZE];
};


int map[V][V] = {
{INT_MAX, 2451, 713, 1018, 1631, 1374, 2408, 213, 2571, 875, 1420, 2145, 1972},
{2451, INT_MAX, 1745, 1524, 831, 1240, 959, 2596, 403, 1589, 1374, 357, 579},
{713, 1745, INT_MAX, 355, 920, 803, 1737, 851, 1858, 262, 940, 1453, 1260},
{1018, 1524, 355, INT_MAX, 700, 862, 1395, 1123, 1584, 466, 1056, 1280, 987},
{1631, 831, 920, 700, INT_MAX, 663, 1021, 1769, 949, 796, 879, 586, 371},
{1374, 1240, 803, 862, 663, INT_MAX, 1681, 1551, 1765, 547, 225, 887, 999},
{2408, 959, 1737, 1395, 1021, 1681, INT_MAX, 2493, 678, 1724, 1891, 1114, 701},
{213, 2596, 851, 1123, 1769, 1551, 2493, INT_MAX, 2699, 1038, 1605, 2300, 2099},
{2571, 403, 1858, 1584, 949, 1765, 678, 2699, INT_MAX, 1744, 1645, 653, 600},
{875, 1589, 262, 466, 796, 547, 1724, 1038, 1744, INT_MAX, 679, 1272, 1162},
{1420, 1374, 940, 1056, 879, 225, 1891, 1605, 1645, 679, INT_MAX, 1017, 1200},
{2145, 357, 1453, 1280, 586, 887, 1114, 2300, 653, 1272, 1017, INT_MAX, 504},
{1972, 579, 1260, 987, 371, 999, 701, 2099, 600, 1162, 1200, 504, INT_MAX},
};

//define the city names, so we can create the gnomes
char CITIES []= "ABCDEFGHIJKLM";


#endif
