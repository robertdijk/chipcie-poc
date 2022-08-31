/*
 *  NKP 2004: Rondje om de Wereld
 *  door Jan Kuipers
 */

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <map>

class location {
public:
  string name;
  int latt;
  vector<int> conn;
  
  location () {
   name=""; latt=0; conn=vector<int>();
  }
  location (string _name, int _latt) {
    name=_name; latt=_latt; conn=vector<int>();
  }
};

vector<location> loc;
vector<int> angle;
bool possible;

void read () {
  string name1,name2;
  int N,M,latt,dummy;
  
  cin >> N;
  loc=vector<location>(N);
  map<string,int> number;

  for (int i=0; i<N; i++) {
    cin >> name1 >> dummy >> latt;
    loc[i] = location(name1,latt);
    number[name1] = i;
  }

  cin >> M;
  
  for (int i=0; i<M; i++) {
    cin >> name1 >> name2;
    int n1=number[name1], n2=number[name2];
    loc[n1].conn.push_back(n2);
    loc[n2].conn.push_back(n1);
  }    
}

void search (int n, int nowangle) {

  if (angle[n]!=-999 && nowangle!=angle[n]) possible=true;
  if (angle[n]!=-999) return;

  angle[n]=nowangle;
  for (int i=0; i<loc[n].conn.size(); i++) {
    int next = loc[n].conn[i];
    int diff = loc[next].latt - loc[n].latt;
    if (diff > 180) diff = diff-360;
    if (diff < -180) diff = diff+360;
    
    search (next, nowangle+diff);
  }
}

void solve () {

  possible=false;
  angle=vector<int>(loc.size(), -999);
  search(0,0);
  cout << (possible ? "ja" : "nee") << endl;
}

int main () {

  int run,runs;
  cin >> runs;
  
  for (run=0; run<runs; run++) {
    read (); 
    solve (); 
  }
  
  return 0;
}
