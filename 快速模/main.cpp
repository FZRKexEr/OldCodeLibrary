//
//  main.cpp
//  快速模
//
//  Created by LiZnB on 2021/9/12.
//

#include <iostream>

/* 似乎更快？
 ll mul (ll a , ll b , ll p) //a*b%p
 {
    
     ll s = a * b - (ll)((long double) a * b / p +0.5) * p;
     return s < 0 ? s + p : s;
 }
 */

ll mul(ll a, ll b, ll c) {
    a %= c, b %= c;
    return ((a * b - (ll)((long double)a / c * b + 1e-8) * c) % c + c) % c;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
