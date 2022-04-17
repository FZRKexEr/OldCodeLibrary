//
//  main.cpp
//  Manacher
//
//  Created by LiZnB on 2021/8/8.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <map>
#include <ctime>
#include <random>
#include <stack>
#include <queue>
#include <vector>

using namespace std;
const int N = 2e7 + 10;

string ma;
int mp[N * 2];

int Manacher(string &s) {
    int slen = s.length();
    ma += "$#";

    for (int i = 0; i < slen; i++) {
        ma += s[i];
        ma += '#';
    }
    ma += '^';
    int mlen = ma.length();
    
    int mx = 0, id = 0;
    mp[0] = 0;
    for (int i = 1; i < mlen; i++) {
        if (i <= mx) {
            mp[i] = min(mx - i, mp[2 * id - i]);
        } else mp[i] = 0;
        while (ma[i + mp[i] + 1] == ma[i - mp[i] - 1]) mp[i]++;
        if (i + mp[i] > mx) {
            mx = i + mp[i];
            id = i;
        }
    }
    int ans = 0;
    for (int i = 0; i < mlen; i++) {
        if (mp[i] > ans) ans = mp[i];
    }
    return ans;
}

int main() {
   // freopen("in.txt","r",stdin);
    
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    string s;
    cin >> s;

    cout << Manacher(s);
    
    
    return 0;
}
