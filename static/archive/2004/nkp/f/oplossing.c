#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int x, y;
} pos_t;

int nBezems, nPlaatsen;
pos_t Bezems[50], Plaatsen[50];

#define INFTY 2100000000
#define NUM_NODES 500
#define NIL -1

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define ABS(a) (((a) < 0) ? (-(a)) : (a))

int num_edges, num_nodes;
int cap[NUM_NODES][NUM_NODES];
int flow[NUM_NODES];
int prevnode[NUM_NODES];
int visited[NUM_NODES];

int max_flow(int source, int sink) {
  int i, maxloc, maxflow;
  int pathcap, curnode, nextnode;
  int totalflow;

  if(source==sink)
    return INFTY;

  totalflow=0;

  while(1) {
    for(i=0; i<num_nodes; i++) {   // for all nodes
      prevnode[i]=NIL;
      flow[i]=0;
      visited[i]=0;
    }
    flow[source]=INFTY;

    while(1) {
      maxflow=0;
      maxloc=NIL;
      for(i=0; i<num_nodes; i++) {
	if(flow[i]>maxflow && !visited[i]) {
	  maxflow=flow[i];
	  maxloc=i;
	}
      }
      if(maxloc==NIL)
	break;
      if(maxloc==sink)
	break;
      visited[maxloc]=1;
      
      for(i=0; i<num_nodes; i++) {
	if(flow[i] < MIN(maxflow, cap[maxloc][i])) {
	  prevnode[i]=maxloc;
	  flow[i]=MIN(maxflow, cap[maxloc][i]);
	}
      }
    }
    
    if(maxloc==NIL)
      break;

    pathcap=flow[sink];
    totalflow+=pathcap;

    curnode=sink;
    while(curnode != source) {
      nextnode=prevnode[curnode];
      cap[nextnode][curnode]-=pathcap;
      cap[curnode][nextnode]+=pathcap;
      curnode=nextnode;
    }
  }

  return totalflow;
}

int possible(int max_len)
{
	int i, j;
	
	// Bouw een bipartite graaf tussen bezems en plaatsen met alleen edges
	// als de afstand tussen bezem en plaats kleiner gelijk aan max_len is.
	// Gebruik max flow om te bepalen of er match is die alle bezems aan
	// plaatsen matched.
	
	for(i=0; i<NUM_NODES; i++)
		for(j=0; j<NUM_NODES; j++)
			cap[i][j]=0;
			
	for(i=0; i<nBezems; i++)
		for(j=0; j<nPlaatsen; j++)
			if((ABS(Plaatsen[j].x-Bezems[i].x)+ABS(Plaatsen[j].y-Bezems[i].y))
												<=max_len)
				cap[i][nBezems+j]=1;


	for(i=0; i<nBezems; i++)
		cap[nBezems+nPlaatsen][i]=1;
	for(i=0; i<nPlaatsen; i++)
		cap[nBezems+i][nBezems+nPlaatsen+1]=1;
	num_nodes=nBezems+nPlaatsen+2;
	
/*	printf("max_len=%d\n", max_len);
	for(i=0; i<num_nodes; i++)
	{
		for(j=0; j<num_nodes; j++)
			printf("%d ", cap[i][j]);
		printf("\n");
	}*/
	return max_flow(num_nodes-2, num_nodes-1)==nBezems;
}

void do_it()
{
	char line[300];
	int l,b;
	pos_t pos;
	int left, right, mid;
	
	scanf("%d %d",&l, &b);
	if(l<1 || l>250 || b<1 || b>250)
	{
		printf("l, b out of bound\n");
		exit(1);
	}
	
	nBezems=0; nPlaatsen=0;
	for(pos.x=0; pos.x<l; pos.x++)
	{
		scanf("%s", line);
		for(pos.y=0; pos.y<b; pos.y++)
		{
			if(line[pos.y]=='B')
				Bezems[nBezems++]=pos;
			if(line[pos.y]=='P')
				Plaatsen[nPlaatsen++]=pos;
		}
	}
	if(nBezems>nPlaatsen)
	{
		printf("Meer bezems dan plaatsen\n");
		exit(1);
	}
	if(nBezems>50 || nPlaatsen>50)
	{
		printf("Teveel bezems of plaatsen\n");
		exit(1);
	}
	
	left=0; right=l+b-2; // left=lower limit , right =upper limit+1;
	while(left<right)
	{
		mid=(left+right)/2;
		if(possible(mid))
			right=mid;
		else
			left=mid+1;
	}
	
	printf("%d\n", left);
}

int main()
{
	int nruns;
	
	scanf("%d", &nruns);
	while(nruns--)
		do_it();
		
	return 0;
}
