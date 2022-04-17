//
//  main.cpp
//  AC自动机
//
//  Created by LiZnB on 2020/12/1.
//
// 模板题 洛谷P5357 【模板】AC自动机（二次加强版）

#include <iostream>
#include <cstring>
#include <map>
#include <queue>
using namespace std;
const int N = 2e6 + 10;

struct AC_auto {
    int ch[N][26], cnt[N], fail[N];
    int ans[N], last[N], ord[N];
    int size;
 
    void Init() {
        memset(ch[0], -1, sizeof(ch[0]));
        memset(cnt, 0, sizeof(cnt));
        memset(fail, 0, sizeof(fail));
        memset(ans, 0, sizeof(ans));
        memset(last, 0, sizeof(last));
        memset(ord, 0, sizeof(ord));
        size = 1;
    }
 
    inline int id(char c) { // ID函数需要单独修改,默认是'a' ~ 'z'
        return c - 'a';
    }
    void insert(char *s, int o) {
        int pos = 0, len = (int)strlen(s + 1);
        for (int i = 1; i <= len; i++) {
            if (ch[pos][id(s[i])] == -1) {
                memset(ch[size], -1, sizeof(ch[size]));
                ch[pos][id(s[i])] = size++;
            }
            pos = ch[pos][id(s[i])];
        }
        cnt[pos]++;
        ord[pos] = o;
    }
 
    void built() {
        queue <int> que;
        for (int i = 0; i <= 25; i++) {
            if (ch[0][i] == -1) {
                ch[0][i] = 0;
            } else {
                que.push(ch[0][i]);
            }
        }
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (int i = 0; i <= 25; i++) {
                if (ch[x][i] == -1) ch[x][i] = ch[fail[x]][i];
                else {
                    int goal = fail[x];
                    while (goal && ch[goal][i] == -1) goal = fail[goal];
                    fail[ch[x][i]] = ch[goal][i];
                    last[ch[x][i]] = cnt[ch[goal][i]] ? ch[goal][i] : last[ch[goal][i]];
                    que.push(ch[x][i]);
                }
            }
        }
    }
 
    void solve(char *s) {
        memset(ans, 0, sizeof(ans));
        int pos = 0, len = (int)strlen(s + 1);
        for (int i = 1; i <= len; i++) {
            pos = ch[pos][id(s[i])];
            int t = pos;
            while (t) {
                ans[ord[t]]++;
                t = last[t];
            }
        }
    }
} AC;

char in[N];
string s;
map <string, int> occur; // 注意map判重
int order[N];

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    
    int n;
    AC.Init();
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        if (occur[s] == 0) {
            occur[s] = i;
            long long len = s.length();
            for (int j = 0; j < len; j++) {
                in[j + 1] = s[j];
            }
            in[len + 1] = '\0';
            AC.insert(in, i);
            order[i] = i;
        } else {
            order[i] = occur[s];
        }
    }
    AC.built();
    cin >> (in + 1);
    AC.solve(in);
    for (int i = 1; i <= n; i++) {
        cout << AC.ans[order[i]] << endl;
    }
    
    return 0;
}
