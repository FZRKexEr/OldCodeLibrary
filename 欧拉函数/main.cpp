//
//  main.cpp
//  欧拉函数
//
//  Created by LiZnB on 2021/7/17.
//

#include <iostream>
#include <cmath>
using namespace std;
// 欧拉函数phi(i): 1 - n 中与 n 互质的数的个数

// 欧拉筛
const int N = 1e6;
int prime[N], phi[N], prinum[N];
void Phi(int n) {
    for (int i = 1; i <= n; i++) {
        prime[i] = 0;
    }
    phi[1] = 1;
    int tot = 0;
    for (int i = 2; i <= n; i++) {
        if (prime[i] == 0) prinum[++tot] = i, phi[i] = i - 1;
        for (int j = 1; j <= tot; j++) {
            if (prinum[j] * i > n) break;
            prime[prinum[j] * i] = 1;
            if ((i % prinum[j]) != 0) phi[prinum[j] * i] = (prinum[j] - 1) * phi[i];
            if ((i % prinum[j]) == 0){
                phi[prinum[j] * i] = phi[i] * prinum[j];
                break;
            }
        }
    }
}

// 求1-n的phi
// 原理：基于筛法。
void phi_table(int n, int *phi) {
    for (int i = 2; i <= n; i++) phi[i] = 0;
    phi[1] = 1; //
    for (int i = 2; i <= n; i++) {
        if (phi[i]) continue; // 是个合数
        for (int j = i; j <= n; j += i) {
            if (!phi[j]) phi[j] = j; // 初始化合数
            phi[j] = phi[j] / i * (i - 1);
        }
    }
}

// 求单点phi 复杂度 O(sqrt(n))
// 原理：基于质因数分解，分解质因子的同时顺便套一下公式
int phi(int n) {
    int ans = n; // 公式 phi(n) = n * (1 - (1 / p)) * ...
    int limit = sqrt(n); // 最多只有1个质数大于sqrt(n)
    for (int i = 2; i <= limit; i++) {
        if (n % i == 0) {
            ans = ans / i * (i - 1); // 先除法再乘法防止整数溢出
            while (n % i == 0) n /= i; // 筛法
        }
    }
    if (n > 1) ans = ans / n * (n - 1); // 这是一个大于sqrt(n)的质数
    return ans;
}

int a[(int)(1e6) + 10];

int main() {
    phi_table(1000, a);
    printf("%d", phi(1e6));
    for (int i = 1; i <= 50; i++) {
        printf("%d %d\n", a[i], phi(i));
    }
    return 0;
}
