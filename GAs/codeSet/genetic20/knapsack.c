/*code derived from Github https://github.com/marcelocd/Knapsack-Genetic-	Algorithm. Modified by Yuzuo
/*
/*      
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define   NUMBER_OF_ITEMS   20
#define   KNAPSACK_CAPACITY 5
#define   POPULATION_SIZE   5
#define   MUTATION_PROB     0.1//bit flip, influence convergence. to low will cause high genetic similarity in a group, too high decrease convergence rate

//Structs
typedef struct{
	int n;
	short *compartment;
	float capacity;
}Knapsack;

typedef struct{
	float benefit;
	float weight;
}Item;

typedef struct{
	int gene_size;
	short *gene;
	float weight;
	float fitness;
	float mating_probability;
}Individual;

typedef struct{
	int size;
	Individual *individual;
}Population;

//-------------------------------------------

//Functions Prototypes ----------------------
//Initializing Functions --------------------
void Init_Default_Knapsack(Knapsack *);
void Init_Default_Items(Item *, Knapsack);
void Init_Population(Population *, Item *, Knapsack);

//Problem Solving Functions -----------------
int Random_Number(int, int);
bool mutateProbability();
float totalWeight(Individual, Item *);
float Fitness(Individual, Item *, Knapsack );
void Assign_Mating_Probability(Population *);
Individual Random_Selection(Population);
bool Individuals_Are_Equal(Individual, Individual);
Individual crossOver(Individual, Individual);
void Mutate(Individual *);
void Clear_Population(Population *);
Individual Genetic_Algorithm(Population, Item *, Knapsack);
void Fill_Knapsack(Knapsack *, Individual);
bool test( Population *);

//Menu Functions ----------------------------


//Printing Functions ------------------------
void Print_Individual(Individual);

//Control Functions -------------------------
void Control(Knapsack *, Item **);

//-------------------------------------------



//Functions Implementation ------------------
//Initializing Functions --------------------
void Init_Default_Knapsack(Knapsack *knapsack){
	knapsack->n = NUMBER_OF_ITEMS;
	knapsack->compartment = (short *) malloc(sizeof(short) * knapsack->n);
	knapsack->capacity = KNAPSACK_CAPACITY;
}


void Init_Default_Items(Item *item, Knapsack knapsack){
	item[0].weight = 3;
	item[0].benefit = 10;

	item[1].weight = 2;
	item[1].benefit = 20;
	
	item[2].weight = 3;
	item[2].benefit = 30;
	
	item[3].weight = 4;
	item[3].benefit = 300;
	
	item[4].weight = 5;
	item[4].benefit = 40;
	
	item[5].weight = 6;
	item[5].benefit = 60;
	
	item[6].weight = 7;
	item[6].benefit = 70;
	
	item[7].weight = 8;
	item[7].benefit = 80;
	
	item[8].weight = 9;
	item[8].benefit = 90;
	
	item[9].weight = 8;
	item[9].benefit = 150;
	
	item[10].weight = 20;
	item[10].benefit = 30;

	item[11].weight = 30;
	item[11].benefit = 50;
	
	item[12].weight = 19;
	item[12].benefit = 30;
	
	item[13].weight = 60;
	item[13].benefit = 100;
	
	item[14].weight = 7;
	item[14].benefit = 250;
	
	item[15].weight = 45;
	item[15].benefit = 150;
	
	item[16].weight = 32;
	item[16].benefit = 70;
	
	item[17].weight = 8;
	item[17].benefit = 90;
	
	item[18].weight = 12;
	item[18].benefit = 10;
	
	item[19].weight = 19;
	item[19].benefit = 60;
}

void Init_Population(Population *population, Item *item, Knapsack knapsack){
	population->size = POPULATION_SIZE;
	population->individual = (Individual *) malloc(sizeof(Individual) * population->size);

	int gene_size = knapsack.n;
	int i, j;

	for(i = 0 ; i < population->size ; i++){
		population->individual[i].gene_size = gene_size;//get gene size
		population->individual[i].gene = (short *) malloc(sizeof(short) * gene_size);//initialize gene
		population->individual[i].weight = 0;//initialize weight

		for(j = 0 ; j < gene_size ; j++)
		population->individual[i].gene[j] = Random_Number(0,1);
			if(population->individual[i].gene[j]  == 1)
				population->individual[i].weight += item[j].weight;
		population->individual[i].fitness = Fitness(population->individual[i], item, knapsack);
	}	

	Assign_Mating_Probability(population);
}

//Problem Solving Functions -----------------
int Random_Number(int start, int end){
    return start + (rand() % (end - start + 1));
}

//generate random mutate prob which is smaller than the mutation prob
bool mutateProbability(){
	float random_number = Random_Number(0, 100);

	random_number /= 100;

	if(random_number <= MUTATION_PROB)
		return true;

	return false;
}

//calculate the total weight of the individual
float totalWeight(Individual individual, Item *item){
	float weight = 0;
	int i;

	for(i = 0 ; i < individual.gene_size ; i++)
		if(individual.gene[i] == 1)
			weight += item[i].weight;

	return weight;
}

//calculate fitness score (in knapsack problem, it can be considered as the benefit of the item)
float Fitness(Individual individual, Item *item, Knapsack knapsack){
	int i;
	float weight = 0;
	float fitness = 0;

	for(i = 0 ; i < individual.gene_size ; i++)
		if(individual.gene[i] == 1){
			weight += item[i].weight;
			fitness += item[i].benefit;
		}

	if(weight > knapsack.capacity)
		return 1;
	return fitness;
}

//calculate mating prob and assign to individuals Use Roulette-wheel selection
void Assign_Mating_Probability(Population *population){
	float fsum = 0;

	for(int i = 0 ; i < population->size ; i++)
		fsum += population->individual[i].fitness;

	for(int i = 0 ; i < population->size ; i++)
		population->individual[i].mating_probability = population->individual[i].fitness / fsum;
}

Individual Random_Selection(Population population){
	float random_number = Random_Number(0, 100);
	float aux = 0;
	int i;

	random_number /= 100;

	for(i = 0 ; i < population.size ; i++){
		aux += population.individual[i].mating_probability;
		if(random_number <= aux)
			return population.individual[i];
	}

	return population.individual[i - 1];
}

// check whether all gene are equal
bool Individuals_Are_Equal(Individual x, Individual y){
	int i;
	for(i = 0 ; i < x.gene_size ; i++)
		if(x.gene[i] != y.gene[i])
			return false;
	return true;
}

Individual crossOver(Individual x, Individual y){
	Individual child;
	child.gene_size = x.gene_size;
	child.gene = (short *) malloc(sizeof(short) * child.gene_size);
	child.weight = 0;

	int gene_size = x.gene_size;
	int select = Random_Number(0,gene_size - 2);
	int i;
	//like biology, child has 50% prob to get gene from mom or dad
	for(i = 0; i < select; i++){
		child.gene[i] = x.gene[i];	
	}
	for(i = select+1; i < gene_size; i++){
		child.gene[i] = y.gene[i];	
	}
	return child;
}

void Mutate(Individual *child){
	int c = Random_Number(0, child->gene_size - 1);

	if(child->gene[c] == 0) child->gene[c] = 1;

	else child->gene[c] = 0;

}

void Clear_Population(Population *population){
	int i, j;
	int gene_size = population->individual[0].gene_size;

	for(i = 0 ; i < population->size ; i++){
		population->individual[i].weight = 0;
		population->individual[i].fitness = 0;
		population->individual[i].mating_probability = 0;
	}
}
//int z=0;
bool test(Population *population){ 
	int i;
	float rate = 0.0;
	for(i = 0; i< population->size; i++){
	
		//printf("%f\n", population->individual[i].fitness);
		//printf("%d\n",j+=1);
		/* if the current fitness score of current individual is similar to another one who next him, raise the rate of success.
		if 90% of individuals has same fitness value: stop the while loop in genetic driver function. In addtion, if both are equal to 0, we still not raise the rate.   http://www.sc.ehu.es/ccwbayes/docencia/kzmm/files/AG-knapsack.pdf
		*/
		if(population->individual[i].fitness == population->individual[i+1].fitness && population->individual[i].fitness!=0)
			rate += 1/(float)population->size;
			
		}
	//printf("%f\n", rate);
	if(rate > 0.9)
		return true;
	return false;

}
//driver
Individual Genetic_Algorithm(Population population, Item *item, Knapsack knapsack){
	Population new_population;
	new_population.individual = (Individual *) malloc(sizeof(Individual) * population.size);
	new_population.size = population.size;

	int generations = 1;
	int i, j;
	bool found = false;

	Individual x, y;
	Individual child;
	Individual best_individual = population.individual[0];

	while(!found && generations <= 1000){
		//printf("%d\n",z+=1);
		Clear_Population(&new_population);

		for(i = 0 ; i < population.size ; i++){
			x = Random_Selection(population);
			y = Random_Selection(population);
			j = 1;
			while(Individuals_Are_Equal(x, y) && j <= 100){
				y = Random_Selection(population);
				j++;
			}//when we select two parents have same genes, we randomly choose another pair of parent

			child = crossOver(x, y);
			if(mutateProbability()) // if it hits the mutation prob(0.1), we mutate the genes
				Mutate(&child);
			child.weight = totalWeight(child, item);
			child.fitness = Fitness(child, item, knapsack);

			if(child.fitness > best_individual.fitness){
				best_individual = child;
			}

			new_population.individual[i] = child;
		}

		Assign_Mating_Probability(&new_population);
		population = new_population;
		if(test(&new_population))
		found = true;

		generations++;
	}

	free(new_population.individual);

	return best_individual;
}

//Menu Functions ----------------------------


//Printing Function ------------------------
void Print_Individual(Individual individual){
	int i;
	printf("Best Individual: ");
	for(i = 0 ; i < individual.gene_size ; i++)
		printf("%hi", individual.gene[i]);
	printf("\n");

}


//Control Functions -------------------------
void Control(Knapsack *knapsack, Item **item){
	system("clear || cls");
	double time_spent = 0.0;
	clock_t begin = clock();
	Init_Default_Knapsack(knapsack);

	*item = (Item *) malloc(sizeof(Item) * knapsack->n);
	Init_Default_Items(*item, *knapsack);

	Population population;
	Init_Population(&population, *item, *knapsack);

	Individual best_individual = Genetic_Algorithm(population, *item, *knapsack);
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	Print_Individual(best_individual);
	//printf("Time: %f\n", time_spent);
}

//-------------------------------------------

//Test --------------------------------------
int main(int argc, char *argv[]){
	srand(time(NULL));

	Knapsack knapsack;
	Item *item;

	Control(&knapsack, &item);

	return 0;
}

//-------------------------------------------
