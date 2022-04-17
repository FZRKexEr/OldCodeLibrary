//
//  main.cpp
//  Segment Tree Beats
//
//  Created by LiZnB on 2021/11/20.
//
//  HDU 5306
//  Created by LiZnB at 16:39:13 on 2021/09/26.
//

#include <bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
const long long N = 1e6 + 10;

void run() {
#ifdef ONLINE_JUDGE
#else
  freopen("in1.txt","r",stdin);
#endif
}


// 区间覆盖最小值+区间最值+区间和
// 永久化标记线段树(没法完成, 因为对节点的modify不能每一层都进行)

int a[N + 10];
struct Segment_T {
#define ls tree[pos].l
#define rs tree[pos].r

  long long lazy[N * 4];

  struct Value {
    long long sum, mx, se, t;
    // 区间和，最大值，严格次大值，最大值个数
  };
  struct Node {
    long long l, r;
    Value val;
  } tree[N * 4];

  void Init(int n) {
    for (int i = 1; i <= 4 * n; i++) {
      lazy[i] = INF;
    }
  }
  // 默认 pos L R val
  Value up(Value vl, Value vr) { // OK
    Value res;
    res.sum = vl.sum + vr.sum;
    res.mx = max(vl.mx, vr.mx);

    if (vl.mx > vr.mx) {
      res.t = vl.t;
      res.se = max(vl.se, vr.mx);
    } else if (vl.mx == vr.mx) {
      res.t = vl.t + vr.t;
      res.se = max(vl.se, vr.se);
    } else {
      res.t = vr.t;
      res.se = max(vr.se, vl.mx);
    }
    return res;
  }

  void Down(); // 先声明
  void add(int pos, int val) {
    Value &t = tree[pos].val;
    if (val >= t.mx) return; // 加上保险
    if (val < t.mx && val > t.se) {
      t.sum += (val - t.mx) * t.t;
      t.mx = val;
      // 在本层就终止了，打上lazy标记
      lazy[pos] = min(lazy[pos], val);
    } else if (val <= t.se) { // 需要向下走了
      Down(pos); // lazy 下传
      add(pos << 1, val);
      add(pos << 1 | 1, val);

      t = up(tree[pos << 1].val, tree[pos << 1 | 1].val);
    }
  }

  void Build(int pos, int L, int R) { // OK
    ls = L;
    rs = R;
    int m = L + (R - L) / 2;
    if (L == R) {
      tree[pos].val.sum = a[L];
      tree[pos].val.mx = a[L];
      tree[pos].val.se = -INF;
      tree[pos].val.t = 1;
      return;
    }
    Build(pos << 1, L, m);
    Build(pos << 1 | 1, m + 1, R);
    tree[pos].val = up(tree[pos << 1].val, tree[pos << 1 | 1].val);
  }

  void Down(int pos) {
    add(pos << 1, lazy[pos]);
    add(pos << 1 | 1, lazy[pos]);
    lazy[pos] = INF;
  }

  void Modify(int pos, int L, int R, long long val) {
    if (val >= tree[pos].val.mx) return;
    if (rs <= R && ls >= L) {
      add(pos, val); // 内含打lazy
      return;
    }
    Down(pos);
    int m = ls + (rs - ls) / 2;
    if (L <= m) Modify(pos << 1, L, R, val);
    if (R > m) Modify(pos << 1 | 1, L, R, val);
    tree[pos].val = up(tree[pos << 1].val, tree[pos << 1 | 1].val);
  }
  Value Query(int pos, int L, int R) { // OK
    if (rs <= R && ls >= L) {
      return tree[pos].val;
    }
    Down(pos);
    int m = ls + (rs - ls) / 2;
    Value res;
    if (R <= m) {
      res = Query(pos << 1, L, R);
    } else if (L > m) {
      res = Query(pos << 1 | 1, L, R);
    } else {
      res = up(Query(pos << 1, L, R), Query(pos << 1 | 1, L, R));
    }
    tree[pos].val = up(tree[pos << 1].val, tree[pos << 1 | 1].val);
    return res;
  }
#undef ls
#undef rs
} T;

signed main() {
  run();
  int z; scanf("%lld", &z);
  while (z--) {
    int n, m;
    scanf("%lld %lld", &n, &m);
    T.Init(n);
    for (int i = 1; i <= n; i++) {
      scanf("%lld", a + i);
    }
    T.Build(1, 1, n);
    for (int i = 1; i <= m; i++) {
      int o, l, r, val;
      scanf("%lld %lld %lld", &o, &l, &r);
      if (o == 1) {
        Segment_T::Value ans = T.Query(1, l, r);
        printf("%lld\n", ans.mx);
      } else if (o == 2) {
        Segment_T::Value ans = T.Query(1, l, r);
        printf("%lld\n", ans.sum);
      } else {
        scanf("%lld", &val);
        T.Modify(1, l, r, val);
      }
    }
  }

  return 0;
}

/*
default_random_engine seed((unsigned int)time(NULL));
uniform_int_distribution<long long> U(1, 1e9);
*/

