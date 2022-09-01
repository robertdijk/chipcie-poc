/******************************************************************************
* Sample solution for the Card Game Cheater problem in NWERC'04
* Author: Andreas Björklund
* Solution: Greedy matching.
******************************************************************************/
#include <stdio.h>

#define MAXN (26)

int adam[MAXN],eve[MAXN];

const char rank[13]={"23456789TJQKA"};
const char suite[4]={"CDSH"};

int cardid(char *str)
{
  int i=0,j=0;
  while (i<13 && rank[i]!=str[0]) i++;
  while (j<4 && suite[j]!=str[1]) j++;
  return i*4+j;  
}

int cmp(void *a,void *b)
{
  return (*(int*)a>*(int*)b)-(*(int*)a<*(int*)b);
}

int main(void)
{
  int n,m,i,j,pts;
  char tmp[3];
  scanf("%d",&n);
  while (n--)
  {
    scanf("%d",&m);
    for (i=0;i<m;i++)
    {
      scanf("%s",tmp);
      adam[i]=cardid(tmp);
    }
    for (i=0;i<m;i++)
    {
      scanf("%s",tmp);
      eve[i]=cardid(tmp);
    }
    qsort(adam,m,sizeof(int),cmp);
    qsort(eve,m,sizeof(int),cmp);
    pts=0;
    for (i=0;i<m;i++)
    {
      for (j=0;j<m && adam[m-j-1]>eve[i];j++);
      if (j<m) 
      {
        adam[m-j-1]=52;
        pts++;
      }
    }
    printf("%d\n",pts);
  }
  return 0;
}
