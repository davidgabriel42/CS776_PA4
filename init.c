#include <stdio.h>
#include <stdlib.h>  /* for calloc */
#include <string.h>
#define INFILE  "infile"
#include "type.h"
#include "math.h"
#define bits_per_dimension 32

int flip(double p);
void randomize(POPULATION *p);
void statistics(POPULATION *p, IPTR pop);
void rawStat(FILE *fp, POPULATION *p, IPTR pop);
double eval(POPULATION *p, IPTR pi);
void shuffle(int *array, size_t n);
void initGa(char *inputFile, POPULATION *p);
void initData(char *inputFile, POPULATION *p);
void initPop(POPULATION *p);
void initReport(POPULATION *p);
void initialize(char *argv[], POPULATION *p)
{ /* initialize everything */

  //used to define const int conversion
  //printf("The size of integer is %lu\n", (unsigned long)sizeof(foo));
  
  char *Ifile;
  int  nameLength = (int) strlen(argv[1]);
  Ifile = (char *) calloc(nameLength + 1, sizeof(char));
  strcpy(Ifile, argv[1]);

  initGa(Ifile, p);
//  printf("after initGa \n");

  initData(Ifile, p);
//  printf("after initData \n");
//  printf("0");
  initPop(p);
//  printf("after initPOP \n");

  statistics(p, p->op);
//  printf("after STATS \n");

  initReport(p);
  printf("init complete\n");
}

void initData(char *Ifile, POPULATION *p)
 { /* inittialize global params,
     popsize:   population size
     lchrom :   chromosome lenght
     maxgen :   maximum no. of generations.
     pcross :   crossover probability
     pmut   :   mutation probability           */

  int i;
  FILE *inpfl;
  char tmp[1024];
  int err;
  char buffer[100];
  char buffer1[100];
  int city;
  int x;
  int y;
  if( (inpfl = fopen(Ifile,"r")) == NULL){
    printf("error in opening file %s \n", Ifile);
    exit(1);
  }

  for (i = 0 ; i < 3; i++)
  {
   fgets(buffer, 100, inpfl);
  }
  err = fscanf(inpfl,"%s %s %d",buffer, buffer1, &p->ndim);
//  printf(" Enter name - name-> ");
//  err = fscanf(inpfl,"%s %s %s",&buffer1[0],&buffer1[0],&buffer[0]);
  printf("Number of cities: %i\n",p->ndim);
  for (i = 0 ; i < 3; i++)
  {
   fgets(buffer, 100, inpfl);
  }
  for ( i = 0 ; i < p->ndim; i++)
  {
    err = fscanf(inpfl,"%d %d %d", &city, &x, &y );
    p->x[i] = x;
    p->y[i] = y;
//    printf("City %d %d %d \n", i, x, y);
  }

  fclose(inpfl);
  printf("\n");

}
void initGa(char *Ifile, POPULATION *p)
{ /* inittialize global params,
     popsize:   population size
     lchrom :   chromosome lenght
     maxgen :   maximum no. of generations.
     pcross :   crossover probability
     pmut   :   mutation probability           */
  int i;
  FILE *inpfl;
  char tmp[1024];
  int err;

  if( (inpfl = fopen(INFILE,"r")) == NULL){
    printf("error in opening file %s \n", INFILE);
    exit(1);
  }

//  printf(" Enter population size - popSize-> "); 
  err = fscanf(inpfl,"%d",&p->popSize);
  if(p->popSize % 2 != 0) {
    p->popSize++;
  }
//  printf("\nNote population size must be even: %i", p->popSize);

//  printf(" Enter chromosome length - lChrom-> "); 
  err = fscanf(inpfl,"%d",&p->lchrom);
//  printf("\n");

//  printf(" Enter max. generations - maxGen-> "); 
  err = fscanf(inpfl,"%d",&p->maxGen);
//  printf("\n");

//  printf(" Enter crossover prob - pCross-> "); 
  err = fscanf(inpfl,"%lf",&p->pCross);
//  printf("\n");

//  printf(" Enter mutation prob - pMut-> "); 
  err = fscanf(inpfl,"%lf",&p->pMut);
//  printf("\n");

//  printf(" Enter file name for graph output -fname-> ");

  err = fscanf(inpfl,"%s", tmp);
  p->ofile = (char *) calloc ((int) strlen(tmp)+1, sizeof(char));
  strcpy(p->ofile, tmp);
  printf("Save file is %s\n", p->ofile);
  

  fclose(inpfl);
  printf("\n");

  randomize(p); /* initialize random number generator */

  /* set progress indicators to zero */
  p->highestEverFitness = 0.0;
  p->highestEverGen = 0;
  p->highestEverIndex = 0;
}

void initPop(POPULATION *p)
{ /* initialize a random population */
  IPTR pi, pj;
  int i, j, k, l, kprev;
  FILE *fp;
  double f1;
  int cities[1000];
//  printf("-1-");


  for (i = 0; i < p->ndim; i++)
  {
    cities[i] = i;
    //printf("cities %d \n", cities[i]);
  } 
  
//  printf("-2-");
  for (i = 0; i < p->ndim; i++)
  {
    j = 0;
//    printf("%d:%d,",i, cities[i]);
  }
//  printf("-3-");
  p->op = (IPTR) calloc (p->popSize, sizeof(INDIVIDUAL));
  p->np = (IPTR) calloc (p->popSize, sizeof(INDIVIDUAL));
//  printf("-4-");
  for (i = 0; i < p->popSize; i++)
  {
    pi = &(p->op[i]);
    pi->chrom = (int *) calloc (p->lchrom, sizeof(int));

    pj = &(p->np[i]);
    pj->chrom = (int *) calloc (p->lchrom, sizeof(int));

    shuffle(cities, p->ndim);
    for (j = 0; j < p->lchrom; j++)
    {
      l = j % bits_per_dimension;
      k = floor(j/bits_per_dimension);
//      if (k != kprev){printf(" \n %d \n", cities[k]); }
//      kprev = k;
      pi->chrom[j] = (cities[k] &  1<<l ) >>l ;
//      printf(" %d ", pi->chrom[j]);
    }
    shuffle(cities, p->ndim);
    for (j = 0; j < p->lchrom; j++)
    {
      l = j % bits_per_dimension;
      k = floor(j/bits_per_dimension);
//      if (k != kprev){printf(" \n %d \n", cities[k]); }
//      kprev = k;
      pj->chrom[j] = (cities[k] &  1<<l ) >>l ;
//      printf(" %d ", pi->chrom[j]);
    }
  }

  pi->fitness  = eval(p, pi);
  pi->parent1 = pi->parent2 = -1;
}


void initReport(POPULATION *p)
{
  FILE *fp;
  int i, k;

  printf("\n\nPopulation Size(popsize)  %d\n", p->popSize);
  printf("Chromosome length (lchrom)  %d\n", p->lchrom);
  printf("Maximum num of generations(maxgen)  %d\n", p->maxGen);
  printf("Crossover Probability (pcross)  %lf\n", p->pCross);
  printf("Mutation Probability (pmut)  %lf\n", p->pMut);
  printf("\n\t\tFirst Generation Stats  \n\n");
  printf("Maximum Fitness  %lf\n", p->max);
  printf("Average Fitness  %lf\n", p->avg);
  printf("Minimum Fitness  %lf\n", p->min);

  if( (fp = fopen(p->ofile, "a")) == NULL){
    printf("error in opening file %s \n", p->ofile);
    exit(1);
  }else{
    rawStat(fp, p,  p->op);
    fclose(fp);
  }
  rawStat(stdout, p, p->op);
}

void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

