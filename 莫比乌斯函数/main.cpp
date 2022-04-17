//
//  main.cpp
//  莫比乌斯函数
//
//  Created by LiZnB on 2021/7/18.
//
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;



const int N = 1e6 + 10;
int prinum[N], prime[N], tot;
// 线性筛
void mobius(int n, int *miu) {
    tot = 0;
    for (int i = 1; i <= n; i++) {
        prime[i] = 0;
        miu[i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        if (prime[i] == 0) {
            prinum[++tot] = i;
            miu[i] = -1;
        }
        for (int j = 1; j <= tot; j++) {
            if (prinum[j] * i > n) break;
            prime[prinum[j] * i] = 1;

            if (i % prinum[j] == 0) {
                miu[prinum[j] * i] = 0;
                break;
            } else {
                miu[prinum[j] * i] = -miu[i];
            }
        }
    }
}

int miu[N];
//
//void Mobius(int n, int *pri) {
//    for (int i = 1; i <= n; i++) pri[i] = 0, miu[i] = 1; // 0个质因数 miu = 1 （相当于(-1) ^ 0）
//    for (int i = 2; i <= n; i++) {
//        if (pri[i]) continue;
//        miu[i] = -1; // 质数miu = -1
//        for (int j = 2 * i; j <= n; j += i) {
//            pri[j] = 1;
//            if ((j / i) % i == 0) miu[j] = 0;
//            else miu[j] *= -1;
//        }
//    }
//}


int pri[1002];
int main() {
    //Mobius(1000, pri);
    mobius(1000, miu);
    for (int i = 1; i <= 50; i++)
        cout << miu[i] << "(" << i << ")" << endl;
    return 0;
}
