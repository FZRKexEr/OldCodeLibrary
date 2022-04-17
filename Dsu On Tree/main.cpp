//
//  main.cpp
//  Dsu On Tree
//
//  Created by LiZnB on 2021/10/12.


#include <bits/stdc++.h>
#define int long long
using namespace std;

void run() {
#ifdef ONLINE_JUDGE
#else
  freopen("in1.txt","r",stdin);
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
}

const int N = 1e6 + 10;
vector<int> G[N];

struct dsu_on_tree {
  int cnt[N], st[N], ft[N], ver[N];
  int sz[N], color[N], tm = 0;
  int mxans = -1, ans = -1;
  int res[N];

  dsu_on_tree() {
    memset(cnt, 0, sizeof(cnt));
  }

  void pre(int pos, int fa) {
    sz[pos] = 1;
    for (auto v : G[pos]) {
      if (v == fa) continue;
      pre(v, pos);
      sz[pos] += sz[v];
    }
  }

  void dfs(int pos, int fa, bool keep) {
    int mx = -1, bigChild = -1;
    st[pos] = ++tm;
    ver[tm] = pos;
    for (auto v : G[pos]) {
      if (v == fa) continue;
      if (sz[v] > mx) {
        mx = sz[v];
        bigChild = v;
      }
    }
    for (auto v : G[pos]) { // 去轻儿子
      if (v == fa || v == bigChild) continue;
      dfs(v, pos, 0);
    }
    if (bigChild != -1) { // 去重儿子
      dfs(bigChild, pos, 1);
    }
    ft[pos] = tm;

    // 答案维护
    for (auto v : G[pos]) { // 轻儿子答案合并到重儿子
      if (v == fa || v == bigChild) continue;

      for (int i = st[v]; i <= ft[v]; i++) {
        cnt[color[ver[i]]]++;
        if (cnt[color[ver[i]]] > mxans) {
          mxans = cnt[color[ver[i]]];
          ans = color[ver[i]];
        } else if (cnt[color[ver[i]]] == mxans) {
          ans += color[ver[i]];
        }
      }
    }

    cnt[color[pos]]++; // 现在cnt里面就是以pos为根的答案
    if (cnt[color[pos]] > mxans) {
      mxans = cnt[color[pos]];
      ans = color[pos];
    } else if (cnt[color[pos]] == mxans) {
      ans += color[pos];
    }

    res[pos] = ans;
    if (keep == 0) { // 不是重儿子就要清除对答案对贡献
      mxans = -1, ans = -1;
      for (int i = st[pos]; i <= ft[pos]; i++) {
        cnt[color[ver[i]]]--;
      }
    }
    // 答案维护

  }
} T;


signed main() {
  run();
  int n; cin >> n;
  for (int i = 1; i <= n; i++) cin >> T.color[i];
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  T.pre(1, -1);
  T.dfs(1, -1, 1);

  for (int i = 1; i <= n; i++) {
    cout << T.res[i] << " ";
  }
  return 0;
}

/*
default_random_engine seed((unsigned int)time(NULL));
uniform_int_distribution<long long> U(1, 1e9);
*/
