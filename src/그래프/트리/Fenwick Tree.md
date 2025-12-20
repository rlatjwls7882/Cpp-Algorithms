# Fenwick Tree (Binary Indexed Tree) 🟢 Platinum V
배열에 누적합을 겹치는 구간 단위로 저장해 구간 합 쿼리를 빠르게 해결하는 자료구조

시간복잡도 : O(logN)

![](https://github.com/user-attachments/assets/cba8d242-51da-4ae9-9082-a67df94f94a5)

각 배열의 공간을

arr[1]은 1 ~ 1의 누적합,  
arr[2]는 1 ~ 2의 누적합,  
arr[3]은 3 ~ 3의 누적합,  
arr[4]는 1 ~ 4의 누적합,  
...

이런 식으로 설정해 놓습니다.

![](https://github.com/user-attachments/assets/e0d6e89f-6bb6-4767-86dc-7c98a180b691)

이런 식으로 설정하면 1번 원소를 변경하면 그에 따라 영향을 받는 곳은 arr[1], arr[2], arr[4], arr[8], ... 입니다.  
각 공간의 크기를 2의 제곱수로 설정했으니 총 logN개만큼 업데이트가 됩니다.

![](https://github.com/user-attachments/assets/ba9ae73a-0491-4c29-a1c0-7f461f6201d0)

구간 쿼리에서도 1 ~ 5의 누적합을 계산할 때도 arr[5]와 arr[4]만 더해 최대 logN개만큼만 더하면 됩니다.

이 때 움직이는 거리는 원소를 변경할 때는 i&-i 만큼 오른쪽으로(i+=i&-i), 누적합을 계산할 때는 i&-i만큼 왼쪽으로(i-=i&-i) 이동하면 됩니다.

[연습 문제 (백준 2042번)](https://www.acmicpc.net/problem/2042)

``` c++
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX = 1'000'001;

ll arr[MAX], a[MAX];

void update(int i, ll val) {
    val-=a[i];
    a[i]+=val;
    while(i<MAX) {
        arr[i]+=val;
        i+=i&-i;
    }
}

ll query(int i) {
    ll ret=0;
    while(i) {
        ret+=arr[i];
        i-=i&-i;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    for(int i=1;i<=n;i++) {
        ll val; cin >> val;
        update(i, val);
    }

    for(int i=0;i<m+k;i++) {
        ll a, b, c; cin >> a >> b >> c;
        if(a==1) update(b, c);
        else cout << query(c)-query(b-1) << '\n';
    }
}
```
