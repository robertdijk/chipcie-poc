#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Hieronder volgt een stuk geometrische code. */

typedef long long coord;

const double eps = 1E-8;

typedef struct {
	coord x, y;
} point;

typedef struct {
	point p1, p2;
} line;

point addp(point a, point b) { a.x += b.x; a.y += b.y; return a; }
point subp(point a, point b) { a.x -= b.x; a.y -= b.y; return a; }

coord dot  (point a, point b) { return a.x*b.x + a.y*b.y; }
coord cross(point a, point b) { return a.x*b.y - a.y*b.x; }

int sign(long long x)
{
	if ( x<0 ) return -1;
	if ( x>0 ) return  1;
	return 0;
}

int intersect(line a, line b)
{
	// directions of lines
	point da = subp(a.p2,a.p1);
	point db = subp(b.p2,b.p1);

	// if lines are parallel:
	if ( cross(da,db)==0 ) {
		if ( cross(da,subp(b.p1,a.p1))!=0 ) return 0;
		if ( dot(subp(b.p1,a.p1),subp(b.p1,a.p2))<=0 ||
			 dot(subp(b.p2,a.p1),subp(b.p2,a.p2))<=0 ||
			 dot(subp(a.p1,b.p1),subp(a.p1,b.p2))<=0 ||
			 dot(subp(a.p2,b.p1),subp(a.p2,b.p2))<=0 ) return 1;
		return 0;
	}
	
	// return false if line segments not really cross
	if ( sign(cross(db,subp(a.p1,b.p1)))*sign(cross(db,subp(a.p2,b.p1)))>0 ) return 0;
	if ( sign(cross(da,subp(b.p1,a.p1)))*sign(cross(da,subp(b.p2,a.p1)))>0 ) return 0;
	
	return 1;
}

/* Einde geometrische code. */

#define maxN 250

const int infty = 999999999;

/* Beperkende voorwaarden van het probleem (om te controleren) */
const int maxcoord = 100;

int run,nruns;

int n,size;
line stok[maxN];
int conn[maxN][maxN];
int visited[maxN];
int nsize[maxN+1];

void error(char *str)
{
	printf("Error in testcase %d: %s!\n",run+1,str);
	exit(1);
}
 
void read()
{
	int i;
	
	scanf("%d\n",&n);
	if ( n<1 || n>maxN ) error("read: invalid n");
	
	for(i=0; i<n; i++) {
		if ( scanf("%lld %lld %lld %lld\n",
				   &stok[i].p1.x,&stok[i].p1.y,
				   &stok[i].p2.x,&stok[i].p2.y)!=4 )
			error("read: not 4 coords");
		if ( abs(stok[i].p1.x)>maxcoord || abs(stok[i].p1.y)>maxcoord ||
			 abs(stok[i].p2.x)>maxcoord || abs(stok[i].p2.y)>maxcoord )
			error("read: coordinaat te groot");
		if ( stok[i].p1.x==stok[i].p2.x &&
			 stok[i].p1.y==stok[i].p2.y )
			error("read: gelijke eindpunten");
	}
}

void write()
{
	int i, first;

	first = 1;
	for(i=n; i>0; i--)
		if ( nsize[i]>0 ) {
			if ( first )
				first = 0;
			else
				printf(" ");
			
			printf("%dx%d",nsize[i],i);
		}
	printf("\n");
}

void floodfill(int i)
{
	int j;
	
	if ( visited[i] ) return;
	
	visited[i] = 1;
	size++;
	for(j=0; j<n; j++) if ( conn[i][j] ) floodfill(j);
}

void solve()
{
	int i,j;
	
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			conn[i][j] = intersect(stok[i],stok[j]);
	
	for(i=0; i<n; i++) visited[i] = 0;

	for(i=1; i<=n; i++) nsize[i] = 0;
	
	for(i=0; i<n; i++) {
		size = 0;
		if ( !visited[i] ) floodfill(i);
		nsize[size]++;
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
