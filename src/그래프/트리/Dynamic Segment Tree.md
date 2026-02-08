# Dynamic Segment Tree 🟢 Platinum V
세그먼트 트리에서 각 노드를 필요한 부분만 동적으로 생성하는 알고리즘

시간복잡도 : $O(Q \logN)$ (Q : 쿼리의 수)

[연습문제 (백준 2042번)](https://www.acmicpc.net/problem/2042)

세그먼트 트리에서 공간을 4N 정도로 미리 잡아주는 것과 달리, 필요한 구간에 대한 노드만 동적으로 생성해 메모리를 최적화할 수 있다.

``` c++
/** http://boj.kr/0fad07836b8449568e728656d94e8c1f 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Node {
    int l=-1, r=-1;
    ll val=0;
};

vector<Node> arr(1);

void update(int nodeNum, int nodeL, int nodeR, int k, ll val) {
    if(nodeL==nodeR) {
        arr[nodeNum].val=val;
        return;
    }

    int mid=nodeL+nodeR>>1;
    if(k<=mid) {
        if(arr[nodeNum].l==-1) {
            arr[nodeNum].l=arr.size();
            arr.push_back({-1, -1, 0});
        }
        update(arr[nodeNum].l, nodeL, mid, k, val);
    } else {
        if(arr[nodeNum].r==-1) {
            arr[nodeNum].r=arr.size();
            arr.push_back({-1, -1, 0});
        }
        update(arr[nodeNum].r, mid+1, nodeR, k, val);
    }
    ll t1 = arr[nodeNum].l!=-1 ? arr[arr[nodeNum].l].val : 0;
    ll t2 = arr[nodeNum].r!=-1 ? arr[arr[nodeNum].r].val : 0;
    arr[nodeNum].val=t1+t2;
}

ll query(ll L, ll R, int nodeNum, int nodeL, int nodeR) {
    if(nodeNum==-1 || R<nodeL || nodeR<L) return 0;
    if(L<=nodeL && nodeR<=R) return arr[nodeNum].val;
    int mid = nodeL+nodeR>>1;
    return query(L, R, arr[nodeNum].l, nodeL, mid)+query(L, R, arr[nodeNum].r, mid+1, nodeR);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    for(int i=0;i<n;i++) {
        ll val; cin >> val;
        update(0, 0, n-1, i, val);
    }

    for(int i=0;i<m+k;i++) {
        ll a, b, c; cin >> a >> b >> c;
        if(a==1) update(0, 0, n-1, b-1, c);
        else cout << query(b-1, c-1, 0, 0, n-1) << '\n';
    }
}
```
