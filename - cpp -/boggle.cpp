#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 12 C

//can't get it to run in time D:

struct TrieNode {
    vector<TrieNode*> c = vector<TrieNode*>(26, nullptr);
    bool isWord = false;    //true if a word ends on this node
    int numWords = 0;   //counts how many words use this node as prefix
    string word = "";

    TrieNode* getNode(char ch) {
        int ind = ch - 'a';
        if(ind < 0 || ind >= 26){
            return nullptr;
        }
        return c[ind];
    }
};

struct Trie {
    TrieNode head = TrieNode();

    void insert(string s){
        TrieNode* ptr = &head;
        for(int i = 0; i < s.size(); i++){
            ptr->numWords ++;
            int ch = s[i] - 'a';
            if(ptr->c[ch] == nullptr) {
                ptr->c[ch] = new TrieNode();
            }
            ptr = ptr->c[ch];
        }
        ptr->numWords ++;
        ptr->isWord = true;
        ptr->word = s;
    }

    TrieNode* query(string s) {
        TrieNode* ptr = &head;
        for(int i = 0; i < s.size(); i++){
            int ch = s[i] - 'a';
            ptr = ptr->c[ch];
            if(ptr == nullptr) {
                break;
            }
        }
        return ptr;
    }
};

ll score = 0;
string longest = "";
set<string> counted;

vector<int> dr = {-1, -1, -1, 0, 0, 1, 1, 1};
vector<int> dc = {-1, 0, 1, -1, 1, -1, 0, 1};

void solve(vector<string>& g, TrieNode& t, vector<vector<bool>>& v, int r, int c) {
    //cout << "SOLVE" << endl;
    if(t.isWord) {
        //cout << "FOUND WORD" << endl;
        if(counted.find(t.word) == counted.end()){
            counted.insert(t.word);
            if(t.word.size() == 8) {
                score += 11;
            }
            else if(t.word.size() == 7) {
                score += 5;
            }
            else if(t.word.size() == 6){
                score += 3;
            }
            else if(t.word.size() == 5){
                score += 2;
            }
            else if(t.word.size() == 3 || t.word.size() == 4) {
                score += 1;
            }
            if(longest.size() < t.word.size()) {
                longest = t.word;
            }
            else if(longest.size() == t.word.size() && longest > t.word) {
                longest = t.word;
            }
        }
    }
    for(int i = 0; i < 8; i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        //cout << "NEXT : " << nr << " " << nc << endl;
        if(nr < 0 || nc < 0 || nr >= 4 || nc >= 4){
            //cout << "OUT OF BOUNDS" << endl;
            continue;
        }
        if(v[nr][nc]){
            //cout << "ALREADY VISITED" << endl;
            continue;
        }
        TrieNode* nextNode = t.getNode(g[nr][nc]);
        if(nextNode == nullptr) {
            //cout << "DOESNT EXIST" << endl;
            continue;
        }
        //cout << "NEXT CHAR : " << g[nr][nc] << " " << nr << " " << nc << endl;
        v[nr][nc] = true;
        solve(g, *nextNode, v, nr, nc);
        v[nr][nc] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    Trie t;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < s.size(); j++){
            s[j] = (char) (s[j] + 'a' - 'A');
        }
        t.insert(s);
    }
    int m;
    cin >> m;
    vector<vector<bool>> v(4, vector<bool>(4, false));
    for(int i = 0; i < m; i++){
        vector<string> g(4);
        for(int j = 0; j < 4; j++){
            cin >> g[j];
            for(int k = 0; k < 4; k++){
                g[j][k] += 'a' - 'A';
            }
        }
        //cout << "START SEARCH" << endl;
        score = 0;
        longest = "";
        counted.clear();
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                //v[j][k] = true;
                solve(g, t.head, v, j, k);
                //v[j][k] = false;
            }
        }
        //cout << "SEARCH FIN" << endl;
        for(int j = 0; j < longest.size(); j++){
            longest[j] += 'A' - 'a';
        }
        cout << score << " " << longest << " " << counted.size() << "\n";
    }
    
    return 0;
}

