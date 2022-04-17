//
//  main.cpp
//  线段树
//
//  Created by LiZnB on 2020/11/26.
//

#include <cstdio>
#include <cstring>
#include <algorithm>

#define ls tree[pos].l
#define rs tree[pos].r
using namespace std;

const int N = 100000 + 10;

struct Tree {
    struct Node {
        int l, r;
        long long val;
    } tree[N * 4];
    
    long long lazy[N * 4];
    
    void Init() {
        memset(lazy, 0ll, sizeof(lazy));
    }
    Tree() {
        memset(lazy, 0ll, sizeof(lazy));
    }
    
    void Build(int L, int R, int pos) {
        ls = L;
        rs = R;
        if (L == R) {
            scanf("%lld", &tree[pos].val);
            return;
        }
        int m = L + (R - L) / 2;
        Build(L, m, pos << 1);
        Build(m + 1, R, pos << 1 | 1);
        tree[pos].val = tree[pos << 1].val + tree[pos << 1 | 1].val;
    }
    
    void Down(int pos) {
        if (lazy[pos] != 0) {
            tree[pos << 1].val += (tree[pos << 1].r - tree[pos << 1].l + 1) * lazy[pos];
            tree[pos << 1 | 1].val += (tree[pos << 1 | 1].r - tree[pos << 1 | 1].l + 1) * lazy[pos];
            lazy[pos << 1] += lazy[pos];
            lazy[pos << 1 | 1] += lazy[pos];
            lazy[pos] = 0;
        }
    }
    
    void Modify(int pos, int L, int R, long long val) {
        if (rs <= R && ls >= L) {
            tree[pos].val += 1ll * (rs - ls + 1) * val;
            lazy[pos] += val;
            return;
        }
        Down(pos);
        int m = ls + (rs - ls) / 2;
        if (L <= m) Modify(pos << 1, L, R, val);
        if (R > m) Modify(pos << 1 | 1, L, R, val);
        tree[pos].val = tree[pos << 1].val + tree[pos << 1 | 1].val;
    }
    
    long long Query(int pos, int L, int R) {
        if (ls >= L && rs <= R) {
            return tree[pos].val;
        }
        Down(pos);
        int m = ls + (rs - ls) / 2;
        long long ans = 0ll;
        if (m >= L) ans += Query(pos << 1, L, R);
        if (m < R) ans += Query(pos << 1 | 1, L, R);
        tree[pos].val = tree[pos << 1].val + tree[pos << 1 | 1].val;
        return ans;
    }
} T;

int n, m;

int main() {
    scanf("%d %d", &n, &m);
    T.Init();
    T.Build(1, n, 1);
    int ord, x, y;
    long long k;
    for (int i = 1; i <= m; i++) {
        scanf("%d", &ord);
        if (ord == 1) {
            scanf("%d %d %lld", &x, &y, &k);
            T.Modify(1, x, y, k);
        } else {
            scanf("%d %d", &x, &y);
            printf("%lld\n", T.Query(1, x, y));
        }
    }
    
    return 0;
}
