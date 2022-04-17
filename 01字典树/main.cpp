//
//  main.cpp
//  01字典树
//
//  Created by LiZnB on 2021/7/22.
//
// 题目http://codeforces.com/contest/665/problem/E

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>
#include <assert.h>
#pragma-GCC-optimize("-Ofast");

using namespace std;

const int N = 1e6 + 10;
long long val[N], k;

struct Trie {
    int ch[N * 30][2];
    int cnt[N * 30];
    int sz;
    
    void Init() { // 这里写的不好，trie树不要初值为0，最好是-1
        memset(ch, 0, sizeof(ch));
        memset(cnt, 0, sizeof(cnt));
        sz = 0;// 这里最好从1开始
    }
    void insert(string s) {
        int p = 0, len = s.length();
        for (int i = 0; i < len; i++) {
            assert(s[i] == '0' || s[i] == '1');
            if (!ch[p][s[i] - '0'])
                ch[p][s[i] - '0'] = ++sz;
            assert(sz < N * 30);
            assert(p < N * 30);
            p = ch[p][s[i] - '0'];
            cnt[p]++;
        }
    }
    
    long long find(string bk, string k) {
        int p = 0, len = bk.length(); // len = 30
        long long ans = 0ll;
        for (int i = 0; i < len; i++) {
            if (ch[p][(bk[i] - '0') ^ 1] && k[i] == '0') {
                ans += cnt[ch[p][(bk[i] - '0') ^ 1]];
            }
            p = ch[p][bk[i] - '0'];
            if (!p) break;
        }
        if (p) ans += cnt[p];
        return ans;
    }
    
} T;


string ltos(long long n) {
    long long val = n;
    string s;
    for (int i = 0; i <= 30; i++) {
        if (val & (1 << i)) s += '1';
        else s += '0';
    }
    reverse(s.begin(), s.end());
    return s;
}


int main() {
//    freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    int n;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    long long sum = 0ll, ans = 0ll;
    
    
    T.Init();
    T.insert(ltos(0ll));
    for (int i = 1; i <= n; i++) {
        sum ^= val[i];
        ans += T.find(ltos(sum ^ k), ltos(k));
        T.insert(ltos(sum));
    }
    cout << ans;
    return 0;
}

// 一般字典树
//const int N = 20 * 1000 + 10; // 结点总数最大值
//const int M = 300; // 字符集的宽度
//
//struct Trie {
//    int child[N][M];
//    int cnt[N];
//    int sz;
//
//    Trie() {
//        memset(child, 0, sizeof(child));
//        memset(cnt, 0, sizeof(cnt));
//        sz = 1; // 默认有一个根结点
//    }
//
//    void insert(string s) {
//        int p = 0; // 根结点
//        int len = s.length();
//        for (int i = 0; i < len; i++) {
//            if (child[p][s[i]] == 0) child[p][s[i]] = sz++; // 没有这条边就加上。
//            p = child[p][s[i]];
//            cnt[p]++; // cnt里存的是结点p的上一条边的字符数量
//        }
//    }
//
//    void find(string s) {
//        int p = 0;
//        int len = s.length();
//        for (int i = 0; i < len; i++) {
//            cout << s[i];
//            p = child[p][s[i]]; // 移动 P
//            if (cnt[p] == 1) break;
//        }
//        cout << endl;
//    }
//
//} Tr;
