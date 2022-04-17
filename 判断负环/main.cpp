//
//  main.cpp
//  判断负环
//
//  Created by LiZnB on 2020/12/5.
//  洛谷P3385 【模板】负环
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
using namespace std;
const int N = 1e5;
const int M = 1e6;
const int INF = 0x3f3f3f3f;

int num = 0;
struct Edge {
    int v, w, nxt;
};

struct SPFA {
    int d[N], first[N], inque[N], cnt[N];
    int top, flag;
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
    int n, m, t;
    int u, v, w;
    scanf("%d", &t);
    while (t--) {
        spfa.Init();
        scanf("%d %d", &n, &m);
                for (int i = 1; i <= m; i++) {
            scanf("%d %d %d", &u, &v, &w);
            if (w >= 0) {
                spfa.add(u, v, w);
                spfa.add(v, u, w);
            } else {
                spfa.add(u, v, w);
            }
        }

        spfa.BFS(n, 1);
        if (spfa.flag) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}

