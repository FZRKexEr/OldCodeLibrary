//
//  main.cpp
//  大质因数探测PR算法
//
//  Created by LiZnB on 2021/11/20.
//

#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace NT {
  int mul(int a, int b, int m) {
    int s = a * b - (long long) ((long double)a * b / m + 0.5) * m;
    return s < 0 ? s + m : s;
  }
  int fpow(int x, int a, int m) {
    int ans = 1;
    while (a) {
      if (a & 1) ans = mul(ans, x, m);
      x = mul(x, x, m), a >>= 1;
    }
    return ans;
  }
}
namespace Miller_Rabin {
  using namespace NT;
  int p[15] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  int detect(int n, int a) {
      if (n == a) return 1;
      if (a % n == 0) return 1;
      int now = n - 1, lst = 1;
      if (fpow(a, now, n) != 1)
        return 0;
      while (!(now & 1)) {
        now /= 2;
        int p = fpow(a, now, n);
        if (lst == 1 && p != 1 && p != n - 1)
          return 0;
        lst = p;
      }
      return 1;
  }

  int MR(int n) {
    if (n < 2) return 0;
    for (int i = 0; i < 7; i++) {
      if (!detect(n, p[i]))
        return 0;
    }
    return 1;
  }
}

namespace Pollard_Rho {
  default_random_engine seed((unsigned int)time(NULL));
  using namespace NT;
  using namespace Miller_Rabin;
  int f(int x, int c, int p) {
    return (mul(x, x, p) + c) % p;
  }

  int PR(int n) {
    uniform_int_distribution<long long> U(1, n);
    if (n == 4) return 2;
    if (MR(n)) return n;
    while (1) {
      int C = U(seed);
      int s = 0, t = 0;
      int acc = 1;
      do {
        for (int i = 1; i <= 128; i++) {
          t = f(f(t, C, n), C, n);
          s = f(s, C, n);
          int tmp = mul(acc, abs(t - s), n);
          if (s == t || tmp == 0)
            break;
          acc = tmp;
        }
        int d = gcd(n, acc);
        if (d > 1) return d;
      } while (s != t);
    }
  }
  typedef pair<int, int> pii;
  // first 存的是质数 second 存的是质数的个数
  vector <pii> DCOMP(int n) {
    vector <pii> ret;
    while (n != 1) {
      int p = PR(n);
      while (!MR(p))
        p = PR(p);
      int c = 0;
      while (n % p == 0) n /= p, ++c;
      ret.push_back(make_pair(p, c));
    }
    return ret;
  }
}
signed main() {
  int t, n; cin >> t;
  while (t--) {
    cin >> n;
    auto ans = Pollard_Rho::DCOMP(n);
    sort(ans.begin(), ans.end());
    int c = 0;
    for (auto i : ans) {
      c += i.second;
    }
    cout << c << " ";
    for (auto i : ans) {
      while (i.second--) cout << i.first << " ";
    }
    cout << endl;
  }
  return 0;
}
