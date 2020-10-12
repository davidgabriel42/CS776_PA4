#include <stdio.h>
#include <math.h>
#include "type.h"
#define bits_per_dim 32

double decode(IPTR pj, int index, int size,POPULATION *p);
double binToDec(int *chrom, int l,POPULATION *p);

double eval(POPULATION *p, IPTR pj) 
     /* Called from gen.c and init.c */
{

  double val;
  //double square = 0.0;

  val = decode(pj, 0, p->lchrom, p); 
  //square = val * val;

  return val;
}

double decode(IPTR pj, int index, int size,POPULATION *p)
{

  return ((double) binToDec(&(pj->chrom[0]), size,p));
}

double binToDec(int *chrom, int l,POPULATION *p)
{
  double x[1000];
  int i;
  int j = 0;
  int k = 0;
  double prod;
  double sum = 0;
  int city;
  double xd, yd, x1, x2, y1, y2;
  double dij;
  int skip = 0;

  prod = 0.0;

  for(i = 0; i < l; i++)
  {
    j = i % bits_per_dim;
    if (j == 0)
    {

      city = (int)prod;
      printf("City: %d \n", city);
      x1 = x2;
      y1 = y2;
      x2 = p->x[city];
      y2 = p->y[city];
      if(skip)
      {
        xd = x2-x1;
        yd = y2-y1;
        dij =  round( sqrt( xd*xd + yd*yd) );
        printf("dist %2.2f \n" , dij);
      }
      skip = 1;
      sum += dij;
      prod = 0;

    }
    prod += (chrom[i] == 0 ? 0.0 : pow((double)2.0, (double) j));
//    printf("prod: %2.2f", prod);
  }
//  printf("sum-sqs: %2.2f ", sum);
  sum = 1000000 - sum;
  return sum;
}

void decToBin(int ad, int *barray, int size)
{
  int i, t;

  t = ad;
  for(i = 0; i < size; i++){
    barray[i] = t%2;
    t = t/2;

  }
}
