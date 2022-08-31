/*
 *  NKP 2004: Safari
 *  door Jan Kuipers
 */

using namespace std;

#include <vector>
#include <iostream>
#include <stdio.h>

int N,M,tmin,tmax;
vector<vector<double> > best;
vector<int> fr,to,ti;
vector<double> p;

void read () {

  cin >> tmin >> tmax;
  cin >> N >> M;

  fr=to=ti=vector<int>(M);
  p=vector<double>(M);

  for(int m=0; m<M; m++) {
    cin >> fr[m] >> to[m] >> ti[m] >> p[m];
    fr[m]--;
    to[m]--;
    p[m]/=100.0;
  }
}

void solve () {

  best=vector<vector<double> >(tmax+1, vector<double>(N, -1.0));
  best[0][0]=0.0;
  double sol=-1.0;

  for (int t=0; t<=tmax; t++) { 
    if (t>=tmin) sol>?= best[t][0];

    for (int m=0; m<M; m++)
      if (t+ti[m]<=tmax && best[t][fr[m]]>=0.0) 
        best[t+ti[m]][to[m]] >?= 1.0 - (1.0-best[t][fr[m]])*(1.0-p[m]);
  }

  if (sol>=0.0)
    printf ("%.2lf\n",100.0*sol); // nog uitzoeken hoe in C++
  else
    cout << "onmogelijk" << endl;
}

int main () {

  int run, runs;
  cin >> runs;

  for (run=0; run<runs; run++) {
    read ();
    solve ();
  }

  return 0;
}
