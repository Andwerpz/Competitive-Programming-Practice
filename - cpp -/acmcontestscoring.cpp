#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 00

//just implementation, nothing too special

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    set<char> sol;
    map<char, int> penalty;
    int t;
    cin >> t;
    int ans = 0;
    while(t != -1) {
        char c;
        cin >> c;
        string s;
        cin >> s;
        if(sol.find(c) == sol.end()) {
            if(s == "wrong") {
                if(penalty.find(c) == penalty.end()) {
                    penalty.insert({c, 0});
                }
                penalty.find(c) -> second += 20;
            }
            else {
                ans += t + penalty.find(c) -> second;
                sol.insert(c);
            }
        }
        cin >> t;
    }
    cout << sol.size() << " " << ans << '\n';
    
    return 0;
}
