//
//  main.cpp
//  Lucas定理
//
//  Created by LiZnB on 2021/8/11.
//
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;

int power(int a, int b, int MOD) {
    int base = a, res = 1ll;
    while (b) {
        if (b & 1) {
            res = res * base % MOD;
        }
        base = base * base % MOD;
        b >>= 1ll;
    }
    return res;
}

int fac[N];

int C(int n, int m, int p) {
    if (m > n) return 0; // 注意m可以大于n
    return fac[n] * power(fac[m], p - 2, p) % p * power(fac[n - m], p - 2, p) % p;
}

int lucas(int n, int m, int p) {
    if (m == 0) return 1ll;
    return lucas(n / p, m / p, p) * C(n % p, m % p, p) % p;
}


signed main() {
  //  freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);

    int z;
    cin >> z;
  
 
    while (z--) {
        int n, m, p;
        cin >> n >> m >> p;

        fac[0] = 1ll;
        for (int i = 1; i < p; i++) {
            fac[i] = fac[i - 1] * i % p;
        }

        cout << lucas(m, n, p) << endl;
    }

    return 0;
}
