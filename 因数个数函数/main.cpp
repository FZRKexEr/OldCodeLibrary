//
//  main.cpp
//  因数个数函数
//
//  Created by LiZnB on 2021/7/19.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int N = 1e6 + 10;

int sigma0[N];

void Sigma0(int n, int *pri) {
    for (int i = 1; i <= n; i++) {
        pri[i] = 0;
        sigma0[i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        if (pri[i]) continue;
        for (int j = i; j <= n; j += i) {
            int cnt = 0, val = j;
            while (val % i == 0) {
                cnt++;
                val /= i;
            }
            sigma0[j] *= (cnt + 1); // sigma0(n) = (c1 + 1)(c2 + 1)...(ck + 1)
            if (j != i) pri[j] = 1;
        }
    }
}




int pri[N];
int main() {
    int n = 1000;
    Sigma0(n, pri);
    for (int i = 1; i <= n; i++) {
        cout << sigma0[i] << endl;
    }
    
    return 0;
}
