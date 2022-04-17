//
//  main.cpp
//  矩阵快速幂
//
//  Created by LiZnB on 2020/11/28.
//

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 1e5 + 2;
const int MOD = 998244353;

struct Matrix {
    int matrix[N][N];
    int n, m;
    Matrix () { memset(matrix, 0, sizeof(matrix)); n = m = 0;}
    Matrix Init() {
        Matrix c;
        c.n = c.m = m;
        for (int i = 1; i <= n; i++) c.matrix[i][i] = 1;
        return c;
    }
    Matrix operator * (const Matrix & oth) {
        Matrix c;
        c.n = n;
        c.m = oth.m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= oth.m; j++) {
                for (int k = 1; k <= m; k++) {
                    (c.matrix[i][j] += (1ll * matrix[i][k] * oth.matrix[k][j]) % MOD) %= MOD;
                }
            }
        }
        return c;
    }
    Matrix operator + (const Matrix & oth) {
        Matrix c;
        c.n = n;
        c.m = m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                c.matrix[i][j] = (1ll * matrix[i][j] + oth.matrix[i][j]) % MOD;
            }
        }
        return c;
    }
    void out() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }
};

Matrix power(Matrix x, long long k) {
    Matrix base, ans;
    ans = x.Init();
    base = x;
    while (k) {
        if (k & 1ll) {
            ans = ans * base;
        }
        k >>= 1ll;
        base = base * base;
    }
    return ans;
}

int main() {
    
    return 0;
}
