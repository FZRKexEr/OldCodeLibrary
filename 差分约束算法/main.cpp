//
//  main.cpp
//  差分约束算法
//
//  Created by LiZnB on 2020/12/5.
//  洛谷P5960 【模板】差分约束算法

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int N = 1e6;
const int M = 1e6;
const long long INF = 0x3f3f3f3f;

struct Edge {
    int v, w, nxt;
};

struct SPFA {
    int first[N], inque[N], cnt[N];
    int top, flag;
    long long d[N];
    queue <int> que;
    Edge edge[M * 2];
    
    void Init() {
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
        
        d[s] = 0ll; cnt[s]++;
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
    spfa.Init();

    int n, m;
    int u, v, w;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        spfa.add(n + 1, i, 996);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        spfa.add(u, v, w);
    }
    spfa.BFS(n + 1, n + 1);
    if (spfa.flag == true) {
        printf("NO\n");
    } else {
        for (int i = 1; i <= n; i++) {
            printf("%lld ", 233-spfa.d[i]);
        }
    }
    return 0;
}
