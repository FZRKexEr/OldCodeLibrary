//
//  main.cpp
//  二维ST表
//
//  Created by LiZnB on 2020/12/17.
//

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;
const int N = 300;
const int INF = 0x3f3f3f3f;

struct ST {
    int f[N][N][20][2]; // 0 min 1 max
    int Log[266];
        
    void Init(int n) {
        Log[1] = 0;
        for (int i = 2; i <= 255; i++) {
            Log[i] = Log[i / 2] + 1;
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; (1 << k) <= min(i, j); k++) {
                    f[i][j][k][1] = -INF;
                    f[i][j][k][0] = INF;
                
                    f[i][j][k][1] = max(f[i][j][k][1], f[i - (1 << (k - 1))][j - (1 << (k - 1))][k - 1][1]);
                    f[i][j][k][1] = max(f[i][j][k][1], f[i - (1 << (k - 1))][j][k - 1][1]);
                    f[i][j][k][1] = max(f[i][j][k][1], f[i][j - (1 << (k - 1))][k - 1][1]);
                    f[i][j][k][1] = max(f[i][j][k][1], f[i][j][k - 1][1]);
                    
                    f[i][j][k][0] = min(f[i][j][k][0], f[i - (1 << (k - 1))][j - (1 << (k - 1))][k - 1][0]);
                    f[i][j][k][0] = min(f[i][j][k][0], f[i - (1 << (k - 1))][j][k - 1][0]);
                    f[i][j][k][0] = min(f[i][j][k][0], f[i][j - (1 << (k - 1))][k - 1][0]);
                    f[i][j][k][0] = min(f[i][j][k][0], f[i][j][k - 1][0]);
                }
            }
        }
    }

    int Query(int x1, int y1, int x2, int y2) {
        int len = Log[x2 - x1 + 1];
        int minn = INF, maxn = -INF;
       
        minn = min(minn, f[x2][y2][len][0]);
        minn = min(minn, f[x1 + (1 << len) - 1][y1 + (1 << len) - 1][len][0]);
        minn = min(minn, f[x2][y1 + (1 << len) - 1][len][0]);
        minn = min(minn, f[x1 + (1 << len) - 1][y2][len][0]);
        
        maxn = max(maxn, f[x2][y2][len][1]);
        maxn = max(maxn, f[x1 + (1 << len) - 1][y1 + (1 << len) - 1][len][1]);
        maxn = max(maxn, f[x2][y1 + (1 << len) - 1][len][1]);
        maxn = max(maxn, f[x1 + (1 << len) - 1][y2][len][1]);

        return maxn - minn;
    }
    
} T;


int main() {
    int n, b, k, val;
    scanf("%d %d %d", &n, &b, &k);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &val);
            T.f[i][j][0][0] = val;
            T.f[i][j][0][1] = val;
        }
    }
    
    T.Init(n);
    
    int x, y;
    for (int i = 1; i <= k; i++) {
        scanf("%d %d", &x, &y);
        printf("%d\n", T.Query(x, y, x + b - 1, y + b - 1));
    }
    return 0;
}
