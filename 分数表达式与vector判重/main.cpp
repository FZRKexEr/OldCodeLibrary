#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <unordered_map>
#include <cassert>


using namespace std;
const int N = 2010;
struct Node {
    int x, y;
} P[N], A[N];

struct Frac {
    int x, y;
    // (y / x)
    /*
     1. 对斜率的保存很友好，可以处理斜率为0，斜率不存在的情况
     2. 可以求出与这一斜率垂直的斜率，包括斜率为0，和斜率不存在
     3. 可以自动读入两点，求斜率，无需再次特判
     4. 支持判重，不支持比较分数大小
     */

    long long gcd(long long a, long long b) {
        if (!b) return a;
        return gcd(b, a % b);
    }

    void calc() { // 规范分数表达式
        if (x == 0) {y = 1; return;}
        if (y == 0) {x = 1; return;}

        long long GCD = gcd(x, y);
        x /= GCD;
        y /= GCD;
        if (x < 0) y *= -1, x *= -1;
    }

    void in(Node a, Node b) { // 从node输入斜率
        x = a.x - b.x;
        y = a.y - b.y;
        calc();
    }

    Frac vertical() { // 求垂直的斜率
        Frac res = (Frac) {y, -1 * x};
        res.calc();
        return res;
    }

    bool operator < (const Frac & oth) const { // 只能用于判重（判重只能这样判！），不能比较分数大小
        if (x != oth.x) return x < oth.x;
        return y < oth.y;
    }
    
    bool operator == (const Frac & oth) const {
        if (x == oth.x && y == oth.y) return true;
        return false;
    }
};

struct Line {
    Frac k; // 斜率，判断相交
    int a, b, c; // 一般式，用于判重

    long long gcd(long long a, long long b) {
        if (!b) return a;
        return gcd(b, a % b);
    }

    void in(Node u, Node v) {
        k.in(u, v);
        a = -k.y;
        b = k.x;
        c = -1 * a * u.x - b * u.y;
    }

    bool operator < (const Line & oth) const { // 判重
        if (a != oth.a) return a < oth.a;
        if (b != oth.b) return b < oth.b;
        return c < oth.c;
    }
};

vector<Frac> cntP[N], cntA; // 用vector+二分替代map判重，非常快

int main() {
//    freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> P[i].x >> P[i].y;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            Frac res;
            res.in(P[i], P[j]);
            cntP[i].push_back(res);
        }
        sort(cntP[i].begin(), cntP[i].end());
    }

    for (int i = 1; i <= q; i++) {
        cin >> A[i].x >> A[i].y;
        cntA.clear();
        for (int j = 1; j <= n; j++) {
            Frac res;
            res.in(A[i], P[j]);
            cntA.push_back(res);
        }
        long long res1 = 0ll, res2 = 0ll;
        sort(cntA.begin(), cntA.end());
        for (int j = 1; j <= n; j++) {
            Frac res;
            res.in(A[i], P[j]);
            res = res.vertical();

            res1 += upper_bound(cntA.begin(), cntA.end(), res) - lower_bound(cntA.begin(), cntA.end(), res);
            
            res2 += upper_bound(cntP[j].begin(), cntP[j].end(), res) - lower_bound(cntP[j].begin(), cntP[j].end(), res);
        }
        cout << res1 / 2 + res2 << endl;
    }
    return 0;
}
