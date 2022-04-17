/**   author:  LiZnB
 *    created: 12.11.2021 21:38:30
 **/
#include <bits/stdc++.h>
#define int long long

using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f3f3f3f3f;

struct Edge {
  int u, v, cap, flow;
  Edge(int a, int b, int c, int d): u(a), v(b), cap(c), flow(d) {}
};

struct EdmondsKarp {
  int n, m;
  vector<Edge> edge; // 可以快速找到反向边的邻接表写法
  vector<int> G[N];
  int a[N]; // 起点到i的可以增广的量
  int p[N]; // 最短路树中访问i的边的编号
  
  void init(int n) {
    for (int i = 0; i < n; i++) G[i].clear();
    edge.clear();
  }

  void add(int u, int v, int cap) {
    edge.push_back(Edge(u, v, cap, 0));
    edge.push_back(Edge(v, u, 0, 0)); // 反向边
    m = edge.size();
    G[u].push_back(m - 2);
    G[v].push_back(m - 1);
  }

  int Maxflow(int s, int t) {
    int flow = 0;
    while (true) {
      memset(a, 0, sizeof(a));  // a 应该大于0，如果a等于0表示未访问
      queue<int> Q;  // Q 做队列名是个好方法
      Q.push(s);
      a[s] = INF;
      while (!Q.empty()) {
        int x = Q.front(); Q.pop();  // 命名
        for (auto it : G[x]) {
          Edge &e = edge[it];
          if (e.cap > e.flow && !a[e.v]) {
            // 这条边还有残量 && e.v 还没被访问过
            p[e.v] = it;
            a[e.v] = min(a[x], e.cap - e.flow);
            Q.push(e.v);
          }
        }
        if (a[t]) break;
      }
      if (!a[t]) break; // s和t不连通了
      for (int u = t; u != s; u = edge[p[u]].u) {
        edge[p[u]].flow += a[t];
        edge[p[u] ^ 1].flow -= a[t];
      }
      flow += a[t];
    }
    return flow;
  }
} e;


signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    e.add(u, v, w);
  }
  cout << e.Maxflow(s, t);
  return 0;
}

