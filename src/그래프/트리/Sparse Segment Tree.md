# Sparse Segment Tree (Dynamic Segment Tree with Lazy Propagation) 🟢 Platinum I
Dynamic Segment Tree를 느리게 갱신하는 알고리즘

시간복잡도 : $O(Q \log N)$ (Q : 쿼리의 수)

[연습문제 (백준 20212번)](https://www.acmicpc.net/problem/20212)

구현 방식은 Dynamic Segment Tree에 Lazy Propagation을 추가한 느낌이라 별도의 설명은 생략한다.

``` c++
/** http://boj.kr/2076e6b093e7480d8b49027defbb2966 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

struct SparseSeg {
    struct Node {
        int l=-1, r=-1;
        ll val=0, lazy=0;
    };
    vector<Node> arr = vector<Node>(1);
    void addNode(int nodeNum) {
        if(arr[nodeNum].l==-1) {
            arr[nodeNum].l=arr.size();
            arr.push_back({});
        }
        if(arr[nodeNum].r==-1) {
            arr[nodeNum].r=arr.size();
            arr.push_back({});
        }
    }
    void updateLazy(int nodeNum, ll nodeL, ll nodeR) {
        if(arr[nodeNum].lazy) {
            arr[nodeNum].val+=arr[nodeNum].lazy*(nodeR-nodeL+1);
            if(nodeL!=nodeR) {
                addNode(nodeNum);
                arr[arr[nodeNum].l].lazy+=arr[nodeNum].lazy;
                arr[arr[nodeNum].r].lazy+=arr[nodeNum].lazy;
            }
            arr[nodeNum].lazy=0;
        }
    }

    void addRange(ll L, ll R, ll val, int nodeNum, ll nodeL, ll nodeR) {
        updateLazy(nodeNum, nodeL, nodeR);
        if(R<nodeL || nodeR<L) return;
        if(L<=nodeL && nodeR<=R) {
            arr[nodeNum].lazy+=val;
            updateLazy(nodeNum, nodeL, nodeR);
            return;
        }

        ll mid=nodeL+nodeR>>1;
        addNode(nodeNum);
        addRange(L, R, val, arr[nodeNum].l, nodeL, mid);
        addRange(L, R, val, arr[nodeNum].r, mid+1, nodeR);
        ll v1 = arr[nodeNum].l!=-1 ? arr[arr[nodeNum].l].val : 0;
        ll v2 = arr[nodeNum].r!=-1 ? arr[arr[nodeNum].r].val : 0;
        arr[nodeNum].val=v1+v2;
    }

    ll sum(ll L, ll R, int nodeNum, ll nodeL, ll nodeR) {
        if(nodeNum==-1 || R<nodeL || nodeR<L) return 0;
        updateLazy(nodeNum, nodeL, nodeR);
        if(L<=nodeL && nodeR<=R) return arr[nodeNum].val;
        int mid = nodeL+nodeR>>1;
        return sum(L, R, arr[nodeNum].l, nodeL, mid)+sum(L, R, arr[nodeNum].r, mid+1, nodeR);
    }
};

struct query {
    int i, j, k, idx;
    bool operator<(const query q) const {
        return k < q.k;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;

    vector<query> q1, q2;
    for(int i=0;i<n;i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        if(a==1) q1.push_back({b, c, d, (int)q1.size()});
        else q2.push_back({b, c, d-1, (int)q2.size()});
    }
    sort(q2.begin(), q2.end());

    int idx=0;
    SparseSeg ss;
    vector<ll> res(q2.size());
    for(query q:q1) {
        ss.addRange(q.i, q.j, q.k, 0, 1, 1e9);
        while(idx<q2.size() && q2[idx].k==q.idx) {
            res[q2[idx].idx]=ss.sum(q2[idx].i, q2[idx].j, 0, 1, 1e9);
            idx++;
        }
    }
    for(auto e:res) cout << e << '\n';
}
```
