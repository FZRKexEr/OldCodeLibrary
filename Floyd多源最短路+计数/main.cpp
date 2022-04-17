//
//  main.cpp
//  Floyd多源最短路+计数
//
//  Created by LiZnB on 2021/11/20.
//

#include <bits/stdc++.h>
#define int long long
const int INF = 0x3f3f3f3f3f3f3f3f;

using namespace std;

const int N = 300;
int d[N][N], cnt[N][N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m; cin >> n >> m;
  memset(d, 0x3f, sizeof(d));
  for (int i = 1; i <= n; i++) d[i][i] = 0;
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    d[u][v] = w;
    d[v][u] = w;
    cnt[v][u] = 1;
    cnt[u][v] = 1;
  }
  // Floyd 的关键是初始化和循环顺序
  // cnt 只能在有边的时候赋值为1
  // d 要在有边和自己到自己的时候赋值，不连通是INF
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (d[i][j] > d[i][k] + d[k][j]) {
          d[i][j] = d[i][k] + d[k][j];
          cnt[i][j] = cnt[i][k] * cnt[k][j];
        } else if (d[i][j] == d[i][k] + d[k][j]) {
          cnt[i][j] += cnt[i][k] * cnt[k][j];
        }
      }
    }
  }
  return 0;
}
