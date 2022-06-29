#include "allinc29.h"
#include <math.h>
#include <algorithm>
#include <iterator>
#include <omp.h>
using namespace std;



//==============================================================================
// PROTOTYPES

bool inList(Individual a, char city);
Individual crossoverPm (Individual a, Individual b);
void mutateW(Individual &a);
void mutate(Individual &a);
void mutatePop(Population &p);
int fitness(Individual a);
void sort(Population &p);
void printInd(Individual a);
void printPop(Population p);
void evolve(Population &p);

// =============================================================================
// EVOLUTION

bool inList(Individual a, char city)
{
	for (int n=0; n<V; n++) if (a.route[n]==city) return true;
	return false;
}

//Function to determine if a sequence is already in the population
bool inPop(Population &p, Individual a){
	
	for(int i = 0; i<POP_SIZE; i++){
		if (equal(begin(p.pop[i].route), end(p.pop[i].route), begin(a.route), end(a.route))){
			return true;
		}else{
			continue;
		}
	}
	return false;

}

Individual crossoverPm (Individual a, Individual b)
{
	int x = rand()%V;
	if (x>V/2) x=x-V/4;
	int y = rand()%V;
	if (y<V/2) y=y+V/4;
	if (x>y)
	{
		int temp = x;
		x=y;
		y=temp;
	}

	Individual c;
	for (int n=0; n<V; n++) c.route[n]='0';
	for (int n=x; n<=y; n++) c.route[n]=a.route[n];

		for (int i=0; i<V; i++)
		{
			if (c.route[i]=='0')
			{
				for (int k=0; k<V; k++) if (!inList (c, a.route[k])) c.route[i]=a.route[k];
			}
		}


	return c;
}

Individual crossoverInj (Individual a, Individual b)
{
	int q = rand()%V/3;

	int x = rand()%V;
	if (x>V/2) x=x-V/4;
	int y = rand()%V;
	if (y<V/2) y=y+V/4;
	if (x>y)
	{
		int temp = x;
		x=y;
		y=temp;
	}

	Individual c;
	for (int n=0; n<V; n++) c.route[n]='0';

	Individual ab;
	for (int n=0; n<V; n++) ab.route[n]='0';
	for (int n=x; n<=y; n++) ab.route[n]=a.route[n];

	for (int n=0; n<=q; n++)
	{
		if (!inList(ab, b.route[n])) c.route[n]=b.route[n];
	}

	for (int h=q+1; h<(y-x); h++) c.route[h]=a.route[h];

		for (int i=0; i<V; i++)
		{
			if (c.route[i]=='0')
			{
				for (int k=0; k<V; k++) if (!inList (c, a.route[k])) c.route[i]=a.route[k];
			}
		}

	return c;
}

void mutateW(Individual &a)
{
	Individual candidate = a;
	for (int i=0; i<MUTATEW_POINTS; i++)
	{
		int k=rand()%(V-1)+1;
		int temp=candidate.route[0];
		candidate.route[0]=candidate.route[k];
		candidate.route[k]=temp;
		if (fitness(candidate)<fitness(a)) a=candidate;
	}

}

void mutate(Individual &a)
{
	Individual candidate = a;
	for (int i=0; i<MUTATE_POINTS; i++)
	{
		int q = rand()%V;
		int d = rand()%V;
		int chance = rand()%2;
		if (chance==1)
		{
			int temp = candidate.route[q];
			candidate.route[q]=candidate.route[d];
			candidate.route[d]=temp;
		}
		if (fitness(candidate)<fitness(a)) a=candidate;
	}
}

void mutatePop(Population &p)
{
	int flip;
	for (int i=0; i<POP_SIZE; i++)
	{
		if (MUTATION_TYPE==0) mutate(p.pop[i]); else mutateW(p.pop[i]);
	}
}

int fitness(Individual a)
{
	int map_copy[V][V];
	memcpy(map_copy,map, V*V*sizeof(int));

	//Calculate the distance between the last city and the first city
	int return_distance=map_copy[a.route[V-1] - 65][a.route[0] - 65];
	if(return_distance == INT_MAX)
		return INT_MAX;
	int f = 0;
	for (int i = 0; i < V - 1; i++) {
		//Misma ciudad
		if(a.route[i + 1] - 65 == a.route[i] - 65 )
			return INT_MAX;

		if (map_copy[a.route[i] - 65][a.route[i + 1] - 65] == INT_MAX)
			return INT_MAX;

		f += map_copy[a.route[i] - 65][a.route[i + 1] - 65];

		//Set to INT_MAX all road to current city
		for(int j=0;j<V;j++)
		map_copy[j][a.route[i] - 65]=INT_MAX;
		
	}
	a.fitness = f + return_distance;
	return f + return_distance;
}

