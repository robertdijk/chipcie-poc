/******************************************************************************
* Sample solution for the Investment problem in NWERC'04
* Author: Andreas Björklund
* Solution: Knapsack
******************************************************************************/
#include <stdio.h>

#define MAXN (11)
#define MAXG (46000)

int r[MAXN],v[MAXN],p[MAXG];

int main(void)
{
  int m,n,y,i,j,t;
  scanf("%d",&t);
  while(t--) 
  {
    scanf("%d %d",&n,&y);
    scanf("%d",&m);
    for (i=0;i<m;i++)
      scanf("%d %d",&v[i],&r[i]);
    for (i=0;i<MAXG;i++)
    {
      p[i]=0;
      for (j=0;j<m;j++)
        if (i-(v[j]/1000)>=0 && r[j]+p[i-(v[j]/1000)]>p[i]) p[i]=r[j]+p[i-(v[j]/1000)];
    }
    for (i=0;i<y;i++)
      n+=p[n/1000];
    printf("%d\n",n);
  }
  return 0;
}
