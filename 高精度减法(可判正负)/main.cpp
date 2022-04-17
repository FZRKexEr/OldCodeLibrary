//
//  main.cpp
//  高精度减法(可判正负)
//
//  Created by LiZnB on 2021/8/10.
//
#include <bits/stdc++.h>
#pragma-GCC-optimize("-Ofast");
#define int long long
//#define ONLINE_JUDGE
using namespace std;

void run() {
#ifdef ONLINE_JUDGE
#else
    freopen("in.txt","r",stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
}
const int N = 1e5 + 10;

struct Bignum { // 不要随便创建Bignum,一次就是O(N)
    int num[N], len;

    Bignum() {
        memset(num, 0, sizeof(num));
        len = 1;
    }

    void Init() {
        for (int i = 1; i <= len; i++) num[i] = 0;
        len = 1;
    }

    bool operator < (const Bignum & oth) {
        if (len < oth.len) return true;
        if (len > oth.len) return false;
        for (int i = len; i >= 1; i--) {
            if (num[i] < oth.num[i]) return true;
            if (num[i] > oth.num[i]) return false;
        }
        return false;
    }

    void operator = (const Bignum &oth) {
        len = oth.len;
        for (int i = 1; i <= len; i++) {
            num[i] = oth.num[i];
        }
    }

    Bignum operator - (const Bignum &oth) { // 只能 (大 - 小),答案可以是0
        int lend = 0;
        Bignum res;
        for (int i = 1; i <= len; i++) {
            if (num[i] - lend >= oth.num[i]) {
                res.num[i] = num[i] - lend - oth.num[i];
                lend = 0;
            } else {
                res.num[i] = num[i] - lend - oth.num[i] + 10;
                lend = 1;
            }
        }
        assert(!lend); // 如果RE,说明初始化没弄好
        res.len = len;
        for (int i = len; i >= 2; i--) {
            if (res.num[i] == 0) res.len--;
            else break;
        }
        return res;
    }

    void in(string &s) {
        len = s.length();
        for (int i = len - 1; i >= 0; i--) {
            num[len - i] = s[i] - '0';
        }
    }

    bool zero() {
        if (num[1] == 0 && len == 1) return true;
        return false;
    }

    void out() {
        for (int i = len; i >= 1; i--) {
            cout << num[i];
        }
        cout << endl;
    }

};

string num;

signed main() {
    run();
    Bignum a, b;
    cin >> num;
    a.in(num);
    cin >> num;
    b.in(num);
    if (a < b) {
        cout << "-";
        a = b - a;
        a.out();
    } else {
        a = a - b;
        a.out();
    }
    
    return 0;
}

/*
default_random_engine seed((unsigned int)time(NULL));
uniform_int_distribution<long long> U(1, 1e9);
*/
