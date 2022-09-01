#include <iostream>

using namespace std;

const int MAXL = 20;
const int MAXH = 100000;
int t[MAXH][MAXL];
int len[MAXH];
int used[MAXH];
int pos[MAXH];

void print() {
  cout << "l u p  table" << endl;
  for (int i = 0; len[i] > 0; ++i) {
    cout << len[i] << ' ' << used[i] << ' ' << pos[i] << ' '; 
    for (int j = 0; j < len[i]; ++j)
      cout << ' ' << t[i][j];
    cout << endl; 
  }
}

void clear() {
  for (int i = 0; i < MAXH; ++i) {
    for (int j = 0; j < MAXL; ++j)
      t[i][j] = 0;
    len[i] = pos[i] = 0;
    used[i] = 1;
  }
}

void solve() {
  clear();

  int B; cin >> B;
  int m; cin >> m;
  for (int i = 0; i < m; ++i) {
    cin >> t[i][0];
    len[i] = 1;
  }
  int q; cin >> q;

  bool imp = false;
  for (int i = 0; i < m; ++i) {
    if (len[i] >= MAXL) cout << "ERROR: Too long!" << endl;
    //print();
    if (len[i] == pos[i]) continue;

    if (i == 0) {
      pos[i] = len[i];
    } else if (len[i-1] - used[i-1] > 0) {
      int res = t[i-1][used[i-1]] + t[i-1][used[i-1]-1];
      if (t[i][pos[i]] != res ||
	  (res/B > 0 && len[i] > pos[i]+1 && t[i][pos[i]+1] != 1)) {
	imp = true;
	break;
      }

      used[i-1]++;
      pos[i]++;

      if (res/B > 0) {
	if (len[i] == pos[i]+1) {
	  t[i][len[i]] = 1;
	  len[i]++;
	}

	pos[i]++;
      }

    } else {
      int res = t[i][pos[i]] - t[i-1][used[i-1]-1];

      t[i-1][len[i-1]] = res<0 ? res+B : res;
      len[i-1]++;
      used[i-1]++;
      pos[i]++;
      if (res < 0) {
	t[i][len[i]] = 1; 
	len[i]++;
	pos[i]++;
      }

      i -= 2;
      continue;
    }
  }

  if (imp) {
    cout << "impossible" << endl;
    return;
  }

  int h = m;
  int i = h-1;
  while(h < q) {
    if (i < 0) {
      cout << "unpredictable" << endl;
      return;
    }
    if (len[i] >= MAXL) cout << "ERROR: Too long!" << endl;

    if (len[i] > used[i]) {
      int res = t[i][used[i]] + t[i][used[i]-1];

      used[i]++;
      t[i+1][len[i+1]] = res%B;
      len[i+1]++;

      if (res/B > 0) {
	t[i+1][len[i+1]] = 1;
	len[i+1]++;
      }

      i++;
    } else {
      i--;
    }

    if (i == h) ++h;
  }

  cout << t[q-1][0] << endl;
}

int main() {
  int n;
  cin >> n;
  for (;n; --n) solve();
  return 0;
}
