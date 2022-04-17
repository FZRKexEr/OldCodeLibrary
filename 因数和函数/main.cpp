//
//  main.cpp
//  因数和函数
//
//  Created by LiZnB on 2021/7/19.
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N = 1e6 + 10;

long long sigma1[N];

long long power(long long a, long long b) {
    long long base = a, ans = 1ll;
    while(b) {
        if (b & 1) {
            ans *= base;
        }
        base *= base;
        b >>= 1;
    }
    return ans;
}

void Sigma1(int n, int *pri) {
    for (int i = 1; i <= n; i++) pri[i] = 0, sigma1[i] = 1ll;
    for (int i = 2; i <= n; i++) {
        if (pri[i]) continue;
        sigma1[i] = 1ll + i;
        for (int j = i * 2; j <= n; j += i) {
            int cnt = 0, val = j;
            while (val % i == 0) {
                cnt++; // k
                val /= i;
            }
            pri[j] = 1;//用快速幂！！！
            sigma1[j] *= 1ll * (power(i, cnt + 1) - 1) / (i - 1); // (p ^ {k + 1} - 1) / (p - 1)
            assert(sigma1[j] > 0);
        }
    }
}

int pri[N];
int main() {
    int n = 100;
    Sigma1(n, pri);
    
    for (int i = 1; i <= n; i++) {
        cout << sigma1[i] << endl;
    }
    return 0;
}
