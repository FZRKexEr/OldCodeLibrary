//
//  main.cpp
//  乘法逆元
//
//  Created by LiZnB on 2020/12/1.
//  洛谷P3811 【模板】乘法逆元


#include <cstdio>
#include <ctime>
using namespace std;
const int N = 4 * 1e6;
int MOD;
int inv[N];


// 常规的单次逆元, 时间复杂度O(nlog(n)), 本题会超时
long long Power(long long x, long long k) {
    long long ans = 1ll, base = x;
    while(k) {
        if (k & 1ll) {
            (ans *= base) %= MOD;
        }
        (base *= base) %= MOD;
        k >>= 1ll;
    }
    return ans;
}

int main() {

    int n;
    scanf("%d %d", &n, &MOD);
    inv[1] = 1;
    printf("%d\n", inv[1]);
    
    // 线性逆元，可以求1～MOD的逆元，时间复杂度O(n)
    for (int i = 2; i <= n; i++) {
        inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
        printf("%d\n", inv[i]);
    }
    
    return 0;
}
