/** https://www.acmicpc.net/problem/17386 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct line {
    ll x1, y1, x2, y2;
};

struct vec {
    ll x, y;
};

bool isInterSect(line a, line b) {
    vec vector1 = {a.x2-a.x1, a.y2-a.y1};
    vec vector2 = {b.x1-a.x2, b.y1-a.y2};
    vec vector3 = {b.x2-a.x2, b.y2-a.y2};

    ll ret1 = vector1.x*vector2.y - vector2.x*vector1.y;
    ll ret2 = vector1.x*vector3.y - vector3.x*vector1.y;
    return ret1<0 && ret2>0 || ret1>0 && ret2<0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    line a, b; cin >> a.x1 >> a.y1 >> a.x2 >> a.y2 >> b.x1 >> b.y1 >> b.x2 >> b.y2;
    cout << (isInterSect(a, b) && isInterSect(b, a));
}
