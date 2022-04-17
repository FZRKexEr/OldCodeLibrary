//
//  main.cpp
//  最小费用最大流zkw MCMF
//
//  Created by LiZnB on 2021/7/27.
//

#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
const int N = 5000;

struct Edge {
    int u, v, cap, flow, cost;
};

struct ZKW_MCMF {
    vector <Edge> edge;
    vector <int> G[N];
    
    int vis[N], d[N];
    int s, t, m;
    long long cost;
    
    void init(int n) {
        for (int i = 0; i <= n; i++) G[i].clear();
        edge.clear();
    }
    
    void add(int u, int v, int cap, int cost) {
        edge.push_back((Edge) {u, v, cap, 0, cost});
        edge.push_back((Edge) {v, u, 0, 0, -cost});
        m = edge.size();
        G[u].push_back(m - 2);
        G[v].push_back(m - 1);
    }

    bool SPFA() {
        memset(vis, 0, sizeof(vis));
        memset(d, INF, sizeof(d));
        deque <int> que;
        que.push_front(t);
        vis[t] = 1, d[t] = 0;
        
         while(!que.empty()) {
            int x = que.front(); que.pop_front();
            
            for (int i = 0; i < G[x].size(); i++) {
                Edge & e = edge[G[x][i] ^ 1];
                int v = edge[G[x][i]].v;
                if(e.cap - e.flow && d[x] + e.cost < d[v]) {
                    d[v] = d[x] + e.cost;
                    if(!vis[v]) {
                        vis[v] = true;
                        if(d[x] > d[v]) que.push_front(v);
                        else que.push_back(v);
                    }
                }
            }
            vis[x] = false;
        }
        return d[s] != INF;
    }
    int DFS(int x, int low) {
        vis[x] = true;
        if(x == t) return low;
        int flow = 0, f;
        for (int i = 0; i < G[x].size(); i++) {
            Edge & e = edge[G[x][i]];
            if(d[e.v] == d[x] - e.cost && e.cap - e.flow && !vis[e.v]) {
                f = DFS(e.v, min(low, e.cap - e.flow));
                flow += f;
                low -= f;
                e.flow += f;
                edge[G[x][i] ^ 1].flow -= f;
                cost += 1ll * f * e.cost;
                if(!low) break;
            }
        }
        return flow;
    }
    long long Mincost (int s, int t, int & flow) {
        this -> s = s, this -> t = t;
        flow = 0, cost = 0ll;
        while(SPFA()) {
            vis[t] = 1;
            while(vis[t]) {
                memset(vis, 0, sizeof(vis));
                flow += DFS(s, INF);
            }
        }
        return cost;
    }
    
} mcmf;


int cnt[N][N];
int main() {
    int n, m, val;
    scanf("%d %d", &m, &n);

    int s = 0, t = n * m + n + 1, tot = 0;
    
    mcmf.init(t);
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cnt[i][j] = ++tot + n;
            mcmf.add(cnt[i][j], t, 1, 0);
        }
    }
    
    for (int i = 1; i <= n; i++) {
        mcmf.add(s, i, 1, 0);
        for (int j = 1; j <= m; j++) {
            scanf("%d", &val);
            for (int k = 1; k <= n; k++) { // 倒数第几个修
                mcmf.add(i, cnt[j][k], 1, 1ll * val * k);
            }
        }
    }

    int flow;
    long long cost;
    cost = mcmf.Mincost(s, t, flow);
    printf("%.2lf\n", (double)cost * 1.0 / n);
    return 0;
}
