//
//  main.cpp
//  SOSDP
//
//  Created by LiZnB on 2021/8/28.
//
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10;
int a[N], val[N];
int s[N][22];
signed main() {
    freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    int z;
    cin >> z;
    while (z--) {
        memset(a, 0, sizeof(a));
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> val[i];
            a[val[i]]++;
        }
        // s[i][j] 表示只和i的前j位不同的子集的权值和, base 0
        for (int i = 1; i <= 1e6; i++) {
            s[i][0] = a[i];
            if (i & 1) s[i][0] += a[i - 1];
            for (int j = 1; j <= 21; j++) { // 注意必须跑满
                s[i][j] = 0;
                s[i][j] += s[i][j - 1];
                if (i & (1 << j)) {
                    s[i][j] += s[i ^ (1 << j)][j - 1];
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int j;
            for (j = 1; (1 << j) <= val[i]; j++);
            ans += s[val[i]][j - 1]; // 注意减j - 1
        }
        cout << ans << endl;
    }
    return 0;
}
