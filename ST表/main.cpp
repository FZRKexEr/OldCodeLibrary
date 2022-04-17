//
//  main.cpp
//  ST表
//
//  Created by LiZnB on 2020/12/5.
//

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
const int N = 1e6 + 10;


struct ST_table {
    int st[N][25];
    int Log[N];
    
    void Init(int n) {
        Log[1] = 0; // 以2为底
        for (int i = 2; i <= n; i++) {
            Log[i] = Log[i / 2] + 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; (1 << j) <= i; j++) {
                st[i][j] = max(st[i][j - 1], st[i - (1 << (j - 1))][j - 1]);
            }
        }
    }

    void build(int n) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &st[i][0]);
        }
        Init(n);
    }
    
    int query(int l, int r) {
        int len = Log[r - l + 1];
        int ans = max(st[r][len], st[l + (1 << len) - 1][len]);
        return ans;
    }
} T;


int main() {
    int n, m;
    int l, r;
    scanf("%d %d", &n, &m);
    T.build(n);
    
    
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &l, &r);
        
        printf("%d\n", T.query(l, r));
    }
    
    return 0;
}
