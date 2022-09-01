/*
 *  NKP 2004: Coalities
 *  door Jan Kuipers
 */

using namespace std;

#include <iostream>
#include <vector>

const int perc_v = 50;
const int perc_p = 60;

int N,V,P;
vector<int> v,p;
vector<vector<int> > count;
int coal, crit;

int main () {

  int run,runs;
  cin >> runs;

  for (run=0; run<runs; run++) {
    cin >> N;

    v=p=vector<int>(N);
    V=P=0;

    for (int i=0; i<N; i++) {
      cin >> v[i] >> p[i];
      V+=v[i];
      P+=p[i];
    }

    count=vector<vector<int> >(V+1, vector<int>(P+1, 0));
    count[0][0]=1;

    for (int i=1; i<N; i++)
      for (int vv=V; vv>=v[i]; vv--)
        for (int pp=P; pp>=p[i]; pp--)
          count[vv][pp] += count[vv-v[i]][pp-p[i]];

    coal=crit=0;

    for (int vv=0; vv<=V; vv++)
      for (int pp=0; pp<=P; pp++) {
        if (100*vv>=perc_v*V && 100*pp>=perc_p*P) coal+=count[vv][pp];
        if (100*(vv+v[0])>=perc_v*V && 100*(pp+p[0])>=perc_p*P) coal+=count[vv][pp];

        if (100*(vv+v[0])>=perc_v*V && 100*(pp+p[0])>=perc_p*P &&
          (100*vv<perc_v*V || 100*pp<perc_p*P)) crit+=count[vv][pp];
      }

    cout << coal << " " << crit << endl;
  }

  return 0;
}
