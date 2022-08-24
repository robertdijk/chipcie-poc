#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge{
  int v, p;
};

long long solve(vector<vector<Edge>> &Adj, int s, int t, long long X){
  auto remaining = vector<long long>(Adj.size(), 0);
  auto visited = vector<bool>(Adj.size(), false);

  remaining[s] = X;
  priority_queue<pair<long long, int>> q;
  q.push({X, s});
  while(!q.empty()){
    auto [ru, u] = q.top(); q.pop();
    if(u == t) break;
    if(visited[u]) continue;
    visited[u] = true;

    for(auto e : Adj[u]){
      if(!visited[e.v]){
        long long rv = (ru * (100 - e.p))/100;
        if(rv > remaining[e.v]){
          remaining[e.v] = rv;
          q.push({rv, e.v});
        }
      }
    }
  }
  return remaining[t];
}

int main(){
  int n, m, s, t;
  long long X;
  cin >> n >> m >> s >> t >> X;
  s--, t--;

  auto Adj = vector<vector<Edge>>(n, vector<Edge>());

  int u, v, p;
  for(int i=0; i<m; i++){
    cin >> u >> v >> p;
    u--, v--;
    Adj[u].push_back({v, p});
    Adj[v].push_back({u, p});
  }

  cout << solve(Adj, s, t, X) << endl;

  return 0;
}
