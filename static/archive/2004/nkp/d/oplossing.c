#include <stdio.h>
#include <stdlib.h>

#define maxN 105000
#define maxP 2000000000

int N,K;
int pos[maxN];
int bestdist = -1;

int comp_int(const void *a1, const void *b1)
{
  int a = *(int *)a1;
  int b = *(int *)b1;
  if ( a<b ) return -1;
  if ( a>b ) return  1;
  return 0;
}

void read()
{
  int i;

  scanf("%d %d\n",&N,&K);
  for(i=0; i<N; i++) scanf("%d",&pos[i]);
}

void write()
{
  printf("%d\n",bestdist);
}

void solve()
{
  int mindist, maxdist, dist;
  int i,nplaced,lastplaced;

  /* Voor de zekerheid, invoer zou gesorteerd moeten zijn: */
  qsort(pos,N,sizeof(int),&comp_int);
  
  mindist = 0;
  maxdist = maxP;

  /* Binary search over de minimale afstand: */
  while ( mindist<maxdist ) {
    dist = (mindist+maxdist+1)/2;
    /* En kijken hoeveel we voor afstand 'dist' kwijt kunnen: */
    nplaced = 1;
    lastplaced = 0;
    for(i=1; i<N; i++)
      if ( pos[i]-pos[lastplaced]>=dist ) {
	nplaced++;
	lastplaced = i;
      }
    if ( nplaced<K )
      maxdist = dist-1;
    else
      mindist = dist;
  }
  bestdist = mindist;
}

int main()
{
  int run,nruns;

  scanf("%d\n",&nruns);

  for(run=0; run<nruns; run++) {
    read();
    solve();
    write();
  }
  
  return 0;
}
