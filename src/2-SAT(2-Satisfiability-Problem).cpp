/** https://www.acmicpc.net/problem/11280 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 20000;

int idx, parent[MAX];
bool visited[MAX];
vector<vector<int>> conn(MAX), SCCs;
stack<int> stk;

int dfs(int cur) {
    stk.push(cur);
    int rem = parent[cur] = ++idx;

    for(int next:conn[cur]) {
        if(!parent[next]) rem = min(rem, dfs(next));
        else if(!visited[next]) rem = min(rem, parent[next]);
    }

    if(rem == parent[cur]) {
        SCCs.push_back(vector<int>());
        while(true) {
            int top = stk.top(); stk.pop();
            SCCs.back().push_back(top);
            visited[top] = true;
            parent[top] = rem;
            if(top==cur) break;
        }
    }
    return rem;
}

int oppo(int x) {
    return x%2==0 ? x+1 : x-1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    while(m--) {
        int x, y; cin >> x >> y;
        x = x<0 ? -x*2-2 : x*2-1;
        y = y<0 ? -y*2-2 : y*2-1;
        conn[oppo(x)].push_back(y);
        conn[oppo(y)].push_back(x);
    }

    for(int i=0;i<2*n;i++) {
        if(!visited[i]) dfs(i);
    }

    for(int i=0;i<2*n;i+=2) {
        if(parent[i]==parent[i+1]) {
            cout << 0;
            return 0;
        }
    }
    cout << 1;
}
