# Fenwick Tree (Binary Indexed Tree) 🟢 Platinum V
배열의 누적합을 부분 구간 합 형태로 저장하여 구간 합과 업데이트를 $O(\log N)$에 처리하는 자료구조

시간복잡도: $O(\log N)$

![](https://github.com/user-attachments/assets/7ae7447c-2f06-4e8d-bdc3-71cb9492168f)

Fenwick Tree에서는 배열의 각 인덱스가 특정 구간의 누적합을 저장한다. 각 인덱스 $i$는 다음 구간의 합을 저장한다.

```math
arr_i = \sum_{j=i-(i\&-i)+1}^{i} a_j
```

예를 들어 다음과 같이 구간이 구성된다.

$$
\begin{aligned}
arr_1 &: [1,1] \\
arr_2 &: [1,2] \\
arr_3 &: [3,3] \\
arr_4 &: [1,4] \\
\cdots
\end{aligned}
$$

이처럼 길이가 $2^k$인 구간의 합을 저장하며, 이러한 구간들이 겹쳐 전체 prefix sum을 구성한다.

![](https://github.com/user-attachments/assets/1e0261bf-f88a-4c83-8a0c-112f21383879)

이 구조에서 어떤 원소가 변경되면 그 값을 포함하는 모든 구간을 업데이트해야 한다. 예를 들어 1번 원소가 변경되면 $arr_1, arr_2, arr_4, arr_8, \dots$ 와 같이 해당 값을 포함하는 구간들이 영향을 받는다. 각 구간의 길이가 $2$의 거듭제곱 단위로 확장되기 때문에 업데이트는 최대 $\log N$번만 수행하면 된다.

![](https://github.com/user-attachments/assets/c43f2059-8ab8-4c4d-864c-7c862df02ace)

구간 합을 구할 때도 같은 방식으로 계산한다. 예를 들어 구간 $[1,5]$의 누적합을 구하려면 $arr_5 + arr_4$를 계산하면 된다. 이렇게 필요한 구간만 더하면 되므로 최대 $\log N$번의 연산으로 누적합을 계산할 수 있다.

이때 이동하는 간격은 `i \& -i`로 계산할 수 있다. 원소를 업데이트할 때는 다음 구간으로 이동하기 위해 `i += i & -i`를 사용하고, 누적합을 계산할 때는 이전 구간으로 이동하기 위해 `i -= i & -i`를 사용한다.

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
