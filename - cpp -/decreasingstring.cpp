#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1886C

//if we can figure out the order in which all the characters are removed, then it's pretty easy to
//find the character at the given position. 

//when removing characters, we first greedily go from front to back to convert the string into a
//monotonically increasing string, then we go from back to front to remove the remaining characters. 

//to find the order for the non-monotonically increasing substrings within the string, we can recursively
//apply our algorithm. 

void find_order(int l, int r, string& s, vector<int>& ans, int& next) {
    //cout << "SOLVE : "<< l << " " << r << "\n";
    //create suffix min
    vector<char> sfx(r - l, 'z');
    for(int i = sfx.size() - 1; i >= 0; i--){
        sfx[i] = min(sfx[i], s[i + l]);
        if(i != sfx.size() - 1) {
            sfx[i] = min(sfx[i], sfx[i + 1]);
        }
    }
    //for each segment that is not suffix min, recursively find the order
    for(int i = 0; i < sfx.size(); i++){
        if(sfx[i] != s[i + l]) {
            int rptr = i;
            while(rptr != r && sfx[rptr] != s[rptr + l]) {
                rptr ++;
            }
            find_order(i + l, rptr + l, s, ans, next);
            i = rptr - 1;
        }
    }
    //for each element that is suffix min, we remove these last in reverse order
    for(int i = sfx.size() - 1; i >= 0; i--){
        if(sfx[i] == s[i + l]) {
            ans[i + l] = next ++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int n = s.size();
        vector<bool> in(n, true);
        ll pos;
        cin >> pos;
        pos --;
        vector<int> order(n, -1);
        int next = 0;
        find_order(0, n, s, order, next);
        int nr_ops = 0;
        int cur_len = n;
        while(pos >= cur_len) {
            pos -= cur_len;
            cur_len --;
            nr_ops ++;
        }
        // for(int i = 0; i < n; i++){
        //     cout << order[i] << " ";
        // }
        // cout << "\n";
        char ans = 0;
        for(int i = 0; i < n; i++){
            if(order[i] >= nr_ops) {
                if(pos == 0){
                    ans = s[i];
                    break;
                }
                pos --;
            }
        }
        cout << ans;
    }
    cout << "\n";
    
    return 0;
}
