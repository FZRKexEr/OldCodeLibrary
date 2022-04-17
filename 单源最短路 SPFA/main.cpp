//
//  main.cpp
//  SPFA
//
//  Created by LiZnB on 2020/12/5.
//  

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;
const int N = 1e5;
const int M = 1e6;
const int INF = 0x3f3f3f3f;

struct Edge {
    int v, w, nxt;
};

struct SPFA {
    int d[N], first[N], inque[N], cnt[N];
    int top, flag;
    queue <int> que;
    Edge edge[M * 2];
    
    SPFA() {
        top = 0;
        memset(first, -1, sizeof(first));
    }
    
    void add(int u, int v, int w) {
        edge[top++] = (Edge) {v, w, first[u]};
        first[u] = top - 1;
    }
    
    void BFS(int all, int s) {
        flag = false;
        memset(d, INF, sizeof(d));
        memset(inque, 0, sizeof(inque));
        memset(cnt, 0, sizeof(cnt));
        
        d[s] = 0; cnt[s]++;
        que.push(s); inque[s] = true;
        
        while (que.empty() == false) {
            int n = que.front();
            que.pop(); inque[n] = false;
            
            int v, w;
            for (int i = first[n]; i != -1; i = edge[i].nxt) {
                v = edge[i].v; w = edge[i].w;
                if (d[v] > d[n] + w) {
                    d[v] = d[n] + w;
                    if (inque[v] == false) {
                        que.push(v); inque[v] = true;
                        if (++cnt[v] >= all) {
                            flag = true;
                            return;
                        }
                    }
                }
            }
        }
    }
    
} spfa;

int main() {
    int n, m, s;
    int u, v, w;
    scanf("%d %d %d", &n, &m, &s);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        spfa.add(u, v, w);
    }
    spfa.BFS(n, s);
    for (int i = 1; i <= n; i++) {
        if (spfa.d[i] == INF)
            printf("%lld ", (1ll << 31) - 1);
        else printf("%d ", spfa.d[i]);
    }
    
    return 0;
}

