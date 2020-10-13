#include <stdio.h>
#include "stdlib.h"
#include "type.h"

int roulette(IPTR pop, double sumFitness, int popsize);
void crossover(POPULATION *p, IPTR p1, IPTR p2, IPTR c1, IPTR c2);
double eval(POPULATION *p, IPTR pj);
int cmp(const void *a, const void *b);

struct str
{
    float value;
    int index;
};

int generation(POPULATION *p, int t)
{
//chc
  double sort_me[p->popSize];
  int i, p1, p2, c;
  IPTR pi, piPlus1, om1, om2;

  for(i = 0; i < p->popSize; i ++)
  {
    sort_me[i] = p->op[i].fitness ;
    printf("%f ",sort_me[i]);
  }

//  printf ("begin gen: ");

  struct str objects[p->popSize];
  for (int i = 0; i < 3; i++)
  {
    objects[i].value = sort_me[i];
    objects[i].index = i;
  }
  //sort objects array according to value maybe using qsort
  qsort(objects, p->popSize, sizeof(objects[0]), cmp);

  for(i = 0; i < p->popSize/2; i =+ 2){
      p1 = objects[i].index;
      p2 = objects[i+1].index;
// p1 and p2 are pop members
//    p1 = roulette(p->op, p->sumFitness, p->popSize);
//    p2 = roulette(p->op, p->sumFitness, p->popSize);

    pi = &(p->np[i]);
    piPlus1 = &(p->np[i+1]);
    om1 = &(p->op[p1]);
    om2 = &(p->op[p2]);
//    printf("----");
    crossover(p, om1, om2, pi, piPlus1);

    pi->fitness = eval(p, pi); 
    pi->parent1 = p1;
    pi->parent2 = p2;

    
    piPlus1->fitness = eval(p, piPlus1);
    piPlus1->parent1 = p2;
    piPlus1->parent2 = p1;

  }

}

int cmp(const void *a, const void *b)
{
    struct str *a1 = (struct str *)a;
    struct str *a2 = (struct str *)b;
    if ((*a1).value > (*a2).value)
        return -1;
    else if ((*a1).value < (*a2).value)
        return 1;
    else
        return 0;
}
