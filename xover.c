#include "type.h"
#include "stdio.h"

int rnd(int low, int high);
int flip(double);
int muteX(POPULATION *p, int pa, int pb);

void crossover(POPULATION *p, IPTR p1, IPTR p2, IPTR c1, IPTR c2)
{
//pmx
/* p1,p2,c1,c2,m1,m2,mc1,mc2 */
  int *pi1,*pi2,*ci1,*ci2;
  int xp1, xp2, i, swp;
  int pmx1[p->lchrom], pmx2[p->lchrom];
  int match;

  pi1 = p1->chrom;
  pi2 = p2->chrom;
  ci1 = c1->chrom;
  ci2 = c2->chrom;

  if(flip(p->pCross)){

    xp1 = rnd(0, p->lchrom - 1);
    xp2 = rnd(0, p->lchrom - 1);
    if(xp1 > xp2)
    {
      swp = xp1;
      xp1 = xp2;
      xp2 = swp;

    }
    printf("%d \t %d \t ", xp1,xp2);
    printf("p1 \t p2 \t");
    for(i = 0; i < p->lchrom;i++)
    {
      printf("%d\t%d\t", pi1[i],pi2[i]);
    }
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
      }
    }
        printf("c1 \t c2 \t");
    for(i = 0; i < p->lchrom;i++)
    {
      printf("%d \t %d \t", ci1[i],ci2[i]);
    }
  }
}

int muteX(POPULATION *p, int pa, int pb)
{
  return (flip(p->pMut) ? 1 - pa  : pa);
}


