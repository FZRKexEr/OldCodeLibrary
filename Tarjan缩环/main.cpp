//
//  main.cpp
//  Tarjan缩环
//
//  Created by LiZnB on 2020/12/5.
//

#include <cstdio>
#include <cstring>
#include <algorithm>
#define Mem(x) memset(x, 0, sizeof(x));
using namespace std;

const int N = 4 * 100000 + 10;

struct Edge {
    int v, nxt;
};

struct PIC {
    Edge edge[N * 2];
    int first[N], top;
    
    void Init() {
        memset(first, -1, sizeof(first));
        top = 0;
    }
    
    void add(int u, int v) {
        edge[top++] = (Edge) {v, first[u]};
        first[u] = top - 1;
    }
} e1, e2;

struct Tarjan {
    int dfn[N], low[N], belong[N], ins[N], stk[N];
    int time, cnt, p;
    
    void Init() {
        Mem(dfn);
        Mem(low);
        Mem(belong);
        Mem(ins);
        Mem(stk);
        time = cnt = p = 0;
    }
    
    void tarjan(int n) {
        dfn[n] = low[n] = ++time;
        stk[++p] = n;
        ins[n] = 1;
        for (int i = e1.first[n]; i != -1; i = e1.edge[i].nxt) {
            int v = e1.edge[i].v;
            if (dfn[v] == 0) {
                tarjan(v);
                low[n] = min(low[v], low[n]);
            } else if (ins[v]){
                low[n] = min(dfn[v], low[n]);
            }
        }
        if (dfn[n] == low[n]) {
            cnt++;
            do {
                belong[stk[p]] = cnt;
                ins[stk[p--]] = 0;
            } while (stk[p + 1] != n);
        }
    }
    
} T;

int data[N], sum[N], f[N];

int DAG(int x) {
    if (f[x]) return f[x];
    f[x] = sum[x];
    for (int i = e2.first[x]; i != -1; i = e2.edge[i].nxt) {
        int v = e2.edge[i].v;
        f[x] = max(f[x], sum[x] + DAG(v));
    }
    return f[x];
}

int main() {
//    freopen("a.in", "r", stdin);
    int n, m, u, v;
    e1.Init();
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &data[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &u, &v);
        e1.add(u, v);
    }
    T.Init();
    for (int i = 1; i <= n; i++) {
        if (T.dfn[i] == 0) T.tarjan(i);
    }
    
    e2.Init();
    for (int i = 1; i <= n; i++) {
        int u = T.belong[i];
        sum[u] += data[i];
        for (int j = e1.first[i]; j != -1; j = e1.edge[j].nxt) {
            int v = T.belong[e1.edge[j].v];
            if (v != u) e2.add(u, v);
        }
    }
    memset(f, 0, sizeof(f));
    int ans = -1;
    for (int i = 1; i <= T.cnt; i++) {
        ans = max(ans, DAG(i));
    }
    printf("%d", ans);
    return 0;
}
