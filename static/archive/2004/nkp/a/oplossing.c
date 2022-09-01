#include <stdio.h>
#include <stdlib.h>

#define maxN 100
#define maxB 100
#define maxT 100
#define maxA 100

const int starttijd = 9*60;
const int infty = 999999999;

int run,nruns;

int n;
int nbussen[maxN+10];
int reisduur[maxN+10];
int bustijd[maxN+10][maxB+10][2]; /* (vroegste, laatste) */
int tijd[maxN+10][2]; /* (vroegste, laatste) tijd bij bushalte n */

int min(int a, int b) { return a<b ? a : b; }
int max(int a, int b) { return a>b ? a : b; }

void read()
{
  int i,j,h,m,a;
  
  scanf("%d\n",&n);
  if ( n<1 || n>maxN ) {
    printf("testcase %d: n fout!\n",run+1);
    exit(1);
  }

  for(i=0; i<n; i++) {
    scanf("%d %d\n",&nbussen[i],&reisduur[i]);
    if ( nbussen[i]<1  || nbussen[i]>maxB ||
	 reisduur[i]<1 || reisduur[i]>maxT ) {
      printf("testcase %d: buslijn %d fout!\n",run+1,i+1);
      exit(1);
    }
    for(j=0; j<nbussen[i]; j++) {
      scanf("%d:%d (%d)\n",&h,&m,&a);
      if ( h<1 || h>23 || m<0 || m>59 || a<0 || a>maxA ) {
	printf("testcase %d: buslijn %d, bus %d fout!\n",run+1,i+1,j+1);
	exit(1);
      }
      bustijd[i][j][0] = h*60+m-a;
      bustijd[i][j][1] = h*60+m+a;
    }
  }
}

void write()
{
  printf("%02d:%02d %02d:%02d\n",
	 tijd[n][0]/60,tijd[n][0]%60,
	 tijd[n][1]/60,tijd[n][1]%60);
}

void solve()
{
  int i,j;

  for(i=1; i<=n; i++) tijd[i][0] = tijd[i][1] = infty;
  tijd[0][0] = tijd[0][1] = starttijd;
  
  for(i=0; i<n; i++) {
    for(j=0; j<nbussen[i]; j++) {
      if ( bustijd[i][j][1]<tijd[i][0] ) continue;
      tijd[i+1][0] = min(reisduur[i]+max(tijd[i][0],bustijd[i][j][0]),
			 tijd[i+1][0]);
      if ( bustijd[i][j][0]<tijd[i][1] ) continue;
      tijd[i+1][1] = min(tijd[i+1][1],reisduur[i]+bustijd[i][j][1]);
    }
  }
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
