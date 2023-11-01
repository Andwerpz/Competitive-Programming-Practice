#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1890C

//first, note that if a string contains an unequal amount of '0' and '1' characters, then it's impossible
//to make it good. This rules out all strings of odd length. 

//next, i claim that fas;dkfjas;fkljasd;fa
//bruh, idk what i did to solve this.

vector<int> find_seq(string s) {
    vector<int> ans(0);
    while(s.size() != 0){
        for(int i = s.size() - 2; i >= 0; i--){
            if(s[i] == '0' && s[i + 1] == '1') {
                ans.push_back(i);
                s = s.substr(0, i) + s.substr(i + 2);
                break;
            }
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // vector<int> tmp_seq = find_seq("00100111");
    // for(int i = 0; i < tmp_seq.size(); i++){
    //     cout << tmp_seq[i] << " ";
    // }
    // cout << endl;
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int zcnt = 0;
        int ocnt = 0;
        for(int i = 0; i < s.size(); i++){
            zcnt += s[i] == '0';
            ocnt += s[i] == '1';
        }
        if(zcnt != ocnt) {
            cout << "-1\n";
            continue;
        }
        vector<int> ans(0);
        int beg_cnt = 0;
        int l_ptr = 0;
        int r_ptr = n - 1;
        bool is_valid = true;
        while(l_ptr < r_ptr) {
            if(s[l_ptr] != s[r_ptr]) {
                l_ptr ++;
                r_ptr --;
                continue;
            }
            if(s[l_ptr] == '0') {
                int tmp = l_ptr;
                zcnt = 0;
                while(l_ptr <= r_ptr && zcnt + (s[l_ptr] == '0'? 1 : -1) >= 0) {
                    zcnt += s[l_ptr] == '0'? 1 : -1;
                    l_ptr ++;
                }
                string substring = s.substr(tmp, l_ptr - tmp);
                reverse(substring.begin(), substring.end());
                for(int i = 0; i < substring.size(); i++){
                    substring[i] = substring[i] == '1'? '0' : '1';
                }
                vector<int> seq = find_seq(substring);
                for(int i = 0; i < seq.size(); i++){
                    ans.push_back(seq[i] + r_ptr + beg_cnt + 1);
                }
                continue;
            }
            else {
                int tmp = r_ptr;
                ocnt = 0;
                while(r_ptr >= l_ptr && ocnt + (s[r_ptr] == '1'? 1 : -1) >= 0) {
                    ocnt += s[r_ptr] == '1'? 1 : -1;
                    r_ptr --;
                }
                string substring = s.substr(r_ptr + 1, tmp - r_ptr);
                reverse(substring.begin(), substring.end());
                for(int i = 0; i < substring.size(); i++){
                    substring[i] = substring[i] == '1'? '0' : '1';
                }
                vector<int> seq = find_seq(substring);
                for(int i = 0; i < seq.size(); i++){
                    ans.push_back(seq[i] + l_ptr + beg_cnt);
                }
                beg_cnt += seq.size() * 2;
                continue;
            }
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
