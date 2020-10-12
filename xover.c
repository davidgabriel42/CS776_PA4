#include "type.h"
#include "stdio.h"

int rnd(int low, int high);
int flip(double);
//int muteX(POPULATION *p, int pa, int pb);

void crossover(POPULATION *p, IPTR p1, IPTR p2, IPTR c1, IPTR c2)
{
//pmx
/* p1,p2,c1,c2,m1,m2,mc1,mc2 */
  int *pi1,*pi2,*ci1,*ci2;
  int xp1, xp2, i, swp, addr;
  int pmx1[p->lchrom], pmx2[p->lchrom];
  int match;

  pi1 = p1->chrom;
  pi2 = p2->chrom;
  ci1 = c1->chrom;
  ci2 = c2->chrom;

  if(flip(p->pCross))
  {

    xp1 = rnd(0, p->lchrom - 1);
    xp2 = rnd(0, p->lchrom - 1);
    if(xp1 > xp2)
    {
      swp = xp1;
      xp1 = xp2;
      xp2 = swp;

    }
/*
    printf("xover: %d \t %d \t xp\n", xp1,xp2);
    printf("xover: p1 \t p2 \t \n");
    for(i = 0; i < p->lchrom;i++)
    {
      printf("xover:%d:: %d\t%d\t\n", i, pi1[i],pi2[i]);
    }
*/
//1
    for(i = xp1; i < xp2; i++)
    {
      ci1[i] = pi2[i];
      ci2[i] = pi1[i];

    }
//2&3
//7FFFFFFF is null
    for(i = 0; i < p->lchrom; i++)
    {
    for(int j = xp1; j < xp2; j++)
      {
        if( ci1[i]==pi2[j]& i <xp1 & i > xp2){ci1[i] = 0x7FFFFFFF;}
        if( ci2[i]==pi1[j]& i <xp1 & i > xp2){ci2[i] = 0x7FFFFFFF;}
      }
    }
//4
    for(i = 0; i < p->lchrom; i++)
    {
      if(ci1[i] == 0x7FFFFFFF)
      {
       
        for(int j = xp1; j < xp2; j++)
        {
          match = 1;
          for(int k = 0; k < p->lchrom; k++)
          {
            if(ci1[k] == pi2[j]){match = 0;}
          }
        if(match){ci1[i] = pi2[j];}
        }
      }
    }

    for(i = 0; i < p->lchrom; i++)
    {
      if(ci2[i] == 0x7FFFFFFF)
      {
       
        for(int j = xp1; j < xp2; j++)
        {
          match = 1;
          for(int k = 0; k < p->lchrom; k++)
          {
            if(ci2[k] == pi1[j]){match = 0;}
          }
        if(match){ci2[i] = pi1[j];}
        }
      }//endif
    }
/*
    printf("xover: c1 \t c2 \t\n");
    for(i = 0; i < p->lchrom;i++)
    {
      printf("xover:%d:: %d \t %d \t\n", i, ci1[i], ci2[i]);
    }
*/
  }//endif

//mutation, swap cities in path
//0-1-2-3M4-5 -> 0-1-2-4-3-5
//wraps around chrom

  for(i = 0; i < p->ndim; i++)
  {
    if(flip(p->pMut))
    {
      for(int j = 0; j < bits_per_dim; j ++)
      {
        addr = i*bits_per_dim + j;
        swp = ci1[addr];
        ci1[addr] = ci1[(addr+bits_per_dim)%p->lchrom];
        ci1[(addr+bits_per_dim)%p->lchrom] = swp;
      }
    }
    if(flip(p->pMut))
    {
      for(int j = 0; j < bits_per_dim; j ++)
      {
        swp = ci2[i+j];
        ci2[i+j] = ci2[(i+j+bits_per_dim)%p->lchrom];
        ci2[(i+j+bits_per_dim)%p->lchrom] = swp;
      }

    }//endif
  }
}

//not used
int muteX(POPULATION *p, int pa, int pb)
{
  return (flip(p->pMut) ? 1 - pa  : pa);
}


