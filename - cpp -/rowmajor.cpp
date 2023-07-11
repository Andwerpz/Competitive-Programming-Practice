#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1844D

//this can be thought of as a graph coloring problem. If a letter is ever adjacent to another letter, draw an edge between the two
//somehow, the greedy graph coloring algorithm produces an optimal coloring. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        //for each divisor of n, draw all connections
        //should be around nlog(n) total. 
        vector<int> div(0);
        for(int i = 1; i < n; i++){
            if(n % i != 0){
                continue;
            }
            div.push_back(i);
        }
        //do graph coloring greedily
        vector<vector<bool>> v(n, vector<bool>(26, false));
        for(int i = 0; i < n; i++){
            char cur = 'a';
            for(int j = 0; j < 26; j++){
                if(!v[i][j]) {
                    break;
                }
                cur ++;
            }
            for(int j = 0; j < div.size(); j++){
                if(i + div[j] >= n){
                    break;
                }
                v[i + div[j]][cur - 'a'] = true;
            }
            cout << cur;
        }
        cout << "\n";
    }
    
    return 0;
}
