#include <stdio.h>
#include <stdlib.h>

#include "type.h"


void rawStat();

void report(int gen, POPULATION *p, IPTR  pop)
{ /* report generations stats */
  FILE *fp;
  int err;
  if( (fp = fopen(p->ofile, "a")) == NULL){
    err = printf("error in opening file %s \n", p->ofile);
    exit(1);
  }else{
    rawStat(fp, p, pop);
    fclose(fp);
  }
  rawStat(stdout, p, pop);


}

void rawStat(FILE *fp, POPULATION *p, IPTR pop)
{
  int err;
  err = fprintf(fp,"gen: %3d max: %10.2lf avg: %10.2lf min: %10.2lf ", p->gen, p->max, 
	  p->avg, p->min);
  err = fprintf(fp,"max gen: %3d max indiv: %10.2lf max index: %3d", p->highestEverGen,  p->highestEverFitness, 
	  p->highestEverIndex);
  err = fprintf(fp," %10.2lf\n", pop[p->maxi].fitness);
}

