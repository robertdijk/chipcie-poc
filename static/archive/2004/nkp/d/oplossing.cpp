/*
 *  NKP 2004: Drugsbende
 *  door Jan Kuipers
 */

using namespace std;

#include <iostream>
#include <vector>

int N,K;
vector<int> x;

bool possible (int D) {
  int prev=x[0],i=0;
  for (int k=1; k<K; k++) {
    while (i<N && x[i]<prev+D) i++;
    if (i==N) return false;
    prev=x[i];
  }
  return true;    
}

int main () {

  int run,runs;
  cin >> runs;
  
  for (run=0; run<runs; run++) {
    cin >> N >> K;
    x = vector<int>(N);
    for (int i=0; i<N; i++) cin >> x[i];

    int low=1, upp=x[N-1];
    while (low != upp) {
      int mid=(low+upp+1)/2;
      if (possible(mid)) low=mid; else upp=mid-1;
    }

    cout << low << endl;
  }

  return 0;
}
