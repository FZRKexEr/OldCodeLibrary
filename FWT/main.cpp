//
//  main.cpp
//  FWT
//
//  Created by LiZnB on 2021/9/1.
//

#include <bits/stdc++.h>
#define int long long
#define ONLINE_JUDGE
using namespace std;

void run() {
#ifdef ONLINE_JUDGE
#else
    freopen("in3.txt","r",stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
}

const int MOD = 998244353;
const int inv2 = (MOD + 1) >> 1;
struct FWT {
    /*  坑点说明：
        1. n 必须是2的倍数
        2. fwt只能求出 0 ~ n-1 的fwt，言外之意是如果要求 2^m 的fwt 需要把n设置成 2^(m+1)
        3. 不能擅自不取模，即使题目不要求取模，也要取模。如果非要不取模，需要用栈来存计算顺序，ufwt时，倒着做一遍。（取模会更慢）
        4. inv2 不要每次都算，这个非常耗时。
        5. FWT数组可能非常大（结果可能很小），所以不能以题目数据范围为准，一定要开long long
    */

    int power(int a, int b) {
        int base = a % MOD, res = 1ll;
        while (b) {
            if (b & 1) {
                res = base * res % MOD;
            }
            base *= base;
            base %= MOD;
            b >>= 1;
        }
        return res;
    }
    
    void fwtor(int *a, int n, int type) {
        for (int i = 0; i <= n; i++) assert(a[i] <= MOD);
        for (int i = 1; i < n; i <<= 1) {
            int sz = i << 1;
            for (int j = 0; j < n; j += sz) {
                for (int k = 0; k < i; k++) {
                    a[j + i + k] = (a[i + j + k] + MOD + a[j + k] * type) % MOD;
                }
            }
        }
    }

    void fwtand(int *a, int n, int type) {
        for (int i = 0; i <= n; i++) assert(a[i] <= MOD);
        for (int i = 1; i < n; i <<= 1) {
            int sz = i << 1;
            for (int j = 0; j < n; j += sz) {
                for (int k = 0; k < i; k++) {
                    if (j + k + i > n) break;
                    a[j + k] = (a[j + k] + MOD + a[j + k + i] * type) % MOD;
                }
            }
        }
    }

    void fwtxor(int *a, int n, int type) {
        for (int i = 0; i <= n; i++) {
            assert(a[i] <= MOD);
        }
        for (int i = 1; i < n; i <<= 1) {
            int sz = i << 1;
            for (int j = 0; j < n; j += sz) {
                for (int k = 0; k < i; k++) {
                    assert(i + j + k < n); // n设置成2的倍数了，一定满足
                    int x = a[j + k], y = a[i + j + k];
                    a[j + k] = (x + y) % MOD;
                    a[j + k + i] = (x - y + MOD) % MOD;
                    
                    if (type == -1) {
                        a[j + k] = a[j + k] * inv2 % MOD;
                        a[j + k + i] = a[j + k + i] * inv2 % MOD;
                    }
                }
            }
        }
    }
} T;
const int N = 1e6 + 10;
int a[N], b[N], c[N];

signed main() {
    run();
    int n;
    cin >> n;
    n = 1ll << n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] %= MOD;
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b[i] %= MOD;
    }
    T.fwtor(a, n - 1, 1);
    T.fwtor(b, n - 1, 1);
    for (int i = 0; i < n; i++) {
        c[i] = (a[i] * b[i]) % MOD;
    }
    T.fwtor(c, n - 1, -1);
    T.fwtor(a, n - 1, -1);
    T.fwtor(b, n - 1, -1);
    for (int i = 0; i < n; i++) {
        cout << c[i] << " ";
    }
    cout << endl;
    T.fwtand(a, n - 1, 1);
    T.fwtand(b, n - 1, 1);
    for (int i = 0; i < n; i++) {
        c[i] = (a[i] * b[i]) % MOD;
    }
    T.fwtand(c, n - 1, -1);
    T.fwtand(a, n - 1, -1);
    T.fwtand(b, n - 1, -1);
    for (int i = 0; i < n; i++) {
        cout << c[i] << " ";
    }
    cout << endl;
    T.fwtxor(a, n - 1, 1);
    T.fwtxor(b, n - 1, 1);
    for (int i = 0; i < n; i++) {
        c[i] = (a[i] * b[i]) % MOD;
    }
    T.fwtxor(c, n - 1, -1);
    for (int i = 0; i < n; i++) {
        cout << c[i] << " ";
    }
    cout << endl;
    return 0;
}

/*
default_random_engine seed((unsigned int)time(NULL));
uniform_int_distribution<long long> U(1, 1e9);
*/
