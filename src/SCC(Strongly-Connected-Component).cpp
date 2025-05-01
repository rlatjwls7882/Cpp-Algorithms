/** https://www.acmicpc.net/problem/2150 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 10001;

bool visited[MAX];
int idx, parent[MAX];
vector<vector<int>> conn(MAX), SCCs;
stack<int> stk;

int dfs(int cur) {
    stk.push(cur);
    int rem = parent[cur] = ++idx;

    for(int next:conn[cur]) {
        if(!parent[next]) rem = min(rem, dfs(next));
        else if(!visited[next]) rem = min(rem, parent[next]);
    }

    if(rem==parent[cur]) {
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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int v, e; cin >> v >> e;

    while(e--) {
        int a, b; cin >> a >> b;
        conn[a].push_back(b);
    }

    // dfs
    for(int i=1;i<=v;i++) {
        if(!visited[i]) dfs(i);
    }

    // sort
    for(int i=0;i<SCCs.size();i++) {
        sort(SCCs[i].begin(), SCCs[i].end());
    }
    sort(SCCs.begin(), SCCs.end());

    // print
    cout << SCCs.size() << endl;
    for(auto SCC:SCCs) {
        for(int val:SCC) {
            cout << val << ' ';
        }
        cout << "-1\n";
    }
}
