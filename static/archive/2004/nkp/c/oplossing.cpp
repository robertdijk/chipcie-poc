/*
 *  NKP 2004: Avondvierdaagse
 *  door Jan Kuipers
 */

using namespace std;

#include <vector>
#include <iostream>
#include <algorithm>

int main () {

  int run,runs;
  cin >> runs;

  for (run=0; run<runs; run++) {
    int N,L;
    cin >> N >> L;
    vector<pair<int,int> > v(N);
    for (int i=0; i<N; i++) cin >> v[i].first >> v[i].second;
//    sort(v.begin(),v.end());

    int sol=0, from=0;

    for (int i=0; i<N; i++) {
      if (from >= v[i].second) continue;
      from >?= v[i].first;

      int n = (v[i].second-from+L-1)/L;
      sol += n;
      from += n*L;
    }

    cout << sol << endl;
  }

  return 0;
}
