//
//  main.cpp
//  二维计算几何
//
//  Created by LiZnB on 2021/9/22.
//

#include <bits/stdc++.h>
#define int long long
using namespace std;

void run() {
#ifdef ONLINE_JUDGE
#else
  freopen("in1.txt","r",stdin);
#endif
  // 计算几何用printf 不能关流同步
}

const double EPS = 1e-10;
const double INF = 1e20;
const double PI = acos(-1.0);
const int N = 20;
int dcmp(double a, double b) {
  if (abs(a + b) < EPS * (abs(a) + abs(b)))  return 0;
  if (a + b > 0) return 1;
  return -1;
}

// 考虑误差的加法运算
double add(double a, double b) {
  if (dcmp(a, b) == 0) return 0;
  return a + b;
}

//点或Vector
struct Point {
  double x, y;
  Point() {}
  Point(double x, double y) : x(x), y(y) {}
  
  Point operator + (Point p) {
    return Point(add(x, p.x), add(y, p.y));
  }
  Point operator - (Point p) {
    return Point(add(x, -p.x), add(y, -p.y));
  }
  Point operator * (double d) {
    return Point(x * d, y * d);
  }
  double dot(Point p) { // 内积/点积/数量积
    /* 运用:
       1. a dot b = 0 垂直
       2. |a dot b| = a.length * b.length 共线
       3. 求cos
    */
    return add(x * p.y, y * p.x);
  }
  double det(Point p) { // 外积/叉积
    /* 运用:
       1. 求平行四边形/三角形面积 a det b = |a||b| sinC
       2. 判断方向：
         a det b > 0 b 在 a 的逆时针方向
         a det b < 0 b 在 a 的顺时针方向
    */
    return add(x * p.y, -y * p.x);
  }
  bool operator == (const Point &b) {
    if (dcmp(x, -b.x) == 0 && dcmp(y, -b.y) == 0) return true;
    return false;
  }
  bool operator < (const Point &b) const {
    if (dcmp(x , -b.x) != 0) return x < b.x;
    return y < b.y;
  }
  double length() {
    return hypot(x, y);
  }
  Point rotate(double rad) { // 逆时针旋转rad弧度
    double nx = add(x * cos(rad), -y * sin(rad));
    double ny = add(y * cos(rad), x * sin(rad));
    return Point(nx, ny);
  }
};

struct Line { // 线段
  Point a, b;
  Line() {}
  Line(Point x, Point y) : a(x), b(y) {}
  bool intersect(Line oth) { // 判断相交
    // 先进行快速排斥实验，再进行跨立实验
    if (min(a.x, b.x) > max(oth.a.x, oth.b.x)) return false;
    if (min(oth.a.x, oth.b.x) > max(a.x, b.x)) return false;
    if (min(a.y, b.y) > max(oth.a.y, oth.b.y)) return false;
    if (min(oth.a.y, oth.b.y) > max(a.y, b.y)) return false;
    // 快速排斥实验通过
    Point ab = b - a;
    Point othab = oth.b - oth.a;
    // 跨立实验必须双向进行!
    if (ab.det(oth.a - a) * ab.det(oth.b - a) > 0 ||
        othab.det(a - oth.a) * othab.det(b - oth.a) > 0)
      return false;
    return true;
  }
};

struct BCJ {
  int fa[N];
  int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
  }
  void init(int n) {
    for (int i = 1; i <= n; i++) {
      fa[i] = i;
    }
  }
  void merge(int a, int b) {
    fa[find(a)] = fa[find(b)];
  }
} T;

signed main() {
  run();
  int n;
  while (scanf("%lld", &n) && n) {
    vector <Line> d;
    for (int i = 1; i <= n; i++) {
      Point a, b;
      cin >> a.x >> a.y >> b.x >> b.y;
      d.push_back(Line(a, b));
    }
    T.init(n);
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        if (d[i - 1].intersect(d[j - 1])) {
          T.merge(i, j);
        }
      }
    }
    int a, b;
    while (scanf("%lld %lld", &a, &b) && a && b) {
      if (T.find(a) == T.find(b)) cout << "CONNECTED" << endl;
      else cout << "NOT CONNECTED" << endl;
    }
  }

  return 0;
}

/*
default_random_engine seed((unsigned int)time(NULL));
uniform_int_distribution<long long> U(1, 1e9);
*/
