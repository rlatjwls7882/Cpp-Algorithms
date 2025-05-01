/** https://www.acmicpc.net/problem/9250 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

struct trie {
    trie* go[26] = {0, };
    bool finish=false;
    trie* fail;

    void insert(char* ch) {
        if(*ch==NULL) {
            finish=true;
            return;
        }

        if(!go[*ch-'a']) go[*ch-'a'] = new trie;
        go[*ch-'a']->insert(ch+1);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    trie* root = new trie;

    while(n--) {
        string s; cin >> s;
        root->insert(&s[0]);
    }

    queue<trie*> q; q.push(root);
    root->fail = root;
    while(!q.empty()) {
        trie* cur = q.front(); q.pop();
        for(int i=0;i<26;i++) {
            if(!cur->go[i]) continue;
            trie* next = cur->go[i];

            if(cur==root) {
                next->fail = root;
            } else {
                trie* dest = cur->fail;
                while(dest!=root && !dest->go[i]) dest = dest->fail;
                if(dest->go[i]) dest = dest->go[i];
                next->fail = dest;
            }
            if(next->fail->finish) next->finish=true;
            q.push(next);
        }
    }

    int Q; cin >> Q;
    while(Q--) {
        string s; cin >> s;
        trie* cur = root;
        for(int i=0;i<s.length();i++) {
            while(cur!=root && !cur->go[s[i]-'a']) cur = cur->fail;
            if(cur->go[s[i]-'a']) cur = cur->go[s[i]-'a'];
            if(cur->finish) break;
        }
        if(cur->finish) cout << "YES\n";
        else cout << "NO\n";
    }
}
