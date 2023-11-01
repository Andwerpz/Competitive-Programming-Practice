#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1890B

//if s is initially good, then print 'Yes'

//else, we need to insert t into s to make s good. 
//note that if t is not good, then we cannot fix s using t, and we should print 'No'. 

//otherwise, what can t fix? 
//if t starts and ends with '1', then it can fix any spot in s with consecutive '0' characters. 
//likewise if t starts and ends with '0'. 
//if t starts and ends with different characters, then t cannot fix any s. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        string s, t;
        cin >> s >> t;
        bool s_good = true;
        bool t_good = true;
        bool s_ones = false;
        bool s_zeroes = false;
        for(int i = 0; i < n - 1; i++){
            if(s[i] == s[i + 1]) {
                s_good = false;
                if(s[i] == '1') {
                    s_ones = true;
                }
                else {
                    s_zeroes = true;
                }
            }
        }
        for(int i = 0; i < m - 1; i++){
            if(t[i] == t[i + 1]) {
                t_good = false;
            }
        }
        if(s_good) {
            cout << "Yes\n";
            continue;
        }
        if(!t_good) {
            cout << "No\n";
            continue;
        }
        if(s_ones && s_zeroes) {
            cout << "No\n";
            continue;
        }
        if(s_ones && t[0] == '0' && t[m - 1] == '0') {
            cout << "Yes\n";
            continue;
        }
        if(s_zeroes && t[0] == '1' && t[m - 1] == '1') {
            cout << "Yes\n";
            continue;
        }
        cout << "No\n";
    }
    
    return 0;
}
