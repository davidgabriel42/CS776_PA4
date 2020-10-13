#include <stdio.h>
#include "stdlib.h"
#include "type.h"

extern double *base_arr;


int roulette(IPTR pop, double sumFitness, int popsize);
void crossover(POPULATION *p, IPTR p1, IPTR p2, IPTR c1, IPTR c2);
double eval(POPULATION *p, IPTR pj);
static int compar (const void *a, const void *b);

static int compar (const void *a, const void *b)
{
  int aa = *((double *) a), bb = *((double *) b);
  if (base_arr[aa] < base_arr[bb])
    return -1;
  if (base_arr[aa] == base_arr[bb])
    return 0;
  if (base_arr[aa] > base_arr[bb])
    return 1;
}

int generation(POPULATION *p, int t)
{
//chc
  double sort_me[p->popSize];
  int i, p1, p2, c;
  int *base_arr;
  int *arr, *idx, n;
 
  printf ("begin gen: ");
//  scanf ("%d", &n);
 
  arr = malloc (sizeof (int) * n);
  idx = malloc (sizeof (int) * n);


  IPTR pi, piPlus1, om1, om2;

  for(i = 0; i < p->popSize; i ++)
  {
    sort_me[i] = p->op[i].fitness ;
    printf("%f ",sort_me[i]);
  }

// source : https://phoxis.org/2012/07/12/get-sorted-index-orderting-of-an-array/
 /* initialize initial index permutation of unmodified `arr'
   */
  for (i = 0; i < n; i++)
    {
      idx[i] = i;
    }
 
  /* Assign the address of out original array to the static global
   * pointer, this will be used by the compare function to index 
   * into the original array using `idx' values
   */

  base_arr = sort_me;
  qsort(sort_me, p->popSize,sizeof(double) , compar);

  for(i = 0; i < p->popSize/2; i =+ 2){
      p1 = idx[i];
      p2 = idx[i+1];
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
    free (arr);
    free (idx);
  }

}
/*
//source:
//https://phoxis.org/2012/07/12/get-sorted-index-orderting-of-an-array/
int *sorted_order (const int *arr, int n)
{
  int *idx, i, j;
 
  idx = malloc (sizeof (int) * n);
 
  for (i=0; i<n; i++)
  {
    idx[i] = i;
  }
 
  for (i=0; i<n; i++)
  {
    for (j=i+1; j<n; j++)
    {
      if (arr[idx[i]] > arr[idx[j]])
      {
        swap (&idx[i], &idx[j]);
      }
    }
  }
 
  return idx;
}
*/
