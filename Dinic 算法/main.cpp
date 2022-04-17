/**   author:  LiZnB
 *    created: 12.11.2021 17:20:16
 **/
#include <bits/stdc++.h>
#define int long long
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f3f3f3f3f;

using namespace std;

struct Edge {
    int u, v, cap, flow;
};

struct Dinic {
    int m;

    vector <Edge> edge;
    vector <int> G[N];
    bool vis[N];
    int d[N];
    int cur[N];

    void init(int n) {
        for (int i = 0; i <= n; i++) G[i].clear();
        edge.clear();
    }

    void add(int u, int v, int cap) {
        edge.push_back((Edge) {u, v, cap, 0});
        edge.push_back((Edge) {v, u, 0, 0});
        m = edge.size();
        G[u].push_back(m - 2);
        G[v].push_back(m - 1);
    }

    bool BFS(int s, int t) {
        memset(vis, 0, sizeof(vis));
        queue<int> que;
        que.push(s);
        d[s] = 0;
        vis[s] = 1;
        while(!que.empty()) {
            int x = que.front();
            que.pop();
            for (int i = 0; i < G[x].size(); i++) {
                Edge & e = edge[G[x][i]];
                if (!vis[e.v] && e.cap > e.flow) {
                    vis[e.v] = 1;
                    d[e.v] = d[x] + 1;
                    que.push(e.v);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int low, int t) {
        if(x == t || low == 0) return low;
        int flow = 0, f;
        for (int & i = cur[x]; i < G[x].size(); i++) {
            Edge & e = edge[G[x][i]];
            if(d[x] + 1 == d[e.v] && (f = DFS(e.v, min(low, e.cap - e.flow), t)) > 0) {
                e.flow += f;
                edge[G[x][i] ^ 1].flow -= f;
                flow += f;
                low -= f;
                if(low == 0) break;
            }
        }
        return flow;
    }

    int Maxflow(int s, int t) {
        int flow = 0;
        while(BFS(s, t)) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF, t);
        }
        return flow;
    }
} dinic;

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    dinic.add(u, v, w);
  }
  cout << dinic.Maxflow(s, t);
  return 0;
}

