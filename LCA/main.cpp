//
//  main.cpp
//  LCA
//
//  Created by LiZnB on 2021/8/9.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 500000 + 10;

struct Edge {
    int v, nxt;
} edge[N * 2];

int first[N], top;

void add(int u, int v) {
    edge[top++] = (Edge) {v, first[u]};
    first[u] = top - 1;
}

struct LCA {
    int d[N], p[N][20];
    
    void DFS(int pos, int fa) {
        p[pos][0] = fa;
        for (int i = first[pos]; i != -1; i = edge[i].nxt) {
            int v = edge[i].v;
            if (v == fa) continue;
            d[v] = d[pos] + 1;
            DFS(v, pos);
        }
    }
    
    void Init(int s, int n) {
        d[s] = 1;
        DFS(s, -1);
        for (int level = 1; (1 << level) <= n; level++) {
            for (int i = 1; i <= n; i++) {
                p[i][level] = p[p[i][level - 1]][level - 1];
            }
        }
    }
   
    int Lca(int a, int b) {
        int i, j;
        if (d[a] < d[b]) swap(a, b);
        for (i = 0; (1 << i) <= d[a]; i++);
        i--;
        for (j = i; j >= 0; j--) {
            if (d[a] - (1 << j) >= d[b]) {
                a = p[a][j];
            }
        }
        if (a == b) return a;
        for (j = i; j >= 0; j--) {
            if (p[a][j] != p[b][j]) {
                a = p[a][j];
                b = p[b][j];
            }
        }
        return p[a][0];
    }
    
} T;


int main() {
    memset(first, -1, sizeof(first));
    int n, m, s;
    int u, v;
    scanf("%d %d %d", &n, &m, &s);
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &u, &v);
        add(u, v);
        add(v, u);
    }
    T.Init(s, n);
    int a, b;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &a, &b);
        printf("%d\n", T.Lca(a, b));
    }
    
    return 0;
}
