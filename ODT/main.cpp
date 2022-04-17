//
//  main.cpp
//  ODT
//
//  Created by LiZnB on 2021/8/29.
//

#include <bits/stdc++.h>
#define int long long
using namespace std;
struct Node {
    int l, r;
    mutable int val;
    Node(const int &a, const int &b, const int &c) : l(a), r(b), val(c) {}
    bool operator < (const Node & oth) const {
        return l < oth.l;
    }
};

struct ODT {
    
    set<Node> odt;
    int n;

    auto split(int x) { // n 可以考虑去掉，让ODT可以处理大区间
        if (x > n) return odt.end();
        auto it = --odt.upper_bound((Node) {x, 0, 0});
        if (it->l == x) return it;
        int l = it->l, r = it -> r, val = it->val;
        odt.erase(it);
        odt.insert((Node) {l, x - 1, val});
        return odt.insert((Node) {x, r, val}).first;
    }

    void assign(int l, int r, int val) {
        auto itr = split(r + 1);  // 必须先右后左, 因为split右端点会让已经split的左端点失效
        auto itl = split(l);
        odt.erase(itl, itr);
        odt.insert((Node) {l, r, val});
    }
} T;

signed main() {
     
    return 0;
}
