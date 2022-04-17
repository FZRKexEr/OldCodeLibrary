//
//  main.cpp
//  二维线段树
//
//  Created by LiZnB on 2020/12/15.
//

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <assert.h>
using namespace std;
const int N = 505;

inline long long gcd(long long a, long long b) {
    if (!b) return a;
    return gcd(b, a % b);
}

long long d[N][N];

struct Tree2Tree {
    int n, m;
    
    struct Tree {
        int l, r, len;
        
        struct Node {
            int l, r;
            long long val;
        } tree[N * 4];
        
        Tree() { len = -1;}
        
        inline void Build(int col, int pos, int L, int R) {
            len = max(len, pos);
            tree[pos].l = L;
            tree[pos].r = R;
            if (L == R) {
                tree[pos].val = d[L][col];
                return;
            }
            int mid = L + (R - L) / 2;
            Build(col, pos << 1, L, mid);
            Build(col, pos << 1 | 1, mid + 1, R);
            tree[pos].val = gcd(tree[pos << 1].val, tree[pos << 1 | 1].val);
        }
        
        inline long long Query(int pos, int L, int R) {
            if (tree[pos].l >= L && tree[pos].r <= R) {
                return tree[pos].val;
            }
            int mid = tree[pos].l + (tree[pos].r - tree[pos].l) / 2;
            long long ans = 0ll;
            if (L <= mid) ans = gcd(ans, Query(pos << 1, L, R));
            if (mid < R) ans = gcd(ans, Query(pos << 1 | 1, L, R));
            return ans;
        }
        
        inline Tree operator + (const Tree & oth) const {
            Tree res;
            res.len = len;
            res.l = min(l, oth.l);
            res.r = max(r, oth.r);
            for (int i = 1; i <= len; i++) {
                res.tree[i].val = gcd(tree[i].val, oth.tree[i].val);
                res.tree[i].l = tree[i].l;
                assert(tree[i].l == oth.tree[i].l);
                res.tree[i].r = tree[i].r;
            }
            return res;
        }
    } t[4 * N];
    
    inline void Build(int pos, int L, int R) {
        if (L == R) {
            t[pos].l = L;
            t[pos].r = R;
            t[pos].Build(L, 1, 1, n);
            return;
        }
        int mid = L + (R - L) / 2;
        Build(pos << 1, L, mid);
        Build(pos << 1 | 1, mid + 1, R);
        t[pos] = t[pos << 1] + t[pos << 1 | 1];
    }
    
    inline long long Query(int pos, int x1, int y1, int x2, int y2) {
        if (t[pos].l >= y1 && t[pos].r <= y2) {
            return t[pos].Query(1, x1, x2);
        }
        int mid = t[pos].l + (t[pos].r - t[pos].l) / 2;
        long long ans = 0ll;
        if (mid >= y1) ans = gcd(ans, Query(pos << 1, x1, y1, x2, y2));
        if (mid < y2) ans = gcd(ans, Query(pos << 1 | 1, x1, y1, x2, y2));
        return ans;
    }
    
} T;

bool check(int len) {
    for (int i = 1; i <= T.n; i++) {
        for (int j = 1; j <= T.m; j++) {
            int x1 = i - len, y1 = j - len, x2 = i + len, y2 = j + len;
            if (x1 <= 0 || y1 <= 0 || x2 > T.n || y2 > T.m) continue;
            if (T.Query(1, x1, y1, x2, y2) == d[i][j]) return true;
        }
    }
    return false;
}

int lower_bound() {
    int l = 0, r = (min(T.m, T.n) - 1) / 2;
    
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    
    if (l - 1 >= 0 && check(l - 1)) return l - 1;
    return -1;
}

int main() {
    freopen("in.txt", "r", stdin);
    double st = clock();
    
    scanf("%d %d", &T.n, &T.m);
    for (int i = 1; i <= T.n; i++) {
        for (int j = 1; j <= T.m; j++) {
            scanf("%lld", &d[i][j]);
        }
    }
    int cnt = 0;
    T.Build(1, 1, T.m);
    int max_len = lower_bound();

    printf("%d\n", (1 + 2 * max_len) * (1 + 2 * max_len));

    for (int i = 1; i <= T.n; i++) {
        for (int j = 1; j <= T.m; j++) {
            int x1 = i - max_len, y1 = j - max_len, x2 = i + max_len, y2 = j + max_len;
            if (x1 <= 0 || y1 <= 0 || x2 > T.n || y2 > T.m) continue;
            if (T.Query(1, x1, y1, x2, y2) == d[i][j]) cnt++;
        }
    }

    printf("%d", cnt);
    double ed = clock();
 //   printf("\n%lf", (ed - st) / CLOCKS_PER_SEC);
    return 0;
}
