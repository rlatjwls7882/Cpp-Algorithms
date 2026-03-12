# Hopcroft-Karp Algorithm 🟢 Platinum III
Kuhn's Algorithm을 개선해 Shortest Augmenting Path를 여러개씩 찾는 알고리즘

시간복잡도 : O($E\sqrt V$)

[연습 문제(백준 3736번)](https://www.acmicpc.net/problem/3736)

전체 동작 과정은 한번의 bfs로 level(최단 거리)를 만들고, 그 level을 따라 여러개의 Shortest Augmenting Path를 찾아주는 것이다.

``` c++
int main() {
    memset(a, -1, sizeof a);
    memset(b, -1, sizeof b);
    int res=0;
    while(true) {
        bfs();
        int flow=0;
        for(int i=0;i<n;i++) flow += a[i]==-1 && dfs(i);
        if(!flow) break;
        res+=flow;
    }
}
```

bfs는 아직 매칭되지 않은 왼쪽 정점에서 시작해서, (a->b->b에 매칭된 a)로 이동하며 level을 만든다.

``` c++
void bfs() {
    queue<int> q;
    for(int i=0;i<n;i++) {
        if(a[i]==-1) {
            level[i]=0;
            q.push(i);
        } else {
            level[i]=-1;
        }
    }
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int next:conn[cur]) {
            if(b[next]!=-1 && level[b[next]]==-1) {
                level[b[next]]=level[cur]+1;
                q.push(b[next]);
            }
        }
    }
}
```

dfs는 기존의 이분매칭과 동일하게 Shortest Augmenting Path를 찾고, level이 1씩 증가하도록 따라간다.

``` c++
bool dfs(int cur) {
    for(int next:conn[cur]) {
        if(b[next]==-1 || level[b[next]]==level[cur]+1 && dfs(b[next])) {
            b[next]=cur;
            a[cur]=next;
            return true;
        }
    }
    return false;
}
```

전체 코드
``` c++
/** http://boj.kr/0caadcb1dfd340e39b9216f9e307abc5 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

const int MAX = 20000;

vector<vector<int>> conn(MAX);
int n, a[MAX], b[MAX], level[MAX];

void bfs() {
    queue<int> q;
    for(int i=0;i<n;i++) {
        if(a[i]==-1) {
            level[i]=0;
            q.push(i);
        } else {
            level[i]=-1;
        }
    }
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int next:conn[cur]) {
            if(b[next]!=-1 && level[b[next]]==-1) {
                level[b[next]]=level[cur]+1;
                q.push(b[next]);
            }
        }
    }
}

bool dfs(int cur) {
    for(int next:conn[cur]) {
        if(b[next]==-1 || level[b[next]]==level[cur]+1 && dfs(b[next])) {
            b[next]=cur;
            a[cur]=next;
            return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    while(true) {
        cin >> n;
        if(cin.fail()) break;
        for(int i=0;i<n;i++) conn[i].clear();

        for(int i=0;i<n;i++) {
            string s; cin >> s >> s;
            int k = stoi(s.substr(1, s.length()-2));
            while(k--) {
                int next; cin >> next;
                conn[i].push_back(next-n);
            }
        }

        memset(a, -1, sizeof a);
        memset(b, -1, sizeof b);
        int res=0;
        while(true) {
            bfs();
            int flow=0;
            for(int i=0;i<n;i++) flow += a[i]==-1 && dfs(i);
            if(!flow) break;
            res+=flow;
        }
        cout << res << '\n';
    }
}
```