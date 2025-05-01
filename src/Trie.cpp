/** https://www.acmicpc.net/problem/5670 제출 코드 */
#include<bits/stdc++.h>
using namespace std;

struct trie {
    trie* go[26] = {0, };
    int branch=0, wordCnt=0;

    ~trie() {
        for(int i=0;i<26;i++) {
            if(go[i]) delete go[i];
        }
    }

    void insert(char* ch) {
        if(*ch==NULL) {
            branch++;
            return;
        }
        if(!go[*ch-'a']) {
            go[*ch-'a'] = new trie;
            branch++;
        }
        wordCnt++;
        go[*ch-'a']->insert(ch+1);
    }

    long long getCnt(int depth) {
        long long res=0;
        if(depth==0 || branch>=2) res += wordCnt;
        for(int i=0;i<26;i++) {
            if(go[i]) res += go[i]->getCnt(depth+1);
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while(true) {
        int n; cin >> n;
        if(cin.fail()) break;

        trie* root = new trie;
        for(int i=0;i<n;i++) {
            string s; cin >> s;
            root->insert(&s[0]);
        }
        cout << setprecision(2) << fixed << root->getCnt(0) / (double)n << '\n';
        delete root;
    }
}
