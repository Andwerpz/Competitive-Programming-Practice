#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ACPC 2023 Fall Contest C

//maintain two pointers; the maximum you can travel to the left and right. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    int loc = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == '?') {
            loc = i;
            break;
        }
    }
    set<char> unlocked;
    int l = loc;
    int r = loc;
    bool escape = false;
    while(true) {
        bool moved = false;
        //move left
        if(l - 1 < 0) {
            escape = true;
            break;
        }
        else if(s[l - 1] == '.') {
            moved = true;
            l --;
        }
        else if('a' <= s[l - 1] && s[l - 1] <= 'z') {
            moved = true;
            unlocked.insert(s[l - 1] - 'a' + 'A');
            l --;
        }
        else if(unlocked.find(s[l - 1]) != unlocked.end()) {
            moved = true;
            l --;
        }
        //move right
        if(r + 1 == n) {
            escape = true;
            break;
        }
        else if(s[r + 1] == '.') {
            moved = true;
            r ++;
        }
        else if('a' <= s[r + 1] && s[r + 1] <= 'z') {
            moved = true;
            unlocked.insert(s[r + 1] - 'a' + 'A');
            r ++;
        }
        else if(unlocked.find(s[r + 1]) != unlocked.end()) {
            r ++;
            moved = true;
        }
        if(!moved) {
            break;
        }
    }
    cout << (escape? "YES" : "NO") << "\n";
    
    return 0;
}
