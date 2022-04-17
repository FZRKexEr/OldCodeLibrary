//
//  main.cpp
//  永久化标记线段树
//
//  Created by LiZnB on 2020/12/15.
//

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define ls tree[pos].l
#define rs tree[pos].r
using namespace std;
const int N = 1e6;


// 区间加法 + 区间求和
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
    
    void Build(int pos, int L, int R) {
        ls = L;
        rs = R;
        int m = L + (R - L) / 2;

        if (L == R) {
            scanf("%lld", &tree[pos].val);
            return;
        }
        Build(pos << 1, L, m);
        Build(pos << 1 | 1, m + 1, R);
        tree[pos].val = tree[pos << 1].val + tree[pos << 1 | 1].val;
    }
        
    void Modify(int pos, int L, int R, long long val) {
        tree[pos].val += (R - L + 1) * val;
        if (ls == L && rs == R) {
            lazy[pos] += val;
            return;
        }
        int m = ls + (rs - ls) / 2;
        if (m >= L) Modify(pos << 1, L, min(m, R), val);
        if (m < R) Modify(pos << 1 | 1, max(m + 1, L), R, val);
    }
    
    long long Query(int pos, int L, int R, long long val) {
        if (ls == L && rs == R) {
            return tree[pos].val + val * (R - L + 1);
        }
        int m = ls + (rs - ls) / 2;
        long long ans = 0ll;
        if (m >= L) ans += Query(pos << 1, L, min(m, R), val + lazy[pos]);
        if (m < R) ans += Query(pos << 1 | 1, max(m + 1, L), R, val + lazy[pos]);
        return ans;
    }
} T;

// 区间赋值+区间最值
//struct Tree {
//    struct Node {
//        int l, r;
//        long long val;
//    } tree[N * 4];
//
//    long long lazy[N * 4];
//
//    void Init() {
//        memset(lazy, 0ll, sizeof(lazy));
//    }
//    Tree() {
//        memset(lazy, 0ll, sizeof(lazy));
//    }
//
//    void Build(int L, int R, int pos) {
//        ls = L;
//        rs = R;
//        if (L == R) {
//            tree[pos].val = 0;
//            return;
//        }
//        int m = L + (R - L) / 2;
//        Build(L, m, pos << 1);
//        Build(m + 1, R, pos << 1 | 1);
//        tree[pos].val = max(tree[pos << 1].val, tree[pos << 1 | 1].val);
//    }
//
//
//    void Down(int pos) {
//        if (lazy[pos] != 0) {
//            tree[pos << 1].val = lazy[pos];
//            tree[pos << 1 | 1].val = 1 * lazy[pos];
//            lazy[pos << 1] = lazy[pos];
//            lazy[pos << 1 | 1] = lazy[pos];
//            lazy[pos] = 0;
//        }
//    }
//
//    void Modify(int pos, int L, int R, long long val) {
//        if (rs <= R && ls >= L) {
//            tree[pos].val = val;
//            lazy[pos] = val;
//            return;
//        }
//        Down(pos);
//        int m = ls + (rs - ls) / 2;
//        if (L <= m) Modify(pos << 1, L, R, val);
//        if (R > m) Modify(pos << 1 | 1, L, R, val);
//        tree[pos].val = max(tree[pos << 1].val, tree[pos << 1 | 1].val);
//    }
//
//    long long Query(int pos, int L, int R) {
//        if (ls >= L && rs <= R) {
//            return tree[pos].val;
//        }
//        Down(pos);
//        int m = ls + (rs - ls) / 2;
//        long long ans = 0ll;
//        if (m >= L) ans = max(ans, Query(pos << 1, L, R));
//        if (m < R) ans = max(ans, Query(pos << 1 | 1, L, R));
//        tree[pos].val = max(tree[pos << 1].val, tree[pos << 1 | 1].val);
//        return ans;
//    }
//} T;

// 维护复杂情况线段树
//const int N = 200000 + 10;
//
//struct Value {
//    int l, r, val, lval, rval, flag; // 是否是一个整体
//};
//
//struct Node {
//    int l, r;
//    Value val;
//};
//int getval(int len) {
//    return (len + 1) * len / 2;
//}
//
//
//struct Tree {
//    Node tree[N * 4];
//      Value up(Value l, Value r) {
//        Value res;
//        res.lval = l.lval;
//        res.rval = r.rval;
//        if (l.rval <= r.lval) {
//            res.l = l.l;
//            res.r = r.r;
//            res.val = l.val + r.val;
//            if (l.flag == true) {
//                assert(l.l == l.r);
//                res.l += r.l;
//            }
//            if (r.flag == true) {
//                assert(r.l == r.r);
//                res.r += l.r;
//            }
//            if (l.flag && r.flag) {
//                res.flag = true;
//            } else {
//                res.flag = false;
//            }
//            if (l.flag == false && r.flag == false) {
//                res.val += getval(l.r + r.l);
//            }
//        } else {
//            res.flag = false;
//            res.l = l.l;
//            res.r = r.r;
//            res.val = l.val + r.val;
//            if (l.flag == false) {
//                res.val += getval(l.r);
//            }
//            if (r.flag == false) {
//                res.val += getval(r.l);
//            }
//        }
//        return res;
//    }
//    void Build(int L, int R, int pos) {
//        ls = L;
//        rs = R;
//        if (L == R) {
//            cin >> tree[pos].val.lval;
//            tree[pos].val.rval = tree[pos].val.lval;
//            tree[pos].val.l = tree[pos].val.r = 1;
//            tree[pos].val.val = 0;
//            tree[pos].val.flag = true;
//            return;
//        }
//        int m = L + (R - L) / 2;
//        Build(L, m, pos << 1);
//        Build(m + 1, R, pos << 1 | 1);
//        tree[pos].val = up(tree[pos << 1].val, tree[pos << 1 | 1].val);
//    }
//
//    void Modify(int pos, int p, long long val) {
//        if (rs == ls) {
//            tree[pos].val = (Value) {1, 1, 0, val, val, 1};
//            return;
//        }
//        int m = ls + (rs - ls) / 2;
//        if (p <= m) Modify(pos << 1, p, val);
//        if (p > m) Modify(pos << 1 | 1, p, val);
//        tree[pos].val = up(tree[pos << 1].val, tree[pos << 1 | 1].val);
//    }
//
//    Value Query(int pos, int L, int R) {
//        if (ls >= L && rs <= R) {
//            return tree[pos].val;
//        }
//        int m = ls + (rs - ls) / 2;
//        Value ans;
//        if (m >= L && m < R) ans = up(Query(pos << 1, L, R), Query(pos << 1 | 1, L, R));
//        else if (m < R) ans = Query(pos << 1 | 1, L, R);
//        else if (m >= L) ans = Query(pos << 1, L, R);
//        tree[pos].val = up(tree[pos << 1].val, tree[pos << 1 | 1].val);
//        return ans;
//    }
//} T;




int main() {
    int n, m;
    scanf("%d %d", &n, &m);
        T.Init();
        T.Build(1, 1, n);
        int ord, x, y;
        long long k;
        for (int i = 1; i <= m; i++) {
            scanf("%d", &ord);
            if (ord == 1) {
                scanf("%d %d %lld", &x, &y, &k);
                T.Modify(1, x, y, k);
            } else {
                scanf("%d %d", &x, &y);
                printf("%lld\n", T.Query(1, x, y, 0ll));
            }
        }
    return 0;
}
