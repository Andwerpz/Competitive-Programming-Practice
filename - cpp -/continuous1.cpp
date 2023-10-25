#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC150A

//my implementation is really bad. 

//intended way is just a sliding window solution; check whether there are multiple solutions. 

void fill_left(string& s, int start, int& one_cnt, int k) {
    for(int i = start; i < s.size(); i++){
        if(s[i] == '0'){
            break;
        }
        if(one_cnt < k && s[i] == '?') {
            s[i] = '1';
            one_cnt ++;
        }
    }
}

void fill_right(string& s, int start, int& one_cnt, int k) {
    for(int i = start; i >= 0; i--){
        if(s[i] == '0') {
            break;
        }
        if(one_cnt < k && s[i] == '?') {
            s[i] = '1';
            one_cnt ++;
        }
    }
}

void fill_zero(string& s) {
    for(int i = 0; i < s.size(); i++){
        if(s[i] == '?') {
            s[i] = '0';
        }
    }
}

bool is_continuous(string& s) {
    bool found = false;
    int cnt = 0;
    for(int i = 0; i < s.size(); i++){
        if(!found) {
            if(s[i] == '1') {
                found = true;
                cnt ++;
            }
        }
        else {
            if(s[i] == '0') {
                found = false;
            }
        }
    }
    return cnt == 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        int l_one = 0;
        int r_one = n - 1;
        for(int i = 0; i < n; i++){
            if(s[i] == '1') {
                l_one = i;
                break;
            }
        }
        for(int i = n - 1; i >= 0; i--){
            if(s[i] == '1') {
                r_one = i;
                break;
            }
        }
        int one_cnt = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '1') {
                one_cnt ++;
            }
        }
        if(one_cnt == 0){
            //check how many consecutive things of '?' there are of length geq k 
            int nr = 0;
            int nr_geq = 0;
            for(int i = 0; i < s.size(); i++){
                if(s[i] == '?') {
                    int r = i;
                    while(r != n && s[r] == '?') {
                        r ++;
                    }
                    if(r - i == k) {
                        nr ++;
                    }
                    else if(r - i >= k){
                        nr_geq ++;
                    }
                    i = r - 1;
                }
            }
            if(nr == 1 && nr_geq == 0){
                cout << "Yes\n";
                continue;
            }
            cout << "No\n";
            continue;
        }
        bool found_zero = false;
        for(int i = l_one; i <= r_one; i++){
            if(s[i] == '0') {
                found_zero = true;
            }
        }
        if(found_zero) {
            cout << "No\n";
            continue;
        }
        if(r_one - l_one + 1 > k) {
            cout << "No\n";
            continue;
        }
        if(r_one - l_one + 1 == k) {
            cout << "Yes\n";
            continue;
        }
        string s1 = s;
        string s2 = s;
        int s1_one = one_cnt;
        int s2_one = one_cnt;
        fill_left(s1, l_one, s1_one, k);
        fill_right(s1, r_one, s1_one, k);
        fill_right(s2, r_one, s2_one, k);
        fill_left(s2, l_one, s2_one, k);
        fill_zero(s1);
        fill_zero(s2);
        if(s1_one != k || s1 != s2 || !is_continuous(s1)) {
            cout << "No\n";
            continue;
        }
        cout << "Yes\n";
    }
    
    return 0;
}
