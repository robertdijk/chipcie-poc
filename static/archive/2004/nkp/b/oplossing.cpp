/*
 *  NKP 2004: Mikado
 *  door Jan Kuipers
 */

using namespace std;

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

class line;

class point {
public:
  int x,y;
  point () { x=y=0; }
  point (int _x, int _y) { x=_x; y=_y; }
  point (line l);
};

class line {
public:
  point p,q;
  line () { p=q=point(); }
  line (point _p, point _q) { p=_p; q=_q; }
};

point::point (line l) { x=l.q.x-l.p.x; y=l.q.y-l.p.y; }

point operator - (point p, point q) { return point(p.x-q.x, p.y-q.y); }
int operator * (point p, point q) { return p.x*q.x+p.y*q.y; }  // inner product
int operator ^ (point p, point q) { return p.x*q.y-p.y*q.x; }  // cross product

int sign (int x) { return x==0 ? 0 : x/abs(x); }

int N;
vector<line> l;
vector<vector<bool> > sect;
vector<bool> u;

void read () {

  cin >> N;
  l=vector<line>(N);

  for (int i=0; i<N; i++) {
    int x1,y1,x2,y2;
    cin >>x1>>y1>>x2>>y2;
    l[i]=line(point(x1,y1),point(x2,y2));
  }
}

bool intersect (line a, line b) {
  if ((a^b) != 0)
    return sign(a^b.p-a.p)*sign(a^b.q-a.p)<=0 && sign(b^a.p-b.p)*sign(b^a.q-b.p)<=0;

  if ((a^a.p-b.p) != 0)
    return false;

  if ((b.p*b>?b.q*b) < (a.p*b<?a.q*b)) return false;
  if ((a.p*b>?a.q*b) < (b.p*b<?b.q*b)) return false;

  return true;
}

int count (int n) {
  if (u[n]) return 0;
  u[n]=true;

  int res=1;
  for (int i=0; i<N; i++)
    if (sect[n][i]) res+=count(i);

  return res;
}

void solve () {

  sect = vector<vector<bool> >(N, vector<bool>(N));
  for (int i=0; i<N; i++)
    for (int j=0; j<N; j++)
      sect[i][j] = intersect(l[i], l[j]);

  u=vector<bool>(N,false);

  vector<int> c(N+1,0);
  for (int i=0; i<N; i++) c[count(i)]++;

  bool first=true;

  for (int i=N; i>=1; i--)
    if (c[i]>0) {
      if (!first) cout<<" "; else first=false;
      cout << c[i] << "x" << i;
    }

  cout << endl;
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
