/*
 *  NKP 2004: Bustijden
 *  door Jan Kuipers
 */

using namespace std;

#include <iostream>
#include <vector>

int main () {
  int run,runs;
  cin >> runs;
  
  for (run=0; run<runs; run++) {
    int N;
    cin >> N;
    int best=9*60, worst=9*60;
    
    for (int i=0; i<N; i++) {
      int newbest=99999, newworst=99999;
      int n,dt;
      cin >> n >> dt;
 
      for (int j=0; j<n; j++) {
	int h,m,t,s; char dum;
	cin >>h>>dum>>m>>dum>>s>>dum;
	t=60*h+m;
	if (t-s >= worst) newworst <?= t+s+dt;
	if (t+s >= best) newbest <?= max(t-s,best)+dt;
      }

      best=newbest;
      worst=newworst;
    }

    cout.width(2); cout.fill('0'); cout << best/60;
    cout << ":";
    cout.width(2); cout.fill('0'); cout << best%60;
    cout << " ";
    cout.width(2); cout.fill('0'); cout << worst/60;
    cout << ":";
    cout.width(2); cout.fill('0'); cout << worst%60;
    cout << endl;
  }
  
  return 0;    
}
