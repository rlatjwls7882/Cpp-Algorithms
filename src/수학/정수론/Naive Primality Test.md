## Naive Primality Test (소수 판정)
2부터 √N까지 약수가 있는지 확인하여 N이 소수인지 판별하는 알고리즘

시간복잡도 : O(√N)

prof. √N보다 큰 N의 약수 i가 존재하면 √N보다 작은 약수인 N/i로 커버가 된다.

[연습 문제 (백준 4134번)](https://www.acmicpc.net/problem/4134)

``` c++
/** http://boj.kr/e6e9596f6b374347ab2a132fb828e8c0 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

bool isPrime(ll n) {
    if(n<=1) return false; // n이 1 이하면 소수가 아님
    for(ll i=2;i*i<=n;i++) { // 2 이상 sqrt(n) 이하의 수 중 n의 약수가 있으면 n은 소수가 아님
        if(n%i==0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        ll n; cin >> n;
        while(true) {
            if(isPrime(n)) {
                cout << n << '\n';
                break;
            }
            n++;
        }
    }
}
```
