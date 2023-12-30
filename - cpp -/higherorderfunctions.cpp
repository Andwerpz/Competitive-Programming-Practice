#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2020 Online H

//simple string parsing implementation. 

int solve(string& s, int r_l, int r_r) {
    //cout << "SOLVING : " << s.substr(r_l, r_r - r_l) << endl;
    if(r_l + 2 == r_r) {
        return 0;
    }
    int ans = 0;
    int cnt = 0;
    for(int i = r_l; i < r_r; i++){
        if(i == r_r - 1 && cnt == 1 && s[i] == ')') {
            return solve(s, r_l + 1, r_r - 1);
        }
        if(s[i] == '(') {
            cnt ++;
        }
        else if(s[i] == ')') {
            cnt --;
        }
        if(cnt == 0 && s[i] == ')') {
            int ans = solve(s, r_l, i + 1);
            if(i != r_r - 1) {
                int ans_2 = solve(s, i + 3, r_r);
                ans = max(ans + 1, ans_2);
            }
            return ans;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    cout << solve(s, 0, s.size()) << "\n";
    
    return 0;
}
