/*
 *  NKP 2004: Parkeren
 *  door Jan Kuipers
 */

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class edge {
public:
  int a,p,d;
  edge (int _a, int _p, int _d) { a=_a; p=_p; d=_d; }
};

bool operator < (edge a, edge b) { return a.d<b.d; }

int X,Y,N,matched;
vector<string> m;
vector<edge> e;
vector<bool> used;
vector<vector<int> > cap;

bool push (int n) {
  if (used[n]) return false;
  used[n]=true;
  
  if (n==1) { matched++; return true; }
  
  for (int i=0; i<N; i++)
    if (cap[n][i]>0 && push(i)) {
      cap[n][i]--; cap[i][n]++;
      return true;
    }   

  return false;
}

int main () {

  int run,runs;
  cin >>runs;

  for (run=0; run<runs; run++) {
    cin >>Y>>X;
    m=vector<string>(Y);
    for (int i=0; i<Y; i++) cin >>m[i];

    e.clear();
    
    int na=0, np=0;
    for (int ay=0; ay<Y; ay++)
      for (int ax=0; ax<X; ax++)
	if (m[ay][ax] == 'B') {
	  np=0;
	  for (int py=0; py<Y; py++)
	    for (int px=0; px<X; px++)
	      if (m[py][px] == 'P') e.push_back(edge(na,np++,abs(ax-px)+abs(ay-py)));
	  na++;
	}

    sort(e.begin(),e.end());

    matched=0; N=na+np+2;
    cap=vector<vector<int> >(N, vector<int>(N,0));
    for (int i=0; i<na; i++) cap[0][2+i]=1;
    for (int i=0; i<np; i++) cap[2+na+i][1]=1;
    
    for (int i=0; i<e.size(); i++) {
      cap[2+e[i].a][2+na+e[i].p]++;
      used=vector<bool>(N,false);
      push(0);

      if (matched == na) { cout << e[i].d << endl; break; }
    }

    if (matched < na) cout << "onmogelijk!\n";
  }

  return 0;
}
