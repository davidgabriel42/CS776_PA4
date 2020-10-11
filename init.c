#include <stdio.h>
#include <stdlib.h>  /* for calloc */
#include <string.h>
#define INFILE  "infile"
#include "type.h"



int flip(double p);
void randomize(POPULATION *p);

void statistics(POPULATION *p, IPTR pop);

void rawStat(FILE *fp, POPULATION *p, IPTR pop);

double eval(POPULATION *p, IPTR pi);

int foo;

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
  printf("after initData\n");

  initPop(p);
  printf("after initPOP\n");

  statistics(p, p->op);
  printf("after STATS\n");

  initReport(p);

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

  if( (inpfl = fopen(Ifile,"r")) == NULL){
    printf("error in opening file %s \n", Ifile);
    exit(1);
  }

  for (i = 0 ; i < 3; i++)
  {
   fgets(buffer, 100, inpfl); 
  }
//  printf(" Enter name - name-> ");
//  err = fscanf(inpfl,"%s %s %s",&buffer1[0],&buffer1[0],&buffer[0]);
//  printf("%s\n",buffer	);


  
  printf(" Enter chromosome length - lChrom-> "); 
  err = fscanf(inpfl,"%d",&p->lchrom);
  printf("\n");

  printf(" Enter max. generations - maxGen-> "); 
  err = fscanf(inpfl,"%d",&p->maxGen);
  printf("\n");

  printf(" Enter crossover prob - pCross-> "); 
  err = fscanf(inpfl,"%lf",&p->pCross);
  printf("\n");

  printf(" Enter mutation prob - pMut-> "); 
  err = fscanf(inpfl,"%lf",&p->pMut);
  printf("\n");

  printf(" Enter file name for graph output -fname-> ");

  err = fscanf(inpfl,"%s", tmp);
  p->ofile = (char *) calloc ((int) strlen(tmp)+1, sizeof(char));
  strcpy(p->ofile, tmp);
  printf("Save file is %s\n", p->ofile);
  

  fclose(inpfl);
  printf("\n");

  randomize(p); 


// initialize random number generator 


// set progress indicators to zero 
  p->highestEverFitness = 0.0;
  p->highestEverGen = 0;
  p->highestEverIndex = 0;

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

  printf(" Enter population size - popSize-> "); 
  err = fscanf(inpfl,"%d",&p->popSize);
  if(p->popSize % 2 != 0) {
    p->popSize++;
  }
  printf("\nNote population size must be even: %i", p->popSize);

  printf(" Enter chromosome length - lChrom-> "); 
  err = fscanf(inpfl,"%d",&p->lchrom);
  printf("\n");

  printf(" Enter max. generations - maxGen-> "); 
  err = fscanf(inpfl,"%d",&p->maxGen);
  printf("\n");

  printf(" Enter crossover prob - pCross-> "); 
  err = fscanf(inpfl,"%lf",&p->pCross);
  printf("\n");

  printf(" Enter mutation prob - pMut-> "); 
  err = fscanf(inpfl,"%lf",&p->pMut);
  printf("\n");

  printf(" Enter file name for graph output -fname-> ");

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
  int i, j;
  FILE *fp;
  double f1;
  
  p->op = (IPTR) calloc (p->popSize, sizeof(INDIVIDUAL));
  p->np = (IPTR) calloc (p->popSize, sizeof(INDIVIDUAL));

  
  for (i = 0; i < p->popSize; i++){
    pi = &(p->op[i]);
    pi->chrom = (int *) calloc (p->lchrom, sizeof(int));

    pj = &(p->np[i]);
    pj->chrom = (int *) calloc (p->lchrom, sizeof(int));

    for (j = 0; j < p->lchrom; j++){
      pi->chrom[j] = flip(0.5); 
      /*      fprintf(stdout, "%1i", pi->chrom[j]); */
    }
    
    pi->fitness  = eval(p, pi);


    /*    fprintf(stdout, " : fitness of %i = %lf\n", i, pi->fitness); */
    
    pi->parent1 = pi->parent2 = -1;
  }
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

