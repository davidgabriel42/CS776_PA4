#define bits_per_dim 32


typedef struct {
  int *chrom;   /* the chromosome */

  double x;     /* Placeholder for a decoded chromosome value */

  double fitness;   

  int parent1;
  int parent2;

} INDIVIDUAL;

typedef INDIVIDUAL *IPTR;

typedef struct {

  IPTR op;       /* arrays of individuals form an evolving population*/
  IPTR np;
  
  int    lchrom;  /* chromosome length */
  int    gen;     /* current generation */

  double sumFitness; /* statistics parameters for selection and tracking*/
  double max;        /* progress */
  double avg;
  double min;

  double pCross;        /* probability of Xover */
  double pMut;          /* probability of Mutation */
  double randomseed;  

  int    ndim;
  double highestEverFitness;
  int    highestEverGen;
  int    highestEverIndex;

  int    maxi; /* index of best individual in current population*/
  int    mini; /* index of worst individual in current population*/

  int    maxGen; /* when to stop */
  int    popSize;/* population size */

  char  *ofile;  /* output File name */
  int   x[1000];
  int   y[1000];
} POPULATION;
