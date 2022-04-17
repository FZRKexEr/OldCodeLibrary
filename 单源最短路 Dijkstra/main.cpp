//
//  main.cpp
//  单源最短路
//
//  Created by LiZnB on 2020/12/4.
//

#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 0x3f3f3f3f;
struct Edge {
    int v, nxt, w;
};

struct Node {
    int pos, val;
    
    bool operator < (const Node & a) const {
        return val > a.val;
    }
    
};

const long long MOD = 1e9 + 7; // 注意修改模数

struct Dijkstra{
    Edge edge[M * 2];
    int first[N], top;
    int d[N], used[N];
    int cnt[N], pre[N];
    
    Dijkstra () {
        memset(first, -1, sizeof(first));
        top = 0;
    }
    
    void add(int u, int v, int w) {
        edge[++top] = (Edge) {v, first[u], w};
        first[u] = top;
    }
    
    priority_queue<Node> que;
    
    void BFS(int s, int all) {
        memset(used, 0, sizeof(used));
        memset(cnt, 0, sizeof(cnt));
        memset(pre, 0, sizeof(pre));

        for (int i = 0; i <= all; i++) d[i] = INF; // 如果用memset对long long不友好

        while (!que.empty())
            que.pop();
        
        que.push((Node) {s, 0});
        d[s] = 0;
        cnt[s] = 1; // 计数
        while (que.empty() == false) {
            Node n = que.top();
            que.pop();
            if (used[n.pos]) continue;
            used[n.pos] = 1;
            
            for (int i = first[n.pos]; i != -1; i = edge[i].nxt) {
                int v = edge[i].v;
                if (d[v] == d[n.pos] + edge[i].w) {
                    (cnt[v] += cnt[n.pos]) %= MOD; // 计数
                }

                if (d[v] > d[n.pos] + edge[i].w) {
                    (cnt[v] = cnt[n.pos]) %= MOD; // 计数

                    d[v] = d[n.pos] + edge[i].w;
                    que.push((Node) {v, d[v]});
                }
            }
        }
    }
    
} e;


int main() {
    int n, m, s;
    int u, v, w;
    scanf("%d %d %d", &n, &m, &s);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        e.add(u, v, w);
    }
    e.BFS(s, n);
    for (int i = 1; i <= n; i++) {
        printf("%d ", e.d[i]);
    }
    return 0;
}