void sort(Population &p)
{
	int c=0;
	Individual temp;
	while (c<SORT_LIMIT)
	{
		for (int i=0; i<(POP_SIZE - 1); i++)
		{
			if (fitness(p.pop[i]) > fitness(p.pop[i+1]))
			{
				temp=p.pop[i];
				p.pop[i]=p.pop[i+1];
				p.pop[i+1]=temp;
			}
		}
	c++;
	}
}

int getFreeIndex(Individual a)
{
	for (int i=0; i<V; i++)
	{
		if (a.route[i]=='0') return i;
	}
	return -1;
}

void printInd(Individual a)
{

	for (int i=0; i<V; i++) cout << a.route[i] << "->";

}

void printPop(Population p)
{
	for (int i=0; i<POP_SIZE; i++)
	{
		printInd(p.pop[i]);
		cout << "x | F=" << fitness(p.pop[i]) << endl;
	}
}

void evolve(Population &p)
{
	mutatePop(p);

	Individual offspring[POP_SIZE/2];
	Individual winners[TOURN_N];
	Individual temp;
	int g=0;
	int c=0;

	#	pragma omp parallel
	while (g<GENERATIONS)
	{

		if (SELECTION_TYPE==0)
		//FIXED RANK SELECTION
		{
			for (int i=0; i<POP_SIZE/2; i++){
				int flip = rand()%2;
				if (flip==0) offspring[i]=crossoverInj (p.pop[i+1], p.pop[i]); else
						offspring[i]=crossoverPm (p.pop[i], p.pop[i+1]);
			}
	    } else if (SELECTION_TYPE==1)
		//TOURNAMENT SELECTION
		{
			for (int i=0; i<POP_SIZE/2; i++)
			{
				for (int j=0; j<=TOURN_N; j++)
				{
					winners[j]=p.pop[rand()%(POP_SIZE)];
				}
				//sort winners
				while (c<SORT_LIMIT)
				{
					for (int l=0; l<TOURN_N - 1; l++)
					{
						if (fitness(winners[l]) > fitness(winners[l+1]))
							{
								temp=winners[l];
								winners[l]=winners[l+1];
								winners[l+1]=temp;
							}
					}
				c++;
				}

				int flip = rand()%2;
				if (flip==0) offspring[i]=crossoverInj(winners[0], winners[1]); else
						offspring[i]=crossoverPm (winners[1], winners[0]);



			}

		}
		sort(p);
		

		for (int i=0; i<POP_SIZE/2; i++){
			for (int j=0; j<POP_SIZE; j++){
				if (fitness(offspring[i]) < fitness(p.pop[j]) && !inPop(p,offspring[i])){
					p.pop[j]=offspring[i];
					break;
				}
			}
		}




	printInd(p.pop[0]);
	cout << " | GEN: " << g << "  | F=" << fitness(p.pop[0]) << endl << endl;

	g++;
	sort(p);
	}

}



// =============================================================================
// MAIN

int main()
{
	srand(time(NULL));

	//Population is created
	Population population1;
	Individual indi[POP_SIZE];
	//int catalog[50];
	char ins;
	//for (int i=1; i<=V; i++) catalog[i]=i;

	//gnomes are filled with '0's for all individuals
	for (int k=0; k<POP_SIZE; k++)
	{
		for (int j=0; j<V; j++) indi[k].route[j]='0';

	}

	//here is where the real initial population is created randomly
	for (int k=0; k<POP_SIZE; k++)
	{
		while(inList (indi[k], '0'))
		{
			ins = CITIES[(rand()%(V))];
			for (int j=0; j<V; j++){
				if (!inList (indi[k], ins)) 
					indi[k].route[getFreeIndex(indi[k])]=ins;
			}
				
		}

	}

	for (int r=0; r<POP_SIZE; r++) population1.pop[r]=indi[r];

	sort(population1);
	cout << "Initial sorted population: " << endl;
	printPop(population1);
	cout << endl << "Starting evolution..." << endl << endl;
    
	#	pragma omp parallel num_threads(thread_count)
	evolve(population1);

	return 0;
}
