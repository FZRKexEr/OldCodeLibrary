//
//  main.cpp
//  拓扑排序(队列+DFS)
//
//  Created by LiZnB on 2021/7/21.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
const int N = 100000 + 10;
const int M = 100000 + 10;
struct Edge {
    int v, nxt; 
} edge[M * 2];

int first[N], top = 0;

void add(int u, int v) {
    edge[top++] = (Edge) {v, first[u]};
    first[u] = top - 1;
}

int degree[N];

queue <int> que;

bool toposort(int n) {
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 0) que.push(i);
    }
    int cnt = 0;
    while (!que.empty()) {
        int x = que.front(); que.pop();
        printf("%d ", x);
        cnt++;
        for (int i = first[x]; i != -1; i = edge[i].nxt) {
            int v = edge[i].v;
            degree[v]--;
            if (degree[v] == 0) que.push(v);
        }
    }
    if (cnt == n) return true;
    return false;
}



int main() {
    memset(first, -1, sizeof(first));
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        while (scanf("%d", &x) && x != 0) {
            add(i, x);
            degree[x]++;
        }
    }
    toposort(n);
    return 0;
}

