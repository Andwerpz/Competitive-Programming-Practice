#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 05 B

//just brute force all the possible strings

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    string ans = s;
    for(int i = 1; i < s.length() - 1; i++){
        for(int j = 1; j < s.length() - i; j++){
            string a = s.substr(0, i);
            string b = s.substr(i, j);
            string c = s.substr(i + j);
            reverse(a.begin(), a.end());
            reverse(b.begin(), b.end());
            reverse(c.begin(), c.end());
            string next = a + b + c;
            if(next < ans) {
                ans = next;
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
