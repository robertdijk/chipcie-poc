#include <stdio.h>
#include <stdlib.h>

#define maxN 100
#define maxM 1000
#define maxL 24

const int empty = 999;

int run,nruns;

int nsteden,nvluchten;
char naam[maxN+10][maxL+10];
int pos[maxN+10][2]; /* lengte, breedte */
int lengte[maxN+10];
int conn[maxN+10][maxN+10];
int sol;

int inrange(int l, int b)
{
  return -180<l && l<=180 && -90<b && b<90;
}

void read()
{
  int i, fr, to, len, br;
  char frstr[maxL+10], tostr[maxL+10];
  
  scanf("%d\n",&nsteden);
  if ( nsteden<1 || nsteden>maxN ) {
    printf("testcase %d: nsteden fout!\n",run+1);
    exit(1);
  }

  for(i=0; i<nsteden; i++) {
    scanf("%s %d %d\n",frstr,&br,&len);
    if ( strlen(frstr)>maxL || !inrange(len,br) ) {
      printf("testcase %d: stad %d fout!\n",run+1,i+1);
      exit(1);
    }
    strcpy(naam[i],frstr);
    pos[i][0] = len;
    pos[i][1] = br;
  }

  scanf("%d\n",&nvluchten);
  if ( nvluchten<1 || nvluchten>maxM ) {
    printf("testcase %d: nvluchten fout!\n",run+1);
    exit(1);
  }

  for(fr=0; fr<nsteden; fr++)
    for(to=0; to<nsteden; to++)
      conn[fr][to] = 0;
  
  for(i=0; i<nvluchten; i++) {
    scanf("%s %s\n",frstr,tostr);
    for(fr=0; fr<nsteden && strcmp(frstr,naam[fr])!=0; fr++);
    for(to=0; to<nsteden && strcmp(tostr,naam[to])!=0; to++);
    if ( fr>=nsteden || to>=nsteden ) {
      printf("testcase %d: route %d fout!\n",run+1,i+1);
	  printf("%s %s\n",frstr,tostr);
      exit(1);
    }
    conn[fr][to] = conn[to][fr] = 1;
    if ( abs(pos[fr][0]-pos[to][0])==180 ) {
      printf("testcase %d: route %d fout!\n",run+1,i+1);
      exit(1);
    }
  }
  
}

void write()
{
  if ( sol )
    printf("ja\n");
  else
    printf("nee\n");
}

void dfs(int i,int len)
{
  int j,dlen;
  
  if ( lengte[i]==len ) return;
  
  if ( lengte[i]!=empty ) {
    sol = 1;
    return;
  }

  lengte[i] = len;
  for(j=0; j<nsteden; j++)
    if ( conn[i][j] ) {
      dlen = pos[j][0]-pos[i][0];
      if ( dlen>180  ) dlen -= 360;
	  if ( dlen<-180 ) dlen += 360;
      dfs(j,len+dlen);
    }
  
}

void solve()
{
  int i;

  for(i=0; i<nsteden; i++) lengte[i] = empty;
  
  sol = 0;
  dfs(0,pos[0][0]);
}

int main()
{
  scanf("%d\n",&nruns);

  for(run=0; run<nruns; run++) {
    read();
    solve();
    write();
  }

  return 0;
}
