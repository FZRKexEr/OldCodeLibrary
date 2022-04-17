//
//  main.cpp
//  树状数组
//
//  Created by LiZnB on 2021/5/18.
//

#include <cstdio>
#include <cstring>

#define lowbit(x) (x & -x)
using namespace std;
const int N = 500000 + 10;


struct Tree    {
    int tree[N], all;
    
    void Init(int n) {
        memset(tree, 0, sizeof(tree)); 
        all = n;
    }
    
    void Modify(int x, int val) {
        while (x) { // 区间修改
            tree[x] += val;
            x -= lowbit(x);
        }
    }
    
    int Query(int x) { // 单点查询
        int ans = 0;
        while(x <= all) {
            ans += tree[x];
            x += lowbit(x);
        }
        return ans;
    }
} T;


int main() {
    int n, m, val;
    scanf("%d %d", &n, &m);
    T.Init(n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val);
        T.Modify(i, val);
        T.Modify(i - 1, -val);
    }
    int a, b, ord, c;
    for (int i = 1; i <= m; i++) {
        scanf("%d", &ord);
        if (ord == 1) {
            scanf("%d %d %d", &a, &b, &c);
            T.Modify(b, c);
            T.Modify(a - 1, -c);
        } else {
            scanf("%d", &a);
            printf("%d\n", T.Query(a));
        }
    }
    return 0;
}
// 二维树状数组
//#include <cstdio>
//#include <cstring>
//#include <cstdlib>
//#include <algorithm>
//#include <cmath>
//#include <iostream>
//using namespace std;
//const int N = 1e3 + 10;
//const int M = 1e3 + 10;
//
//
//
//struct Tree {
//    struct Node {
//        long long c, kc, lc, klc;
//    } tree[N][M];
//    // 牢记公式：s[i][j] = + (i + 1)(j + 1) sigma(c[k][l])
//    //                   - (j + 1) sigma(k * c[k][l])
//    //                   - (i + 1) sigma(l * c[k][l])
//    //                   + sigma(k * l * c[k][l])
//
//    int maxn, maxm;
//
//    inline int lowbit(int x) {
//        return x & -x;
//    }
//
//    void Init(int n, int m) {
//        maxn = n;
//        maxm = m;
//        memset(tree, 0ll, sizeof(tree));
//    }
//
//    // 单点更新
//    void Modify(int x, int y, long long val) {
//        int k = x, l = y;
//        for (int k = x; k <= maxn; k += lowbit(k)) {
//            for (int l = y; l <= maxm; l += lowbit(l)) {
//                tree[k][l].c += val;
//                tree[k][l].kc += x * val;
//                tree[k][l].lc += y * val;
//                tree[k][l].klc += x * y * val;
//            }
//        }
//
//    }
//
//    // 区间查询
//    long long Query(int x, int y) {
//        long long ans = 0ll;
//        for (int i = x; i > 0; i -= lowbit(i)) {
//            for (int j = y; j > 0; j -= lowbit(j)) {
//                ans += (x + 1) * (y + 1) * tree[i][j].c;
//                ans -= (x + 1) * tree[i][j].lc;
//                ans -= (y + 1) * tree[i][j].kc;
//                ans += tree[i][j].klc;
//            }
//        }
//        return ans;
//    }
//
//    void Add(int x1, int y1, int x2, int y2, long long val) {
//        Modify(x1, y1, val);
//        Modify(x2 + 1, y1, -val);
//        Modify(x1, y2 + 1, -val);
//        Modify(x2 + 1, y2 + 1, val);
//    }
//
//    long long Sol(int x1, int y1, int x2, int y2) {
//        return Query(x2, y2) - Query(x1 - 1, y2) - Query(x2, y1 - 1) + Query(x1 - 1, y1 - 1);
//    }
//} T;
//
//
//
//int main() {
//
//    int n, m, q;
//    long long val;
//    scanf("%d %d %d", &n, &m, &q);
//    T.Init(n, m);
//    for (int i = 1; i <= n; i++) {
//        for (int j = 1; j <= m; j++) {
//            scanf("%lld", &val);
//            T.Add(i, j, i, j, val);
//        }
//    }
//    for (int i = 1; i <= q; i++) {
//        int op, x1, y1, x2, y2;
//        scanf("%d %d %d %d %d", &op, &x1, &y1, &x2, &y2);
//        if (op == 1) {
//            scanf("%lld", &val);
//            T.Add(x1, y1, x2, y2, val);
//        } else {
//            printf("%lld\n", T.Sol(x1, y1, x2, y2));
//        }
//    }
//
//    return 0;
//}
