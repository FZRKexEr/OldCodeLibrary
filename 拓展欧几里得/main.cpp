//
//  main.cpp
//  拓展欧几里得
//
//  Created by LiZnB on 2021/7/16.
//

#include <iostream>
using namespace std;
void exgcd(int a, int b, int &d, int &x, int &y) {
    if (!b) {
        d = a; x = 1; y = 0;
    } else {
        exgcd(b, a % b, d, y, x); y -= x * (a / b); // 注意括号！
    }
}
 
int main() {
    int a = 6, b = 15, gcd, x, y, c = 9;
    exgcd(a, b, gcd, x, y);
   
    x += (b / gcd);
    y -= (a / gcd); //这里依然是 ax + by = gcd
    
    x = c / gcd * x;
    y = c / gcd * y; // 这里是 ax + by = c
    
    cout << gcd << endl;
    cout << x << endl;
    cout << y << endl;
    
    
    return 0;
}
